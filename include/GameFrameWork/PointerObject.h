/* 
 * File:   PointerObject.h
 * Author: angel
 *
 * Created on 19 de julio de 2014, 14:01
 */

#ifndef POINTEROBJECT_H
#define	POINTEROBJECT_H

#include "GameFrameWork/GameObject.h"

class PointerObject:public GameObject {
public:
    PointerObject(GameContainer& container,
                 int posx,
                 int posy,
                 int heigh,
                 int width);
    PointerObject(const PointerObject& orig);
    virtual ~PointerObject();
    
    
    /**
     * draws the object
     */
    void draw();
    
    /**
     * updates the object
     */
    void update( unsigned long dt);
    
    /**
     * inform of events to the object
     * @param e the event
     */
    void handleEvent(SDL_Event *e);
    
    /**
     * 
     * @return the name of the object 
     */
    std::string to_string();
    
    
private:

    
    static SDL_Texture* pointerImgs[2];
    static const char* pointerImgsPath[2];
};

#endif	/* POINTEROBJECT_H */

