//
// Created by herolab on 8/18/21.
//

#ifndef TESTING_TOOLOBJECT_H
#define TESTING_TOOLOBJECT_H

#include <Eigen/Dense>
#include "GenericObject.h"

//===========================================================================

class ToolObject : public GenericObject
{
    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

    public:

        //! Constructor of ToolObject
        ToolObject(){};

        //! Destructor of ToolObject
        ~ToolObject(){};

    //-----------------------------------------------------------------------
    // PUBLIC METHODS
    //-----------------------------------------------------------------------

    public:

        //! This method initiates the haptic device communication
        void initiateHapticDevice();

        //! This method returns haptic values
        void getHapticData();

        //! This method return graphical values
        void getGraphicsData();

        //! This method computes return force
        void updateHapticForce();


    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS
    //-----------------------------------------------------------------------





};

#endif //TESTING_TOOLOBJECT_H
