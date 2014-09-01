/* 
 * File:   GameInfoPrinter.cpp
 * Author: angel
 * 
 * Created on 2 de julio de 2014, 19:28
 */

#include <iostream>

#include "GameFrameWork/GameInfoPrinter.h"
#include "GameFrameWork/GameContainer.h"
#include "utils/utils.h"
#include "utils/Debug.h"

/**
* constructor for the class
* @param container the main game container
* @param message the message to print
*/
GameInfoPrinter::GameInfoPrinter(GameContainer& container,
                 int posx,
                 int posy,
                 int heigh,
                 int width,std::string message):
                                                TextObject(container,posx,posy,
                                                            heigh,width,message)
{
    
}

/**
 * copy constructor
 * @param orig
 */
GameInfoPrinter::GameInfoPrinter(const GameInfoPrinter& orig):
                                                    TextObject(orig)
{
}

/**
* destructor for the class
*/
GameInfoPrinter::~GameInfoPrinter()
{
    
}

/**
* updates the object
*/
void GameInfoPrinter::update(unsigned long dt)
{
    std::string compound_msg;
    GameContainer& c=this->getContainer();
    long long time;
    if(c.getLifeTime()>c.getPlayTime()){
        time=((c.getLifeTime()-c.getPlayTime())/1000);
    }
    else{
        time=0;
    }
    int frame_rate=c.getFrameRate();
    compound_msg="Time:"+int2string(time)+"\nScore:"+int2string(c.getScore())+"\n";
    if(!time){
        compound_msg+="GAME IS OVER\n";
    }
    DEBUG(
            compound_msg+="fps:"+int2string(frame_rate)+"\n";
            )
    this->setMessage(compound_msg);
}
/**
* inform of events to the object
* @param e the event
*/
void GameInfoPrinter::handleEvent(SDL_Event *e)
{
    switch(e->type){
     case SDL_EventType::SDL_KEYDOWN:
        {
            //I only handle active debug for seeing fps
            if(e->key.keysym.sym==SDLK_o)
            {
                DEBUG(std::cout<<"pressing o"<<std::endl;);
                Debug::debugButtonPressed();
            }
            break;
        }
    }
}