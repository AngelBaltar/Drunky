/* 
 * File:   GameObject.h
 * Author: angel
 *
 */

#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H
#include <string>
#include <SDL.h>


class GameContainer;

class GameObject {
public:
    /*
     * main constructor for the class
     */
    GameObject(GameContainer& container,
                 int posx,
                 int posy,
                 int heigh,
                 int width);
    
    /*
    * constructor for the class without a container
    */
    GameObject( int posx,
                 int posy,
                 int heigh,
                 int width);
    
    /**
     * copy constructor for the class
     * @param orig
     */
    GameObject(const GameObject& orig);
    
    /**
     * destructor for the class
     */
    virtual ~GameObject();
    
    /*
     * gets the container of the object
     */
    GameContainer& getContainer() const ;
    
    /**
     * 
     * @return the object x position 
     */
    int getPosX()const;
    
    /**
     * 
     * @return the object y position 
     */
    int getPosY()const;
    
    /**
     * the object width
     * @return 
     */
    int getWidth()const;
    
    /**
     * the object heigh
     * @return 
     */
    int getHeigh()const;
    
    /**
     * sets the x position
     * @param x position
     */
    virtual void setPosX(int x);
    
    /**
     * sets the y position
     * @param y position
     */
    virtual void setPosY(int y);
    
    
    /**
     * kills the object
     */
    virtual void die();
    
    /**
     * 
     * @return true if this object is dead 
     */
    bool isDead();
    
    
     /**
     * draws the object
     */
    virtual void draw()=0;
    
    /**
     * updates the object
     */
    virtual void update( unsigned long dt)=0;
    
    /**
     * inform of events to the object
     * @param e the event
     */
    virtual void handleEvent(SDL_Event *e)=0;
    
    /**
     * 
     * @return the name of the object 
     */
    virtual std::string to_string()=0;
    
    /**
     * 
     * @return true if the object is empty 
     */
    virtual bool isEmpty()const;
    
    /**
     * 
     * @return true if the object is being moved 
     */
    virtual bool isDragged()const;
    
    /**
     * sets the dragged attribute
     * @param dr
     */
    virtual void setDragged(bool dr);
    
    /**
     * game object equal
     * @param obj
     * @return 
     */
    virtual bool operator==(const GameObject &obj) const;
    
    /**
    * assignament for objects
    * @param obj
    * @return 
    */
    virtual GameObject& operator=(const GameObject& obj);
private:
    GameContainer* _container;
    int _posx;
    int _posy;
    int _heigh;
    int _width;
    bool _dead;
    bool _dragged;

};

#endif	/* GAMEOBJECT_H */

