//
// Created by herolab on 8/18/21.
//

#include "TriMesh.h"

/*
 * This method loads a file
 */

void TriMesh::loadFromFileIGL(std::string a_filename, igl::opengl::glfw::Viewer* viewer)
{
    // Load a mesh in OBJ format
    igl::readOBJ(a_filename, V, F);

   // Sets the mesh in the visualizer
   viewer->data().set_mesh(V, F);
}

/*
 * This method renders the mesh
 */

//! This method renders the mesh
void TriMesh::render(igl::opengl::glfw::Viewer* viewer)
{

}