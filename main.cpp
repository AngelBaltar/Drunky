/* 
 * File:   main.cpp
 * Author: angel
 *
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>

#include <vector>
#include "utils/Debug.h"
#include "GameFrameWork/GameContainer.h"
#include "GameFrameWork/GameFactory.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/**
 * 
 * @param argc number of parameters
 * @param argv parameters to main
 * @return 0 on success
 */
int main(int argc, char **argv)
{
    
    SDL_Event event;
    if(TTF_Init()!=0){
        exit(1);
    }
    SDL_Init(SDL_INIT_EVERYTHING);
    //main container for the game
    GameContainer& container=*GameFactory::createGame();
    unsigned long long time=SDL_GetTicks();
    while(!container.gameOver()){
        //update the game sending the delta time
        container.update(SDL_GetTicks()-time);
        time=SDL_GetTicks();
        //draw the actual frame
        container.draw();
        // handle events
        while (SDL_PollEvent(&event)) {
         container.handleEvent(&event);
        }
    }
    SDL_Quit();
    return 0;
}