//
// Created by aldo on 8/4/21.
//

#include "TetMesh.h"

/*
 * This method loads a file
 */

void TetMesh::loadFromFileVTU(const char *a_filename)
{

    //creates the reader and loads the grid
    vtkSmartPointer<vtkXMLUnstructuredGridReader> reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    reader->SetFileName(a_filename);
    reader->Update();

    //create the grid
    h_grid = reader->GetOutput();

    //builds the mesh objects from structure
    buildTetMeshVTU();

}

/*
 * These methods build the mesh objects
 */

void TetMesh::buildTetMeshVTU()
{
    h_grid->RemoveGhostCells();
    vtkCellTypes* type_list = vtkCellTypes::New();
    h_grid->GetCellTypes(type_list);
    h_grid->BuildLinks();

    //vtkIdType num_types = type_list->GetNumberOfTypes();

    // Initiate iterator for mesh
    vtkSmartPointer<vtkCellIterator> it = h_grid->NewCellIterator();

    it->InitTraversal();

    while(it->IsDoneWithTraversal())
    {


    }

}

/*
 * These methods add new objects to the mesh and store them in
 * a vector
 */
void TetMesh::createNewVertex(Eigen::Vector3d a_pos, int i)
{

    MeshVertex* a_vertex = new MeshVertex( a_pos , i);
    h_vertexList[i] = a_vertex;

}

void TetMesh::createNewLink(MeshVertex* a_v1, MeshVertex* a_v2, int i )
{

    MeshEdge* a_edge = new MeshEdge( a_v1 , a_v2, i);
    h_edgeList[i] = a_edge;

}

void TetMesh::createNewTriangle(MeshVertex* a_v1, MeshVertex* a_v2, MeshVertex* a_v3, int i , bool isOutside)
{

    MeshTriangle* a_triangle = new MeshTriangle(a_v1, a_v2, a_v3, i , isOutside);
    h_triangleList[i] = a_triangle;

}

void TetMesh:: createNewTetrahedron(MeshVertex* a_v1, MeshVertex* a_v2, MeshVertex* a_v3, MeshVertex* a_v4, int i)
{

    MeshTetrahedron* a_tetrahedron = new MeshTetrahedron(a_v1, a_v2, a_v3, a_v4, i);
    h_tetrahedraList[i] = a_tetrahedron;

}

vtkSmartPointer<vtkActor> TetMesh::getActor()
{
    //creates the mapper used for actor
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(h_grid);

    // creates the actor used for rendering
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    return actor;
}
