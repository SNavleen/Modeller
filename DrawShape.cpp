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
#include "Vector3D.h"

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
    glColor3f(this->red,this->green,this->blue);
	if(modelType == "Cube"){
		drawCube();
	}
	if(modelType == "Sphere"){
		drawSphere();
	}
	if(modelType == "Cone"){
		drawCone();
	}
	if(modelType == "Torus"){
		drawTorus();
	}
	if(modelType == "Teapot"){
		drawTeapot();
	}
}
//code where we add what the node will do when moving up the tree
void DrawShape::nodeSpecificCodeUp(){}

void DrawShape::drawWireFrame(){
  printf("drawing the wire frame\n");
  glColor3f(0.0f,1.0f,0.0f);
  printf("going to draw the wireframe of the cube\n");
  double minX=-1,minY=-1,minZ=-1;
  double maxX=1,maxY=1,maxZ=1;
  if(modelType == "Cube"){
  }else if(modelType == "Teapot"){
    minX=-1.5;minY=-1;minZ=-1;
    maxX=1.5;maxY=1;maxZ=1;
  }else if(modelType == "Cone"){
    minX=-0.5;minY=-0.5;minZ=-0;
    maxX=0.5;maxY=0.5;maxZ=1;
  }else if(modelType == "Torus"){
    minX=-1.2,minY=-1.2,minZ=-0.5;
    maxX=1.2,maxY=1.2,maxZ=0.5;
  }
  // get min value
  Vector3D v1 = Vector3D(maxX,maxY,maxZ);
  Vector3D v2 = Vector3D(maxX,minY,maxZ);
  Vector3D v3 = Vector3D(minX,minY,maxZ);
  Vector3D v4 = Vector3D(minX,maxY,maxZ);
  Vector3D v5 = Vector3D(maxX,maxY,minZ);
  Vector3D v6 = Vector3D(maxX,minY,minZ);
  Vector3D v7 = Vector3D(minX,minY,minZ);
  Vector3D v8 = Vector3D(minX,maxY,minZ);

  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

  glBegin(GL_POLYGON); // begin drawing
    glVertex3f(v1.x,v1.y,v1.z);
    glVertex3f(v2.x,v2.y,v2.z);
    glVertex3f(v3.x,v3.y,v3.z);
    glVertex3f(v4.x,v4.y,v4.z);
  glEnd();

  glBegin(GL_POLYGON); // begin drawing
    glVertex3f(v5.x,v5.y,v5.z);
    glVertex3f(v6.x,v6.y,v6.z);
    glVertex3f(v7.x,v7.y,v7.z);
    glVertex3f(v8.x,v8.y,v8.z);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(v1.x,v1.y,v1.z);
  glVertex3f(v5.x,v5.y,v5.z);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(v2.x,v2.y,v2.z);
  glVertex3f(v6.x,v6.y,v6.z);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(v3.x,v3.y,v3.z);
  glVertex3f(v7.x,v7.y,v7.z);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(v4.x,v4.y,v4.z);
  glVertex3f(v8.x,v8.y,v8.z);
  glEnd();

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

/*DrawShape lighting();*/
void DrawShape::lighting(){
	float amb[4] = {1, 1, 1, 1};
	float diff[4] = {1, 1, 1, 1};
	float spec[4] = {1, 1, 1, 1};
	float light_pos[] = {0,150,0,1.0};
	float light_pos2[] = {100,150,100,1.0};


	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	glLightf(GL_LIGHT0, GL_SHININESS, 100);

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
	glLightf(GL_LIGHT1, GL_SHININESS, 100);
}
/*DrawShape material();*/
void DrawShape::material(){
	float mat_ambient[4] ={ 0.0f,0.05f,0.0f,1.0f };
	float mat_diffuse[4] ={ 0.4f,0.5f,0.4f,1.0f};
	float mat_specular[4] ={0.04f,0.7f,0.04f,1.0f };
	float shine =  10.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}
//Private

/*DrawShape drawCube();*/
void DrawShape::drawCube(){
	glutSolidCube(1);
}
/*DrawShape drawSphere();*/
void DrawShape::drawSphere(){
	glutSolidSphere(1, 10, 10);
}
/*DrawShape drawCone();*/
void DrawShape::drawCone(){
	glutSolidCone(0.5, 1, 20, 1);
}
/*DrawShape drawTorus();*/
void DrawShape::drawTorus(){
	glutSolidTorus(0.25, 1, 40, 40);
}
/*DrawShape drawTeapot();*/
void DrawShape::drawTeapot(){
	glutSolidTeapot(1);
}

