/* 
 * File:   GameContainer.cpp
 * Author: angel
 */

#include "GameFrameWork/GameContainer.h"

#include <iostream>
#include <stdlib.h>

#include "utils/utils.h"
#include "utils/Debug.h"

#include <SDL_image.h>
#include <SDL_mouse.h>

/**
 * empty constructor for the class
 */
GameContainer::GameContainer():_frameRate((unsigned int)(-1)),
                               _gameOver(false),
                                _total_time(0),
                                _score(0),
                                _game_started(false),
                                _screen(NULL),
                                _render(NULL),
                                _background(NULL),
                                _font(NULL),
                                _music(NULL)
                                
{
    
    this->_screen = SDL_CreateWindow("Drunky",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                            755, 600, SDL_WINDOW_SHOWN);
    
    this->_render = SDL_CreateRenderer(this->_screen, -1,
                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    this->_background= IMG_LoadTexture(this->_render, STR(RESOURCES) "/gfx/BackGround.jpg");
    this->_font = TTF_OpenFont(STR(RESOURCES)"/gfx/font.ttf", 40);
    //music here
    if (Mix_Init(MIX_INIT_MP3) == -1){
     exit(10);
    }
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 8192;
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
      exit(10);
    }
    Mix_AllocateChannels(2);
    this->_music = Mix_LoadMUS(STR(RESOURCES)"/sfx/OverdriveSexMachine.mp3");
    
    if(this->_screen==NULL 
         || this->_background==NULL 
         || this->_font==NULL
         || this->_render==NULL
         ||this->_music==NULL){
        std::cout<<"can't find basic Resources for the game, make sure you are in the correct path\n";
        std::cout<<"I'm searching at "<<STR(RESOURCES)<<"\n";
        exit(10);
    }
    if(Mix_PlayMusic(this->_music,-1)!=0){
        exit(12);
    }
    SDL_ShowCursor(0);
}

/**
 * empty destructor for the class
 */
GameContainer::~GameContainer() 
{
    SDL_free(this->_render);
    SDL_free(this->_background);
    SDL_free(this->_screen);
    TTF_CloseFont(this->_font);
    Mix_FreeMusic(this->_music);
    Mix_CloseAudio();
    for(auto s: (*this)){
        s->~GameObject();
    }
}

/**
 * called when button pressed, informs all game objects if necessary
 */
void GameContainer::handleEvent(SDL_Event *e)
{    
     switch(e->type)
        {
            case SDL_EventType::SDL_QUIT:
            {
                this->_gameOver=true;
                break;
            }
       }
    if(!this->_game_started){
        //no events right now
        return;
    }
    if(this->_total_time>this->getLifeTime()){
        return;//no more gaming
    }
    //inform all my objects
    for(auto s: (*this)){
        s->handleEvent(e);
    }
}

/**
* 
* @return true if the game is finished 
*/
bool GameContainer::gameOver() const
{
    return this->_gameOver;
}

/**
* @return the total playing time 
*/
unsigned long long GameContainer::getPlayTime() const
{
   return this->_total_time;
}

/**
* gets the life in miliseconds of this container
* @return a minute
*/
unsigned long long GameContainer::getLifeTime() const
{
    //1 minute
    return 60000;
    //return 4000;
    //return 60000*10;
}

/**
* @return the actual framerate of the game 
*/
unsigned int GameContainer::getFrameRate()const
{
    return this->_frameRate;
}

/**
* gets the score
* @return score
*/
unsigned int GameContainer::getScore() const
{
    return this->_score;
}

/**
* adds points to score
* @param pts
*/
void GameContainer::addToScore(unsigned int pts)
{
    this->_score+=pts;
}

/**
* @return the renderer for the game so everyone can draw itself
*/
SDL_Renderer * GameContainer::getRenderer() const
{
    return this->_render;
}

/**
* 
* @return a basic font to write things 
*/
TTF_Font * GameContainer::getFont() const
{
    return this->_font;
}

/*
 * calculate the next frame of the game
 * dt is the delta time from the last frame in ms
 */
void GameContainer::update(unsigned long dt)
{
    //frames I can produce in a second
    unsigned int fram=(dt?(1000/dt):(unsigned int)(-1));
    this->_frameRate+=fram;
    this->_frameRate/=2;
    //how long you have been playing
    if(this->_game_started){
        this->_total_time+=dt;
    }
    
    if(this->_total_time>this->getLifeTime()){
        if(Mix_PlayingMusic()){
            Mix_PauseMusic();
        }
        return;//no more gaming
    }
    //update all my objects
    for(auto s: (*this)){
        s->update(dt);
    }
}

/**
 * draw the game actual frame
 */
void GameContainer::draw()
{
    SDL_RenderClear(this->_render);
    SDL_RenderCopy(this->_render, this->_background, NULL, NULL);
    
    //draw all my objects
    for(auto s: (*this)){
        s->draw();
    }
    //Update Screen
    SDL_RenderPresent(this->_render);
}

 /**
* adds a new object to the container
* @param obj the object to add
* @return the container again
*/
GameContainer& GameContainer::operator+=(GameObject& obj)
{
    this->_objectsList.push_back(&obj);
    return (*this);
}

 /**
* @return an iterator 
*/
GameContainer::iterator GameContainer::begin()
{
   return this->_objectsList.begin();
}

/**
* 
* @return the end iterator
*/
GameContainer::iterator GameContainer::end()
{
   return this->_objectsList.end();
}

/**
* @return the start const iterator 
*/
GameContainer::const_iterator GameContainer::begin() const
{
    return this->_objectsList.begin();
}

/**
* 
* @return the end const iterator
*/
GameContainer::const_iterator GameContainer::end() const
{
    return this->_objectsList.end();
}

/**
* 
* @return true if game is initialized and playing 
*/
bool GameContainer::isGameStarted()const
{
    return this->_game_started;
}

/**
* all initialized, starts the game
*/
void GameContainer::startGame()
{
    this->_game_started=true;
}