//
// Created by herolab on 9/8/21.
//

#include "GenericMesh.h"

void GenericMesh::buildMeshVertices(Eigen::MatrixX3d* vertices)
{

    h_numberVertices = vertices->size();

    for (int i = 0 ; i < h_numberVertices; i++)
    {
        Eigen::Vector3d pos = vertices->row( i );
        createNewVertex(pos , i);
    }

}

void GenericMesh::createNewVertex(Eigen::Vector3d a_pos, int i)
{

    MeshVertex* a_vertex = new MeshVertex( a_pos , i);
    h_vertexList[i] = a_vertex;

}