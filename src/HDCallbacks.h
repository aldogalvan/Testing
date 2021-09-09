//
// Created by herolab on 9/9/21.
//

#ifndef TESTING_HDCALLBACKS_H
#define TESTING_HDCALLBACKS_H

// INCLUDE HD LIBRARIES
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>

// INCLUDE EIGEN
#include <Eigen/Dense>


class HDCallbacks
{
    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

public:

    //! Constructor of HDCallbacks
    HDCallbacks()
    {
        initializeHD();
    }

    //! Destructor of HDCallbacks
    ~HDCallbacks();

    //-----------------------------------------------------------------------
    // PUBLIC METHODS
    //-----------------------------------------------------------------------

public:

    //! This function initiates the haptic device
    void initializeHD();

    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS
    //-----------------------------------------------------------------------

public:

    static HHD hHD;

    static HDSchedulerHandle hUpdateDeviceCallback;

};

#endif //TESTING_HDCALLBACKS_H
