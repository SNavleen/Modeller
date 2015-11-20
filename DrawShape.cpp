#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/freeglut.h>
#   include <windows.h>
#endif

#include "DrawShape.h"
using namespace std;

//Constructors
DrawMesh::DrawMesh(){
}

//Deconstructor
DrawMesh::~DrawMesh(){
}

//Public function

/*DrawShape drawCube();*/
void DrawShape::drawCube(){
}
/*DrawShape drawSphere();*/
void drawSphere(){
}
/*DrawShape drawCone();*/
void drawCone(){
}
/*DrawShape drawCylinder();*/
void drawCylinder(){
}
/*DrawShape drawTorus();*/
void drawTorus(){
}
/*DrawShape drawTeapot();*/
void drawTeapot(){
}
/*DrawShape drawTetrahedron();*/
void drawTetrahedron(){
}
/*DrawShape drawOctahedron();*/
void drawOctahedron(){
}
/*DrawShape drawDodecahedron();*/
void drawDodecahedron(){
}
/*DrawShape drawIcosahedron();*/
void drawIcosahedron(){
}

