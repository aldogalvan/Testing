//
// Created by herolab on 8/12/21.
//

#ifndef TESTING_GENERICOBJECT_H
#define TESTING_GENERICOBJECT_H

// INCLUDE EIGEN LIBRARY
#include <Eigen/Dense>

#include "GenericMesh.h"

//===========================================================================
class GenericObject
{
    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

public:

    //! Constructor of GenericObject
    GenericObject(){};

    //! Destructor of GenericObject
    ~GenericObject(){};

    //-----------------------------------------------------------------------
    // PUBLIC METHODS
    //-----------------------------------------------------------------------

public:

    //! This method renders this object graphically
    void renderGraphics();

    //! This method computes collisions between this object and others
    void computeCollisions();

public:

    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS
    //-----------------------------------------------------------------------

    //! The mesh representing the surface of the object (NULL IF NONE)
    GenericMesh* surfaceMesh;

    //! The mesh representing the volume of the object (NULL IF NONE)
    GenericMesh* volumetricMesh;


};

#endif //TESTING_GENERICOBJECT_H
