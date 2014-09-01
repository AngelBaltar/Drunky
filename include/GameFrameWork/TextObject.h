/* 
 * File:   TextObject.h
 * Author: angel
 *
 */

#ifndef TEXTOBJECT_H
#define	TEXTOBJECT_H

#include <string>
#include "GameFrameWork/GameObject.h"

class GameContainer;
class TextObject :public GameObject{
public:
    /**
     * constructor for the class
     * @param container the container of the game
     * @param message the message we want to print
     */
    TextObject(GameContainer &container,
                unsigned int posx,
                unsigned int posy,
                unsigned int heigh,
                unsigned int width,std::string message);
    
    /**
     * copy constructor
     * @param orig
     */
    TextObject(const TextObject& orig);
    
    /**
     * destructor for the class
     */
    virtual ~TextObject();
    
    /**
     * @return the actual message
     */
    std::string getMessage()const ;
    
    /**
     * sets the message
     * @param str message to set
     */
    void setMessage(std::string str);
    
    /**
     * draws the object
     */
    virtual void draw();
        
    /**
     * updates the object
     */
    virtual void update(unsigned long dt)=0;
    
    /**
     * inform of events to the object
     * @param e the event
     */
    virtual void handleEvent(SDL_Event *e)=0;
    
    /**
     * 
     * @return the name of the object 
     */
    virtual std::string to_string();
   
    /**
    * assignament for objects
    * @param obj
    * @return 
    */
    virtual TextObject& operator=(const TextObject& obj);
    
private:
    std::string _message;
};

#endif	/* TEXTOBJECT_H */

