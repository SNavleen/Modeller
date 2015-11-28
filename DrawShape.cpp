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
DrawShape::DrawShape(){
}

//Deconstructor
DrawShape::~DrawShape(){
}

//Public function

/*DrawShape drawCube();*/
void DrawShape::drawCube(){
}
/*DrawShape drawSphere();*/
void DrawShape::drawSphere(){
}
/*DrawShape drawCone();*/
void DrawShape::drawCone(){
}
/*DrawShape drawCylinder();*/
void DrawShape::drawCylinder(){
}
/*DrawShape drawTorus();*/
void DrawShape::drawTorus(){
}
/*DrawShape drawTeapot();*/
void DrawShape::drawTeapot(){
}
/*DrawShape drawTetrahedron();*/
void DrawShape::drawTetrahedron(){
}
/*DrawShape drawOctahedron();*/
void DrawShape::drawOctahedron(){
}
/*DrawShape drawDodecahedron();*/
void DrawShape::drawDodecahedron(){
}
/*DrawShape drawIcosahedron();*/
void DrawShape::drawIcosahedron(){
}

