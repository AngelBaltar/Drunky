/* 
 * File:   GameContainer.h
 * Author: angel
 */

#ifndef GAMECONTAINER_H
#define	GAMECONTAINER_H

#include <vector>
#include "GameFrameWork/GameObject.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class GameContainer {
public:
    /**
    * empty constructor for the class
    */
    GameContainer();
    
    /**
    * empty destructor for the class
    */
    virtual ~GameContainer();
    
    /**
    * called when button pressed, informs all game objects if necessary
    */
    void handleEvent(SDL_Event *e);
    
    /*
    * calculate the next frame of the game
    * dt is the delta time from the last frame in ms
    */
    void update(unsigned long dt);
    
    /**
    * draw the game actual frame
    */
    void draw();
    
    /**
     * 
     * @return true if the game is finished 
     */
    bool gameOver() const;
    
    /**
     * 
     * @return the total playing time 
     */
    unsigned long long getPlayTime() const;
    
    /**
     * gets the life in miliseconds of this container
     * @return a minute
     */
    unsigned long long getLifeTime() const;
    
    /**
     * @return the actual framerate of the game 
     */
    unsigned int getFrameRate()const;
    
    /**
     * gets the score
     * @return score
     */
    unsigned int getScore()const;
    
    /**
     * adds points to score
     * @param pts
     */
    void addToScore(unsigned int pts);
    
    /**
     * @return the renderer for the game so everyone can draw itself
     */
    SDL_Renderer * getRenderer() const;
    
    /**
     * 
     * @return a basic font to write things 
     */
    TTF_Font * getFont() const;
    
    /**
     * 
     * @return true if game is initialized and playing 
     */
    bool isGameStarted()const;
    
    /**
     * all initialized, starts the game
     */
    void startGame();
    
    /**
     * adds a new object to the container
     * @param obj the object to add
     * @return the container again
     */
    GameContainer& operator+=(GameObject& obj);
    
    
    
    typedef std::vector<GameObject*>::iterator iterator;
    typedef std::vector<GameObject*>::const_iterator const_iterator;
        
    /**
    * @return the start iterator 
    */
    GameContainer::iterator begin();

    /**
    * 
    * @return the end iterator
    */
    GameContainer::iterator end();
    
    /**
    * @return the start const iterator 
    */
    GameContainer::const_iterator begin() const;

    /**
    * 
    * @return the end const iterator
    */
    GameContainer::const_iterator end() const;

    
private:
    //TODO REMEMBER TO IMPLEMENT DESTRUCTORS AND CONSTRUCTORS FOR NEW ATTRIBUTES
    unsigned int _frameRate;
    bool _gameOver;
    unsigned long long _total_time;
    unsigned int _score;
    bool _game_started;
    
    SDL_Window* _screen;
    SDL_Renderer * _render;
    SDL_Texture* _background;   
    TTF_Font *_font;
    Mix_Music* _music;
    
    std::vector<GameObject*> _objectsList;

};

#endif	/* GAMECONTAINER_H */

