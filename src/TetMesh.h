//
// Created by aldo on 8/4/21.
//
#ifndef TESTING_TETMESH_H
#define TESTING_TETMESH_H

#include <Eigen/Dense>
#include <vector>
#include "MeshObjects.h"
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGridCellIterator.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkCellTypes.h>

using namespace std;

class TetMesh {

    //-----------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //-----------------------------------------------------------------------

public:

    //! Constructor of TetMesh
    TetMesh() {};

    //! Destructor of TetMesh
    ~TetMesh() {};

public:
    //-----------------------------------------------------------------------
    // PUBLIC METHODS
    //-----------------------------------------------------------------------

    //! This method loads a file using VTK
    void loadFromFileVTU(const char * a_filename);

    //! This method builds the volumetric mesh from an unstructured mesh
    void buildTetMeshVTU();

    //! This method builds the vertex objects
    void createNewVertex(Eigen::Vector3d a_pos, int a_idx);

    //! This method builds the link objects
    void createNewLink(MeshVertex *a_v1, MeshVertex *a_v2, int a_idx);

    //! THis method builds the triangle objects
    void createNewTriangle(MeshVertex *a_v1, MeshVertex *a_v2, MeshVertex *a_v3, int a_idx, bool isOutside);

    //! This method builds the tetrahedra objects
    void createNewTetrahedron(MeshVertex *a_v1, MeshVertex *a_v2, MeshVertex *a_v3, MeshVertex *a_v4, int a_idx);

    //! This method returns the actor for visual rendering
    vtkSmartPointer<vtkActor> getActor();

    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //-----------------------------------------------------------------------

public:

    //! Pointer to the vtk object
    vtkSmartPointer<vtkUnstructuredGrid> h_grid;

    //!Number of vertices
    int h_numberVertices;

    //!Number of links
    int h_numberEdges;

    //!Number of faces
    int h_numberTriangles;

    //!Number of tetrahedrons
    int h_numberTetrahedrons;

    //! List of nodes composing the skeleton.
    vector<MeshVertex*> h_vertexList;

    //! List of links connecting the different nodes.
    vector<MeshEdge*> h_edgeList;

    //! List of tetrahedrons composing the mesh
    vector<MeshTetrahedron *> h_tetrahedraList;

    //! List of faces composing the mesh
    vector<MeshTriangle*> h_triangleList;

};

#endif //TESTING_TETMESH_H
