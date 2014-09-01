/* 
 * File:   GameBoard.cpp
 * Author: angel
 * 
 */
#include <iostream>

#include "GameFrameWork/BoardObject.h"
#include "GameFrameWork/GameFactory.h"
#include "utils/Debug.h"
#include "utils/utils.h"

#define TIME_TO_KILL 190


const char* BoardObject::sound_effects_path[3]={STR(RESOURCES)"/sfx/pop1.wav",
                                          STR(RESOURCES)"/sfx/pop2.wav",
                                          STR(RESOURCES)"/sfx/pop3.wav"
                                            };
Mix_Chunk* BoardObject::sound_effecs[3]={NULL,NULL,NULL};

/**
* main constructor for the class
* @param container the game container
* @param posx the x position of the board
* @param posy the y position of the board
* @param heigh the heigh of the board
* @param width the width of the board
* @param yLength the y coordinates length
* @param xLength the x coordinates length
*/
BoardObject::BoardObject(GameContainer& container,
                 int posx,
                 int posy,
                 int heigh,
                 int width,
                 int yLength,
                 int xLength):GameObject(container,
                                    posx,
                                    posy,
                                    heigh,
                                    width),
                                    _yLength(yLength),
                                    _xLength(xLength),_kill_timer(0)
{
    this->_board=(GameObject**)malloc(sizeof(GameObject*)*yLength*xLength);
    for( int y=0;y<this->_yLength;++y){
        for( int x=0;x<this->_xLength;++x){
            (*this)[y][x]=GameFactory::createEmptyDrink((*this));
        }
    }
}

/**
* private copy constructor
* @param orig
* @return 
*/
BoardObject::BoardObject(const BoardObject& orig):GameObject(orig.getContainer(),
                                    orig.getPosX(),
                                    orig.getPosY(),
                                    orig.getHeigh(),
                                    orig.getWidth()),
                                    _board(orig._board),
                                    _yLength(orig._yLength),
                                    _xLength(orig._xLength),
                                    _kill_timer(orig._kill_timer)
{
    //note not deep copy here
}

/**
* main destructor for the class
*/
BoardObject::~BoardObject()
{
    //todo iterate and free
    for( int y=0;y<this->_yLength;++y){
        for( int x=0;x<this->_xLength;++x){
            (*this)[y][x]->~GameObject();
        }
    }
    free(this->_board);
    
}

/**
* index the y coordinate of the board
* @param y the y coordinate
* @return the entire row for the y coordinate
*/
GameObject ** BoardObject::operator[](const  int y)const
{
    if(y>=this->_yLength){
        DEBUG(std::cout<<"your are hitting the bone here "<<y<<std::endl);
        exit(21);
    }
    return this->_board+y*this->_xLength;
}

/**
* draws the object
*/
void BoardObject::draw()
{
    BoardObject &board=(*this);
    for( int y=0;y<this->_yLength;++y){
        for( int x=0;x<this->_xLength;++x){
             board[y][x]->draw();
        }
    }
    for( int y=0;y<this->_yLength;++y){
        for( int x=0;x<this->_xLength;++x){
             if(board[y][x]->isDragged()){
                //draw dragged ones always on top
                board[y][x]->draw();
             }
        }
    }
}

/**
* updates null the object in the board
*/
void BoardObject::updateEmptyDrink(GameObject*obj, int y, int x, unsigned long  dt)
{
    BoardObject &board=(*this);
    if(y==0){
        obj->~GameObject();
        obj=GameFactory::createRandomDrink((*this));
        int posx=x*obj->getWidth()+this->getPosX()+(obj->getWidth()>>1);
        int posy=this->getPosY()+(obj->getHeigh()>>1);
        obj->setPosX(posx);
        obj->setPosY(posy);
        board[0][x]=obj;
     
    }
}

/**
* updates non null the object in the board
*/
void BoardObject::updateNonEmptyDrink(GameObject*obj, int y, int x, unsigned long  dt)
{
    int posx_board=x*obj->getWidth()+this->getPosX()+(obj->getWidth()>>1);
    int posy_board=y*obj->getHeigh()+this->getPosY()+(obj->getHeigh()>>1);
    int board_x=this->getObjectPosX(obj);
    int board_y=this->getObjectPosY(obj);
    BoardObject &board=(*this);
    
    if(board[y][x]==board[board_y][board_x]){
        //the movement is not a real swap
        return;
    }
    
    // check drink movements to move them in the board
    if(obj->getPosX()!=posx_board || obj->getPosY()!=posy_board){

        int total_move=abs(y-board_y)+abs(x-board_x);

        if(board_y>=this->_yLength
                || board_x>=this->_xLength
                || total_move>1){
            //this is an invalid movement
            //reset
            obj->setPosX(posx_board);
            obj->setPosY(posy_board);
        }
        else{
            board[y][x]=board[board_y][board_x];
            board[board_y][board_x]=obj;
            if(!this->emptyObjs()) {
                //check the swap produces lines if just droped
                unsigned int old_size=this->_lines.size();
                this->getLines();
                DEBUG(std::cout<<"size lines:"<<this->_lines.size()<<"\n";);
                if(this->_lines.size()<=old_size) {
                    //if not swap them again
                    board[board_y][board_x]=board[y][x];
                    board[y][x]=obj;
                }
                else{
                    this->_kill_timer=0;
                }
                //put every one in his place
                board[y][x]->setPosX(x*board[y][x]->getWidth()+this->getPosX());
                board[y][x]->setPosY(y*board[y][x]->getHeigh()+this->getPosY());
                board[board_y][board_x]->setPosX(board_x*board[board_y][board_x]->getWidth()+this->getPosX());
                board[board_y][board_x]->setPosY(board_y*board[board_y][board_x]->getHeigh()+this->getPosY());
            }
            else{
                //having empty objects we dont update object positions
                //because objects are falling down, let them fall down
                //itselves, if we do setPositions here we are disturbing them
                this->_kill_timer=0;
            }
        }
    }
}

/**
* updates dead the object in the board
*/
void BoardObject::updateDeadDrink(GameObject*obj, int y, int x, unsigned long  dt)
{
    BoardObject &board=(*this);
    obj->~GameObject();
    board[y][x]=GameFactory::createEmptyDrink((*this));
}

/**
* updates the object
*/
void BoardObject::update( unsigned long  dt)
{
    BoardObject &board=(*this);
    this->_kill_timer-=dt;
    for( int y=0;y<this->_yLength;++y){
        for( int x=0;x<this->_xLength;++x){
            GameObject *obj=board[y][x];
            obj->update(dt);
            if(obj->isDead() && this->_kill_timer<=0){
                this->updateDeadDrink(obj,y,x,dt);
                continue;
            }
            if(obj->isEmpty()){
                this->updateEmptyDrink(obj,y,x,dt);
                continue;
            }
            if(!obj->isEmpty()){
                this->updateNonEmptyDrink(obj,y,x,dt);
                continue;
            } 
        }
    }
    if(this->_lines.empty()){
        this->getLines();
    }
    if(!this->_lines.empty() && this->getContainer().isGameStarted()){
        unsigned int rnd=random()&3;
        if(BoardObject::sound_effecs[rnd]==NULL){
            BoardObject::sound_effecs[rnd]=Mix_LoadWAV(BoardObject::sound_effects_path[rnd]);
        }
        Mix_PlayChannel(0,BoardObject::sound_effecs[rnd],1);
    }
    for(auto s: this->_lines){
        s->die();
    }
    if(!this->getContainer().isGameStarted()
         && this->_lines.empty()
         && !this->emptyObjs() ){
        this->getContainer().startGame();
    }
    if(this->getContainer().isGameStarted()){
        this->getContainer().addToScore(this->_lines.size());
    }
    this->_lines.clear();
    if(this->_kill_timer<=0){
        this->_kill_timer=TIME_TO_KILL;
    }
}

/**
* inform of events to the object
* @param e the event
*/
void BoardObject::handleEvent(SDL_Event *e)
{
    BoardObject &board=(*this);
    if(!this->_lines.empty() || this->emptyObjs()){
        //block input, the objects are moving
        return;
    }
    for( int y=0;y<this->_yLength;++y){
        for( int x=0;x<this->_xLength;++x){
            board[y][x]->handleEvent(e);
        }
    }
}

/**
* 
* @return the name of the object 
*/
std::string BoardObject::to_string()
{
    return "board";
}

/**
* returns true if the object can go down
* @param y
* @param x
* @return 
*/
bool BoardObject::canFallDown(GameObject *obj)
{
    BoardObject &board=(*this);
     int posx=this->getObjectPosX(obj);
     int posy=this->getObjectPosY(obj);
    if(posy>=this->_yLength-1){
        return false;
    }
    if(posx>=this->_xLength){
        return false;
    }
    return board[posy+1][posx]->isEmpty();
}

/**
* gets the x pos in the board
* @param obj
* @return 
*/
 int BoardObject::getObjectPosX(GameObject *obj)
{
    int posx=(obj->getPosX()-this->getPosX())/obj->getWidth();
    return posx;
}

/**
* gets the y pos in the board
* @param obj
* @return 
*/
 int BoardObject::getObjectPosY(GameObject *obj)
{
     int posy=(obj->getPosY()-this->getPosY())/obj->getHeigh();
     return posy;
}


/**
 * gets the center position x for a object
 * @param obj
 * @return 
 */
 int BoardObject::getCenterX(GameObject *obj)
{
     int posx=this->getObjectPosX(obj);
    return this->getPosX()+posx*obj->getWidth()+(obj->getWidth()>>1);
}

/**
 * gets the center position y for a object
 * @param obj
 * @return 
 */
 int BoardObject::getCenterY(GameObject *obj)
{
     int posy=this->getObjectPosY(obj);
    return this->getPosY()+posy*obj->getHeigh()+(obj->getHeigh()>>1);
}
 
/**
* gets the neighbor of object
* @param obj
* @param delta_y -1 or +1
* @param delta_x -1 or +1
* @return 
*/
GameObject* BoardObject::getNeighbor(GameObject *obj,int delta_y,int delta_x)
{
     int posy=this->getObjectPosY(obj);
     int posx=this->getObjectPosX(obj);
     if((posx+delta_x)>=0
         && (posx+delta_x)<this->_xLength
         && (posy+delta_y)>=0
         && (posy+delta_y)<this->_yLength){
         return (*this)[posy+delta_y][posx+delta_x];
     }
     return NULL;
}
 
/**
* gets the lines with x y in the middle of the stencil
* @param y
* @param x
*/
void BoardObject::getLines(int y,int x)
{    
    GameObject& obj=*((*this)[y][x]);
    BoardObject& board=(*this);
    std::vector< GameObject *> line;
    
    //check horizontal
    line.push_back(&obj);
    for(int step=-1;step<2;step+=2){
        int delta=step;
        while((x+delta)>=0
              && (x+delta)<this->_xLength
              && (*(board[y][x+delta]))==obj){
            line.push_back((*this)[y][x]);
            delta+=step;
        }
    }

    if(line.size()>=3){
        for(auto s: line){
            this->_lines.push_back(s);
        }
    }

    line.clear();

    //check vertical
    line.push_back(&obj);
    for(int step=-1;step<2;step+=2){
        int delta=step;
        while((y+delta)>=0 
             &&(y+delta)<this->_yLength
             &&  (*(board[y+delta][x]))==obj){
            line.push_back((*this)[y][x]);
            delta+=step;
        }
    }

    if(line.size()>=3){
        for(auto s: line){
            this->_lines.push_back(s);
        }
    }
}

/**
* @return the actual lines on the board 
*/
void BoardObject::getLines()
{ 
    for(int y=0;y<this->_yLength;++y){
        for(int x=0;x<this->_xLength;++x){
           GameObject& obj=*((*this)[y][x]);
            if(obj.isEmpty()){
                //we have an empty drink
                //this is not a good time to check lines
                //we wait until all drinks are placed
                this->_lines.clear();
                return ;
            }
            this->getLines(y,x);
        }
    }
}

/**
* 
* @return true if there are empty objects in the board 
*/
bool BoardObject::emptyObjs()
{
    BoardObject &board=(*this);
    for(int y=0;y<this->_yLength;++y){
        for(int x=0;x<this->_xLength;++x){
            if(board[y][x]->isEmpty()){
                return true;
            }
        }
    }
    return false;
}