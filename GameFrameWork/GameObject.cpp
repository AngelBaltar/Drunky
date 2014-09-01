/* 
 * File:   GameObject.cpp
 * Author: angel
 * 
 */

#include "GameFrameWork/GameObject.h"
#include "GameFrameWork/GameContainer.h"
#include <iostream>

/*
* main constructor for the class
*/
GameObject::GameObject(GameContainer& container,
                int posx,
                int posy,
                int heigh,
                int width):_container(&container),
                                                 _posx(posx),
                                                 _posy(posy),
                                                 _heigh(heigh),
                                                 _width(width),
                                                 _dead(false),
                                                 _dragged(false)
{
    container+=(*this);
}


/*
* constructor for the class without a container
*/
GameObject::GameObject(int posx,
                int posy,
                int heigh,
                int width): _container(nullptr),
                                     _posx(posx),
                                     _posy(posy),
                                     _heigh(heigh),
                                     _width(width),
                                     _dead(false),
                                     _dragged(false)
{
   
}

/**
* copy constructor for the class
* @param orig
*/
GameObject::GameObject(const GameObject& orig):_container(orig._container),
                                               _posx(orig.getPosX()),
                                               _posy(orig.getPosY()),
                                               _heigh(orig.getHeigh()),
                                               _width(orig.getWidth()),
                                               _dead(orig._dead),
                                               _dragged(orig._dragged)
{
}

/**
* destructor for the class
*/
GameObject::~GameObject() {
}

/*
* gets the container of the object
*/
GameContainer& GameObject::getContainer() const
{
    return *this->_container;
}

/**
 * 
 * @return the object x position 
 */
int GameObject::getPosX()const
{
    return this->_posx;
}

/**
 * 
 * @return the object y position 
 */
int GameObject::getPosY()const
{
    return this->_posy;
}

/**
 * the object width
 * @return 
 */
int GameObject::getWidth()const
{
    return this->_width;
}

/**
 * the object heigh
 * @return 
 */
int GameObject::getHeigh()const
{
    return this->_heigh;
}

/**
 * sets the x position
 * @param x position
 */
void GameObject::setPosX(int x)
{
    this->_posx=x;
}

/**
 * sets the y position
 * @param y position
 */
void GameObject::setPosY(int y)
{
    this->_posy=y;
}

/**
* kills the object
*/
void GameObject::die()
{
    this->_dead=true;
}

/**
* 
* @return true if this object is dead 
*/
bool GameObject::isDead()
{
    return this->_dead;
}


/**
 * assignament for objects
 * @param obj
 * @return 
 */
GameObject& GameObject::operator=(const GameObject& obj)
{
    this->_container=obj._container;
    this->_dead=obj._dead;
    this->_heigh=obj._heigh;
    this->_posx=obj._posx;
    this->_posy=obj._posy;
    this->_width=obj._width;
    return (*this);
}

/**
* 
* @return true if the object is empty 
*/
bool GameObject::isEmpty() const
{
    return false;
}

/**
* 
* @return true if the object is being moved 
*/
bool GameObject::isDragged() const
{
    return this->_dragged;
}

/**
* sets the dragged attribute
* @param dr
*/
void GameObject::setDragged(bool dr)
{
    this->_dragged=dr;
}