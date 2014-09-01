/* 
 * File:   drinkObject.h
 * Author: angel
 *
 * Created on 3 de julio de 2014, 14:33
 */

#ifndef DRINKOBJECT_H
#define	DRINKOBJECT_H

#include "GameFrameWork/GameObject.h"


class BoardObject;
class DrinkObject: public GameObject {
public:
    
    typedef enum{
        noneDrink=0,
        redDrink=1,
        blueDrink=2,
        greenDrink=3,
        yellowDrink=4,
        purpleDrink=5
    } DrinkType;
    
    /**
     * create a Drink into a board
     * @param board the board
     * @param posx x position
     * @param posy y position
     * @param heigh
     * @param width 
     * @param type Drink type
     */
    DrinkObject(BoardObject& board,
                unsigned int posx,
                unsigned int posy,DrinkType type);
    
    /**
     * copy constructor
     * @param orig copy from
     */
    DrinkObject(const DrinkObject& orig);
    
    /**
     * main destructor for the class
     */
    virtual ~DrinkObject();
    
    /**
     * 
     * @return the type of this Drink
     */
    DrinkType getType() const;
    
    /**
     * sets the x position
     * @param x position
     */
    void setPosX(unsigned int x);
    
    /**
     * sets the y position
     * @param y position
     */
    void setPosY(unsigned int y);
    
    /**
    * draws the object
    */
    void draw();
    
    /**
     * updates the object
     */
    void update(unsigned long dt);
    
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
    
    /**
    * @return if the Drink is empty
    */
    bool isEmpty()const ;
     
    /**
     * game object equal
     * @param obj
     * @return 
     */
    bool operator==(const DrinkObject &obj) const;
    
    /**
     * compare objects with Drinks
     * @param obj
     * @return 
     */
    bool operator==(const GameObject &obj) const;
    
    /**
    * assignament for objects
    * @param obj
    * @return 
    */
    DrinkObject& operator=(const DrinkObject& obj);
private:
    BoardObject& _board;
    DrinkObject::DrinkType _type;
    double _step;
    int _delta_x;
    int _delta_y;
    bool _draggedByNeighbor;
    
    static SDL_Texture* drinkImgs[6];
    static const char* getImgsPath[6];
};

#endif	/* DRINKOBJECT_H */

