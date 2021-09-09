//
// Created by herolab on 9/8/21.
//

#ifndef TESTING_GENERICMESH_H
#define TESTING_GENERICMESH_H

//INCLUDE EIGEN LIBRARY
#include <Eigen/Dense>

#include "MeshObjects.h"
#include <vector>

//===========================================================================

class GenericMesh
{

    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

public:

    //! Constructor of GenericMesh
    GenericMesh(){};

    //! Destructor of GenericMesh
    ~GenericMesh(){};

    //-----------------------------------------------------------------------
    // PUBLIC METHODS
    //-----------------------------------------------------------------------

    //! This method builds the vertex objects
    void buildMeshVertices(Eigen::MatrixX3d* vertices);

    //! This method builds a vertex object
    void createNewVertex(Eigen::Vector3d a_pos, int a_idx);

public:

    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS
    //-----------------------------------------------------------------------

    //!Number of vertices
    int h_numberVertices;

    //! List of nodes composing the skeleton.
    std::vector<MeshVertex*> h_vertexList;

    //! Matrix representing vertex positions
    Eigen::MatrixX3d V_;

};

#endif //TESTING_GENERICMESH_H
