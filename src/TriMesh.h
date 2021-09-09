//
// Created by herolab on 8/18/21.
//

#ifndef TESTING_TRIMESH_H
#define TESTING_TRIMESH_H

#include <Eigen/Dense>
#include <vector>

#include "GenericMesh.h"

using namespace std;

class TriMesh: public GenericMesh
{

    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

public:

    //! Constructor of TriMesh
    TriMesh(){};

    //! Destructor of TriMesh
    ~TriMesh(){};

    //-----------------------------------------------------------------------
    // PUBLIC METHODS
    //-----------------------------------------------------------------------

public:

    //! This method updates the mesh
    void updateMesh();

    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //-----------------------------------------------------------------------

public:

    //! Array of links
    Eigen::MatrixX2i L_;

    //! Array of faces
    Eigen::MatrixX3i F_;

};

#endif //TESTING_TRIMESH_H
