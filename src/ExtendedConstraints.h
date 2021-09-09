//
// Created by herolab on 9/8/21.
//

#ifndef TESTING_EXTENDEDCONSTRAINTS_H
#define TESTING_EXTENDEDCONSTRAINTS_H

#include <Eigen/Dense>
#include "GenericConstrants.h"
#include "MeshObjects.h"

class ExtendedConstraints : public GenericConstraints
{

    //===========================================================================

    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

    //! Constructor of GenericConstraints
    ExtendedConstraints(){};

    //! Destructor of GenericConstraints
    virtual ~ExtendedConstraints(){};


};
#endif //TESTING_EXTENDEDCONSTRAINTS_H
