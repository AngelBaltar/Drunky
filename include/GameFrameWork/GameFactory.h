/* 
 * File:   GameFactory.h
 * Author: angel
 *
 * Created on 3 de julio de 2014, 19:47
 */

#ifndef GAMEFACTORY_H
#define	GAMEFACTORY_H

#include "GameContainer.h"
#include "DrinkObject.h"


class GameContainer;
class DrinkObject;
class BoardObject;
namespace GameFactory {

    /**
     * creates and initializes the game
     * @return the game
     */
    GameContainer *createGame();
    
    /**
     * 
     * @return a random generated drink
     */
    DrinkObject *createRandomDrink(BoardObject &board);
    
    /**
    * creates a emoty drink
    * @return 
    */
   DrinkObject* createEmptyDrink(BoardObject &board);
    
}

#endif	/* GAMEFACTORY_H */

