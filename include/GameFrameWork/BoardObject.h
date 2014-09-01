/* 
 * File:   GameBoard.h
 * Author: angel
 *
 */

#ifndef BOARDOBJECT_H
#define	BOARDOBJECT_H
#include <vector>
#include "GameFrameWork/GameObject.h"
#include "GameObject.h"
#include <SDL_mixer.h>

class GameObject;
class BoardObject :public GameObject{
public:
    
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
    BoardObject(GameContainer& container,
                 int posx,
                 int posy,
                 int heigh,
                 int width,
                 int yLength,
                 int xLength);
    
    /**
     * main destructor for the class
     */
    virtual ~BoardObject();
    
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
    * returns true if the object can go down
    * @param y
    * @param x
    * @return 
    */
    bool canFallDown(GameObject *obj);
    
    /**
     * gets the center position x for a object
     * @param obj
     * @return 
     */
     int getCenterX(GameObject *obj);
    
    /**
     * gets the center position y for a object
     * @param obj
     * @return 
     */
     int getCenterY(GameObject *obj);
     
     /**
      * gets the neighbor of object
      * @param obj
      * @param delta_y -1 or +1
      * @param delta_x -1 or +1
      * @return 
      */
     GameObject* getNeighbor(GameObject *obj,int delta_y,int delta_x);
    
private:
     GameObject ** _board;
     int _yLength;
     int _xLength;
     int _kill_timer;
     std::vector<GameObject*> _lines;
     
     static const char* sound_effects_path[3];
     static Mix_Chunk* sound_effecs[3];
     
    /**
     * private copy constructor
     * @param orig
     * @return 
     */
    BoardObject(const BoardObject& orig);
    
    /**
     * gets the x pos in the board
     * @param obj
     * @return 
     */
     int getObjectPosX(GameObject *obj);
    
    /**
     * gets the y pos in thye board
     * @param obj
     * @return 
     */
     int getObjectPosY(GameObject *obj);
    
    /**
     * index the y coordinate of the board
     * @param y the y coordinate
     * @return the entire row for the y coordinate
     */
    GameObject ** operator[](const  int y)const;
    
    /**
     * 
     * @return true if there are empty objects in the board 
     */
    bool emptyObjs();
    
    /**
     * gets the lines with x y in the middle of the stencil
     * @param y
     * @param x
     */
    void getLines(int y,int x);
    
    /**
     * @return the actual lines on the board 
     */
    void getLines() ;
    
    /**
     * updates null the object in the board
     */
    void updateEmptyDrink(GameObject*obj, int y, int x, unsigned long dt);
    
    /**
     * updates non null the object in the board
     */
    void updateNonEmptyDrink(GameObject*obj, int y, int x, unsigned long dt);
    
    /**
     * updates dead the object in the board
     */
    void updateDeadDrink(GameObject*obj, int y, int x,unsigned  long dt);
  
};

#endif	/* GAMEBOARD_H */

