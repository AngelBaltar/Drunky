/* 
 * File:   PointerObject.cpp
 * Author: angel
 * 
 * Created on 19 de julio de 2014, 14:01
 */

#include <SDL_image.h>

#include "GameFrameWork/PointerObject.h"
#include "GameFrameWork/GameContainer.h"
#include "utils/utils.h"

SDL_Texture* PointerObject::pointerImgs[2]={NULL,NULL};

const char* PointerObject::pointerImgsPath[2]={STR(RESOURCES)"/gfx/pointer.png",
                                STR(RESOURCES)"/gfx/pointer_dragged.png"
                                };


PointerObject::PointerObject(GameContainer& container,
                 int posx,
                 int posy,
                 int heigh,
                 int width):GameObject(container,posx,posy,heigh,width) {
}

PointerObject::PointerObject(const PointerObject& orig):
                        GameObject(orig.getContainer(),orig.getPosX(),orig.getPosY(),
                        orig.getHeigh(),orig.getWidth()) {
}

PointerObject::~PointerObject() {
}

/**
* draws the object
*/
void PointerObject::draw()
{
    int draw=0;
    SDL_Renderer * render=this->getContainer().getRenderer();
    if(this->isDragged()) {
        draw=1;
    }
    if(PointerObject::pointerImgs[draw]==NULL){
        PointerObject::pointerImgs[draw]=IMG_LoadTexture(render, PointerObject::pointerImgsPath[draw]);
    }
    SDL_Rect DestR;
    DestR.x = this->getPosX();
    DestR.y = this->getPosY();
    DestR.h=this->getHeigh();
    DestR.w=this->getWidth();
    SDL_RenderCopy(render, PointerObject::pointerImgs[draw], NULL, &DestR);
    
}

/**
* updates the object
*/
void PointerObject::update( unsigned long dt)
{
    //just keep the mouse
    int x,y;
    SDL_GetMouseState(&x,&y);
    if(this->getPosX()!=x){
        this->setPosX(x);
    }
    if(this->getPosY()!=y){
        this->setPosY(y);
    }
}

/**
* inform of events to the object
* @param e the event
*/
void PointerObject::handleEvent(SDL_Event *e)
{
    switch(e->type)
    {
        case SDL_EventType::SDL_MOUSEBUTTONDOWN:
        {
            
            this->setDragged(true);
            break;
        }
        case SDL_EventType::SDL_MOUSEBUTTONUP:
        {
          this->setDragged(false);
            break;
        }
        case SDL_EventType::SDL_MOUSEMOTION:
        {
            //DEBUG(std::cout<<"move:"<<e->motion.xrel<<" "<<e->motion.yrel<<std::endl;);
           this->setPosX(this->getPosX()+e->motion.xrel);
           this->setPosY(this->getPosY()+e->motion.yrel);
        }
        default:break;
    }
}

/**
* 
* @return the name of the object 
 * 
*/
std::string PointerObject::to_string()
{
    return "Pointer";
}