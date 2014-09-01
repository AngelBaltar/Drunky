/* 
 * File:    DrinkObject.cpp
 * Author: angel
 * 
 */
#include <SDL_image.h>
#include <iostream>

#include "GameFrameWork/GameContainer.h"
#include "GameFrameWork/DrinkObject.h"
#include "GameFrameWork/BoardObject.h"
#include "utils/utils.h"

SDL_Texture* DrinkObject::drinkImgs[6]={NULL,NULL,NULL,NULL,NULL,NULL};

const char* DrinkObject::getImgsPath[6]={"",
                                       STR(RESOURCES)"/gfx/Red.png",
                                       STR(RESOURCES)"/gfx/Blue.png",
                                       STR(RESOURCES)"/gfx/Green.png",
                                       STR(RESOURCES)"/gfx/Yellow.png",
                                       STR(RESOURCES)"/gfx/Purple.png",
                                      };

/**
* create a drink into a board
* @param board the board
* @param posx x position
* @param posy y position
* @param heigh
* @param width 
* @param type drink type
*/
DrinkObject::DrinkObject(BoardObject& board,
                unsigned int posx,
                unsigned int posy,DrinkType type):GameObject(posx,posy,42,42),
                                                _board(board),_type(type),_step(random()%3 +1),
                                                _delta_x(0),_delta_y(0),
                                                _draggedByNeighbor(false)
{

}

DrinkObject::DrinkObject(const DrinkObject& orig):GameObject(orig),
                                            _board(orig._board),
                                            _type(orig.getType()),_step(orig._step),
                                            _delta_x(orig._delta_x),
                                            _delta_y(orig._delta_y),
                                            _draggedByNeighbor(false)
{
}

DrinkObject::~DrinkObject()
{
}

/**
* 
* @return the type of this drink
*/
DrinkObject::DrinkType DrinkObject::getType() const
{
    return this->_type;
}

/**
* draws the object
*/
void DrinkObject::draw()
{
    if(this->_type==DrinkObject::noneDrink){
        return;
    }
    SDL_Renderer * render=this->_board.getContainer().getRenderer();
    if(DrinkObject::drinkImgs[this->_type]==0){
        DrinkObject::drinkImgs[this->_type]=IMG_LoadTexture(render, 
                                    DrinkObject::getImgsPath[this->_type]);
    }
    SDL_Rect DestR;
    DestR.x = this->getPosX()+this->_delta_x;
    DestR.y = this->getPosY()+this->_delta_y;
    DestR.h=this->getHeigh();
    DestR.w=this->getWidth();
    if(this->isDead() || !this->_board.getContainer().isGameStarted()){
        SDL_SetTextureAlphaMod(DrinkObject::drinkImgs[this->_type],128);
    }
    if(this->isDead()){
        switch(this->_type){
            case DrinkObject::blueDrink: 
            {
               SDL_SetTextureColorMod(DrinkObject::drinkImgs[this->_type],128,128,255);
               break;
            }
            case DrinkObject::redDrink: 
            {
               SDL_SetTextureColorMod(DrinkObject::drinkImgs[this->_type],255,128,128);
               break;
            }
            case DrinkObject::greenDrink: 
            {
               SDL_SetTextureColorMod(DrinkObject::drinkImgs[this->_type],128,255,128);
               break;
            }
            case DrinkObject::yellowDrink: 
            {
               SDL_SetTextureColorMod(DrinkObject::drinkImgs[this->_type],255,255,128);
               break;
            }
            case DrinkObject::purpleDrink: 
            {
               SDL_SetTextureColorMod(DrinkObject::drinkImgs[this->_type],255,128,255);
               break;
            }
            default:break;
        }
    }
    SDL_RenderCopy(render, DrinkObject::drinkImgs[this->_type], NULL, &DestR);
    if(this->isDead() || !this->_board.getContainer().isGameStarted()){
        SDL_SetTextureAlphaMod(DrinkObject::drinkImgs[this->_type],255);
    }
    if(this->isDead()){
        SDL_SetTextureColorMod(DrinkObject::drinkImgs[this->_type],255,255,255);
    }
        
}

/**
* updates the object
*/
void DrinkObject::update(unsigned long dt)
{
    if(this->_type==DrinkObject::noneDrink){
        return;
    }
    if(this->_board.canFallDown(this)){
        unsigned move=this->getPosY()+(dt/4)*this->_step;
        this->setPosY(move);
    }
    else{
        //keep the drink in the middle
        int centery=this->_board.getCenterY(this);
        int centerx=this->_board.getCenterX(this);
        if(!this->isDragged()){
            //keep myself on the middle
            if(this->getPosY()!=centery){
             this->setPosY(centery);
            }
            if(this->getPosX()!=centerx){
             this->setPosX(centerx);
            }
        }
    }
}

/**
* inform of events to the object
* @param e the event
*/
void DrinkObject::handleEvent(SDL_Event *e)
{
    if(this->_type==DrinkObject::noneDrink){
        return;
    }
    int x_begin=this->getPosX();
    int x_end=x_begin+this->getWidth();
    int y_begin=this->getPosY();
    int y_end=y_begin+this->getHeigh();
    switch(e->type)
    {
        case SDL_EventType::SDL_MOUSEBUTTONDOWN:
        {
            
            if(e->button.x>x_begin && e->button.x<x_end
              && e->button.y>y_begin && e->button.y<y_end){
                //I m being dragged
                this->setDragged(true);
                this->_draggedByNeighbor=false;
                this->_delta_x=0;
                this->_delta_y=0;
            }
            break;
        }
        case SDL_EventType::SDL_MOUSEBUTTONUP:
        {
           // DEBUG(std::cout<<"drop:"<<e->button.x<<" "<<e->button.y<<std::endl;);
            if(this->isDragged()){
                //Im being released
                this->setDragged(false);
                this->_draggedByNeighbor=false;
                this->setPosX(this->getPosX()+this->_delta_x);
                this->setPosY(this->getPosY()+this->_delta_y);
            }
            break;
        }
        case SDL_EventType::SDL_MOUSEMOTION:
        {
            //DEBUG(std::cout<<"move:"<<e->motion.xrel<<" "<<e->motion.yrel<<std::endl;);
            if(this->isDragged() && !this->_draggedByNeighbor){
                //Im being delta moving
                
                int xrel=e->motion.xrel;
                int yrel=e->motion.yrel;

                if(abs(xrel)>abs(yrel)){
                    yrel=0;
                }
                else{
                    xrel=0;
                }
             
                //CATCH ALL OTHER NEIGHBORS PUT THEIR DELTAS TO ZERO
                //BECAUSE YOU CAN CHANGE DIRECTION
                int n_x=(xrel<0)*(-1)+(xrel>0);
                int n_y=(yrel<0)*(-1)+(yrel>0);
                for(int i=-1;i<2;++i){
                    for(int j=-1;j<2;++j){
                        if(i==n_x && j==n_y){
                            continue;
                        }
                        if(i==0 && j==0){
                            continue;
                        }
                        GameObject * stencil=this->_board.getNeighbor(this,j,i);
                        DrinkObject * stencilDrink=dynamic_cast<DrinkObject*>(stencil);
                        if(stencilDrink){
                            stencilDrink->_delta_x=0;
                            stencilDrink->_delta_y=0;
                            stencilDrink->_draggedByNeighbor=false;
                            stencilDrink->setDragged(false);
                        }
                    }
                }
                GameObject * neighbor=this->_board.getNeighbor(this,n_y,n_x);
                DrinkObject * neighborDrink=dynamic_cast<DrinkObject*>(neighbor);
                
                int x_total=this->getPosX()+this->_delta_x+xrel;
                int y_total=this->getPosY()+this->_delta_y+yrel;
                int mov_x_begin=this->getPosX()-this->getWidth();
                int mov_x_end=mov_x_begin+(this->getWidth()<<1);
                int mov_y_begin=this->getPosY()-this->getHeigh();
                int mov_y_end=mov_y_begin+(this->getHeigh()<<1);

                if((x_total<mov_x_begin) || (x_total>mov_x_end)
                   ||(y_total<mov_y_begin) || (y_total>mov_y_end) )
                {
                    //we can not accept it, you are getting out of
                    //allowed movements
                    ;
                }
                else{
                    this->_delta_x+=xrel;
                    this->_delta_y+=yrel;
                    if(neighborDrink){
                        neighborDrink->_delta_x-=xrel;
                        neighborDrink->_delta_y-=yrel;
                        neighborDrink->_draggedByNeighbor=true;
                        neighborDrink->setDragged(true);
                    }
                }
            }
            break;
        }
   }
}

/**
* @return if the drink is empty
*/
bool DrinkObject::isEmpty() const
{
    return this->_type==DrinkObject::noneDrink;
}

/**
* 
* @return the name of the object 
*/
std::string DrinkObject::to_string()
{
    return "drink";
}

/**
* game object equal
* @param obj
* @return 
*/
bool DrinkObject::operator==(const DrinkObject &obj) const
{
    return this->_type==obj._type && this->_type!=DrinkObject::noneDrink;
}

/**
* compare objects with drinks
* @param obj
* @return 
*/
bool DrinkObject::operator==(const GameObject &obj) const
{
   const DrinkObject *g=dynamic_cast<const DrinkObject*>(&obj);
   if(!g){
       return false;
   }
   return this->operator==(*g);
}

/**
* game object equal
* @param obj
* @return 
*/
bool GameObject::operator==(const GameObject &obj) const
{
     //I dont like this thing much
    //it requires RTTI and is not efficient
    //but is the easiest way to do it
     const DrinkObject *g=dynamic_cast<const DrinkObject*>(&obj);
     const DrinkObject *h=dynamic_cast<const DrinkObject*>(this);
     if(!g || !h){
         return false;
     }
     return (*g)==(*h);
 }

/**
* assignament for objects
* @param obj
* @return 
*/
DrinkObject& DrinkObject::operator=(const DrinkObject& obj)
{
    GameObject::operator=(obj);
    this->_board=obj._board;
    this->_step=obj._step;
    this->_type=obj._type;
    return (*this);
}

/**
* sets the x position
* @param x position
*/
void DrinkObject::setPosX(unsigned int x)
{
    GameObject::setPosX(x);
    this->_delta_x=0;
}

/**
* sets the y position
* @param y position
*/
void DrinkObject::setPosY(unsigned int y)
{
    GameObject::setPosY(y);
    this->_delta_y=0;
}