//
// Created by aldo on 8/4/21.
//

#ifndef TESTING_MESHOBJECTS_H
#define TESTING_MESHOBJECTS_H

#include <Eigen/Dense>
#include <set>

struct MeshVertex {

    MeshVertex( Eigen::Vector3d a_pos, int a_idx){

        pos0 = a_pos;
        pos = a_pos;
        idx = a_idx;

    }

    ~MeshVertex(){};

    Eigen::Vector3d pos0;
    Eigen::Vector3d pos;
    double mass = 1;
    int idx;
    bool isOutside;
    int collisionIdx;

};

struct MeshEdge{

    MeshEdge(MeshVertex* a_v1, MeshVertex* a_v2, int a_idx ){

        v1 = a_v1;
        v2 = a_v2;
        idx = a_idx;
        length0 = computeLength();

    }

    ~MeshEdge(){};

    MeshVertex* v1;
    MeshVertex* v2;
    double compStiffness = 1;
    double extStiffness = 1;
    int idx;
    double length0;
    double length;

    double computeLength(){
        length = (v1->pos - v2->pos).norm();
        return length;
    }

};

struct MeshTriangle{
    MeshTriangle(MeshVertex* a_v1, MeshVertex* a_v2, MeshVertex* a_v3, int a_idx , bool a_Outside){

        v1 = a_v1;
        v2 = a_v2;
        v3 = a_v3;
        idx = a_idx;
        area0 = computeArea();
        isOutside = a_Outside;

    }

    ~MeshTriangle(){};

    MeshVertex* v1;
    MeshVertex* v2;
    MeshVertex* v3;
    double compStiffness = 1;
    double extStiffness = 1;
    int idx;
    double area0;
    double area;
    int collisionIdx;
    bool isOutside;

    double computeArea(){
        area  = 0.5*(v2->pos - v1->pos).cross(v3->pos - v1->pos).norm();
        return area;
    }

};

struct MeshTetrahedron {
    MeshTetrahedron(MeshVertex* a_v1, MeshVertex* a_v2, MeshVertex* a_v3, MeshVertex* a_v4, int a_idx){
        v1 = a_v1;
        v2 = a_v2;
        v3 = a_v3;
        v4 = a_v4;
        centroid0 = computeCentroid();
        volume0 = computeVolume();
    }

    ~MeshTetrahedron(){};

    MeshVertex* v1;
    MeshVertex* v2;
    MeshVertex* v3;
    MeshVertex* v4;
    double compStiffness = 1;
    double extStiffness = 1;
    int idx;
    Eigen::Vector3d centroid0;
    Eigen::Vector3d centroid;
    double volume0;
    double volume;

    double computeVolume(){
        Eigen::Vector3d a = v2->pos - v1->pos;
        Eigen::Vector3d b = v3->pos - v1->pos;
        Eigen::Vector3d c = v4->pos - v1->pos;

        volume = 1/6*abs((a).cross(b).dot(c));
        return volume;
    }

    Eigen::Vector3d computeCentroid(){
        centroid = (v1->pos + v2->pos + v3->pos + v4->pos)/4;
        return centroid;
    }

};

struct SurfaceVertex {

    SurfaceVertex(Eigen::Vector3d a_pos, int a_idx){

        pos0 = a_pos;
        pos = a_pos;
        idx = a_idx;

    }

    ~SurfaceVertex();

    MeshTetrahedron* tetrahedron;
    Eigen::Vector3d pos0;
    Eigen::Vector3d pos;
    Eigen::Vector4d tetrahedronBary;
    int idx;


    void computeTetrahedronBary(){

        Eigen::Vector3d vap = pos0 - tetrahedron->v1->pos0;
        Eigen::Vector3d vbp = pos0 - tetrahedron->v2->pos0;
        Eigen::Vector3d vab = tetrahedron->v2->pos0 - tetrahedron->v1->pos0;
        Eigen::Vector3d vac = tetrahedron->v3->pos0 - tetrahedron->v1->pos0;
        Eigen::Vector3d vad = tetrahedron->v4->pos0 - tetrahedron->v1->pos0;
        Eigen::Vector3d vbc = tetrahedron->v3->pos0 - tetrahedron->v2->pos0;
        Eigen::Vector3d vbd = tetrahedron->v4->pos0 - tetrahedron->v2->pos0;

        double va = (vbp).cross(vbd).dot(vbc);
        double vb = (vap).cross(vac).dot(vbd);
        double vc = (vap).cross(vad).dot(vab);
        double vd = (vap).cross(vab).dot(vac);
        double v = 1 / ((vab).cross(vac).dot(vad));

        tetrahedronBary(0) = va*v; tetrahedronBary(1) = vb*v;
        tetrahedronBary(2) = vc*v; tetrahedronBary(3) = vd*v;

    }

    Eigen::Vector3d updatePosition(){

        Eigen::Vector3d a = tetrahedron->v1->pos;
        Eigen::Vector3d b = tetrahedron->v2->pos;
        Eigen::Vector3d c = tetrahedron->v3->pos;
        Eigen::Vector3d d = tetrahedron->v4->pos;

        Eigen::Vector3d newpos = tetrahedronBary(0)*a + tetrahedronBary(1)*b +
                tetrahedronBary(2)*c + tetrahedronBary(3)*d;

        pos = newpos;
        return pos;

    }


};

struct SurfaceTriangle {

    SurfaceTriangle( int a_idx, SurfaceVertex* a_v1, SurfaceVertex* a_v2, SurfaceVertex* a_v3, double a_area){

        idx = a_idx;
        v1 = a_v1;
        v2 = a_v2;
        v3 = a_v3;
        area = a_area;

    }

    ~SurfaceTriangle();

    int idx;
    SurfaceVertex* v1;
    SurfaceVertex* v2;
    SurfaceVertex* v3;
    double area;

};

#endif //TESTING_MESHOBJECTS_H
