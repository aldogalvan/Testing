//
// Created by aldo on 8/4/21.
//

#include "TetMesh.h"

/*
 * These methods add new objects to the mesh and store them in
 * a vector
 */

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

