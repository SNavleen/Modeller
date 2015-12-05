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
DrawShape::DrawShape(char *modelType, int red, int green, int blue){
	this->red = red/255;
	this->green = green/255;
	this->blue = blue/255;
	nodeType = model;
	this->modelType = modelType;
	isDrawable = true;
}

//Deconstructor
DrawShape::~DrawShape(){
}

//Public function

void DrawShape::drawAxis(){
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,100,0);

		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,100);
	glEnd();
}

void DrawShape::nodeSpecificCodeDown(){
	glColor3f(red, green, blue);
	if(modelType == "Cube"){
		glutSolidCube(1);
	}
	if(modelType == "Sphere"){
		glutSolidSphere(1, 12, 10);
	}
	if(modelType == "Teapot"){
		glutSolidTeapot(1);
	}
}

//Private

/*DrawShape drawCube();*/
void DrawShape::drawCube(){
	glutSolidCube(1);
}
/*DrawShape drawSphere();*/
void DrawShape::drawSphere(){
	glutSolidSphere(1, 12, 10);
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
	glutSolidTeapot(1);
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

