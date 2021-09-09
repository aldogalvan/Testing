//
// Created by aldo on 8/4/21.
//
#ifndef TESTING_TETMESH_H
#define TESTING_TETMESH_H

// INCLUDE EIGEN LIBRARY
#include <Eigen/Dense>

#include <vector>
#include "MeshObjects.h"
#include "GenericMesh.h"


class TetMesh : public GenericMesh
{

    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

public:

    //! Constructor of TetMesh
    TetMesh(Eigen::MatrixX3d vertices, Eigen::MatrixX2i links,
            Eigen::MatrixX3i faces, Eigen::MatrixX4i tetrahedra)
            {

        V_ = vertices;
        L_ = links;
        F_ = faces;
        T_ = tetrahedra;

            };

    //! Destructor of TetMesh
    ~TetMesh() {};

    //-----------------------------------------------------------------------
    // PUBLIC METHODS
    //-----------------------------------------------------------------------

public:

    //! This method builds the link objects
    void createNewLink(MeshVertex *a_v1, MeshVertex *a_v2, int a_idx);

    //! This method builds the triangle objects
    void createNewTriangle(MeshVertex *a_v1, MeshVertex *a_v2, MeshVertex *a_v3, int a_idx, bool isOutside);

    //! This method builds the tetrahedra objects
    void createNewTetrahedron(MeshVertex *a_v1, MeshVertex *a_v2, MeshVertex *a_v3, MeshVertex *a_v4, int a_idx);


    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //-----------------------------------------------------------------------

public:

    //!Number of links
    int h_numberEdges;

    //!Number of faces
    int h_numberTriangles;

    //!Number of tetrahedrons
    int h_numberTetrahedrons;

    //! List of links connecting the different nodes.
    std::vector<MeshEdge*> h_edgeList;

    //! List of tetrahedrons composing the mesh
    std::vector<MeshTetrahedron *> h_tetrahedraList;

    //! List of faces composing the mesh
    std::vector<MeshTriangle*> h_triangleList;

    //! Matrix representing indices of links
    Eigen::MatrixX2i L_;

    //! Matrix representing indices of faces
    Eigen::MatrixX3i F_;

    //! Matrix representing indices of tetrahedra
    Eigen::MatrixX4i T_;

};

#endif //TESTING_TETMESH_H
