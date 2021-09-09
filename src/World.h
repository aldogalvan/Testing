//
// Created by herolab on 9/8/21.
//

#ifndef TESTING_WORLD_H
#define TESTING_WORLD_H


// INCLUDE EIGEN LIBRARY
#include <Eigen/Dense>

// INCLUDE STD
#include <list>

#include "GenericObject.h"

//===========================================================================

class World
{
    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

public:

    //! Constructor of World
    World();

    //! Destructor of World
    ~World();

    //-----------------------------------------------------------------------
    // PUBLIC METHODS
    //-----------------------------------------------------------------------

public:

    //! This method sets the scheduler for the world
    void setScheduler();

    //! This method renders all objects in this world graphically
    void renderWorldGraphics();

    //! This method renders all objects in this world haptically
    void renderWorldHaptics();

    //! This method computes collisions between all objects in the world
    void computeWorldCollisions();

    //! This method adds a generic object to the world
    void addGenericObject();

    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS
    //-----------------------------------------------------------------------

public:

    //! The list of generic objects making up the world
    std::list<GenericObject*> m_objects;

    //! The list of tool objects / haptic devices making up the world
    std::list<GenericObject*> m_tools;



};

#endif //TESTING_WORLD_H
