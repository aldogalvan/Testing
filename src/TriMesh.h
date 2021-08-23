//
// Created by herolab on 8/18/21.
//

#ifndef TESTING_TRIMESH_H
#define TESTING_TRIMESH_H

#include <Eigen/Dense>
#include <vector>

// INCLUDE IGL
#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOBJ.h>

using namespace std;

class TriMesh {

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

    //! This method loads the mesh from a file
    void loadFromFileIGL(const char *a_filename , igl::opengl::glfw::Viewer* viewer);

    //! This method renders the mesh
    void render(igl::opengl::glfw::Viewer* viewer);

    //! This method updates the mesh
    void updateMesh();

    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //-----------------------------------------------------------------------

public:

    //! Array of vertices
    Eigen::MatrixX3d V;

    //! Array of faces
    Eigen::MatrixX3i F;

};

#endif //TESTING_TRIMESH_H
