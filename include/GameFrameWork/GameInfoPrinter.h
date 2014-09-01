/* 
 * File:   GameInfoPrinter.h
 * Author: angel
 *
 * Created on 2 de julio de 2014, 19:28
 */

#ifndef GAMEINFOPRINTER_H
#define	GAMEINFOPRINTER_H

#include "GameFrameWork/TextObject.h"


class GameInfoPrinter: public TextObject {
public:
    /**
     * constructor for the class
     * @param container the main game container
     * @param message the message to print
     */
    GameInfoPrinter(GameContainer& container,
                 int posx,
                 int posy,
                 int heigh,
                 int width,std::string message);
    
    /**
     * copy constructor
     * @param orig
     */
    GameInfoPrinter(const GameInfoPrinter& orig);
    
    /**
     * destructor for the class
     */
    virtual ~GameInfoPrinter();
    
    /**
     * updates the object
     */
    void update( unsigned long dt);
    
    /**
     * inform of events to the object
     * @param e the event
     */
    void handleEvent(SDL_Event *e);
    
private:

};

#endif	/* GAMEINFOPRINTER_H */

