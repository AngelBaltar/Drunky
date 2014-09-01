/* 
 * File:   GameFactory.cpp
 * Author: angel
 * 
 */

#include <math.h>
#include <iostream>

#include "GameFrameWork/GameFactory.h"
#include "GameFrameWork/GameContainer.h"
#include "GameFrameWork/GameInfoPrinter.h"
#include "GameFrameWork/DrinkObject.h"
#include "GameFrameWork/BoardObject.h"
#include "utils/Debug.h"
#include "GameFrameWork/PointerObject.h"

/**
 * creates and initializes the game
 * @return the game
 */
GameContainer* GameFactory::createGame()
{
    GameContainer *game=new GameContainer();
    GameInfoPrinter *printer __attribute__((unused));
    printer=new GameInfoPrinter(*game,40,385,100,300,"");
    BoardObject * board __attribute__((unused));
    board=new BoardObject(*game,310,80,340,340,8,8);
    PointerObject * pointer __attribute__((unused));
    pointer=new PointerObject(*game,0,0,20,20);
    unsigned int seed=SDL_GetTicks();
    srandom(seed);
    return game;
}

/**
* 
* @return a random generated drink
*/
DrinkObject* GameFactory::createRandomDrink(BoardObject &board)
{
    static const  DrinkObject::DrinkType 
                random_types[5]={DrinkObject::blueDrink,
                                    DrinkObject::greenDrink,
                                    DrinkObject::redDrink,
                                    DrinkObject::yellowDrink,
                                    DrinkObject::purpleDrink
                                };
    
    DrinkObject::DrinkType type=random_types[random()%5];
    DrinkObject * drink=new DrinkObject(board,0,0,type);
    DEBUG(
      if(drink->isEmpty()){
        std::cout<<"this drink creation is wrong\n";
    });
    return drink;
}

/**
* creates a empty drink
* @return 
*/
DrinkObject* GameFactory::createEmptyDrink(BoardObject &board)
{
    DrinkObject * drink=new DrinkObject(board,0,0,DrinkObject::noneDrink);
    return drink;
}