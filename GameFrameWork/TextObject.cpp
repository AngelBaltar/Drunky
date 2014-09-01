/* 
 * File:   TextObject.cpp
 * Author: angel
 * 
 */

#include "GameFrameWork/TextObject.h"
#include "GameFrameWork/GameContainer.h"
#include <iostream>

/**
* constructor for the class
* @param container the container of the game
* @param message the message we want to print
*/
TextObject::TextObject(GameContainer &container,
                unsigned int posx,
                unsigned int posy,
                unsigned int heigh,
                unsigned int width,
                std::string message):GameObject(container,posx,posy,heigh,width),
                                        _message(message)
{
    
}

/**
* copy constructor
* @param orig
*/
TextObject::TextObject(const TextObject& orig):GameObject(orig),
                                            _message(orig.getMessage())
{
    
}

/**
* destructor for the class
*/
TextObject::~TextObject()
{
    
}

/**
* @return the actual message
*/
std::string TextObject::getMessage()const 
{
    return this->_message;
}

/**
 * sets the message
 * @param str message to set
 */
void TextObject::setMessage(std::string str)
{
    this->_message=str;
}

/**
* draws the object
*/
void TextObject::draw()
{
    SDL_Surface *text;
    SDL_Color text_color = {0, 0, 255};
   
    SDL_Renderer *render=this->getContainer().getRenderer();
    TTF_Font * font=this->getContainer().getFont();
    
    // Write text to surface
    std::string line="";
    std::string mess=this->getMessage();
    unsigned int i=0;
    SDL_Rect DestR;
    DestR.x = this->getPosX();
    DestR.y = this->getPosY();
    DestR.h=TTF_FontHeight(font);
    DestR.w=0;
    while(i<mess.length()){
        if(mess[i]!='\n'){
            line+=mess[i];
        }
        else{
            text = TTF_RenderText_Blended(font,line.c_str(),text_color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(render, text);
            SDL_FreeSurface(text);
            int w,h;
            TTF_SizeText(font,line.c_str(),&w,&h);
            DestR.w=w;
            SDL_RenderCopy(render, texture, NULL, &DestR);
            DestR.y +=h;
            line="";
        }
        i++;
    }
    
}

/**
* 
* @return the name of the object 
*/
std::string TextObject::to_string()
{
    return "text";
}

/**
* assignament for objects
* @param obj
* @return 
*/
TextObject& TextObject::operator=(const TextObject& obj)
{
    GameObject::operator=(obj);
    this->_message=obj._message;
    return (*this);
}
