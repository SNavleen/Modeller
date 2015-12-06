#include "nodeGroup.h"
#include <stdio.h> //needed for printf command
#ifdef __APPLE__
#  	include <OpenGL/gl.h>
#  	include <OpenGL/glu.h>
#  	include <GLUT/glut.h>
#else
#  	include <GL/gl.h>
#  	include <GL/glu.h>
#   include <GL/freeglut.h>
#	include <windows.h>
#endif

NodeGroup::NodeGroup(){
	nodeType = group;
}

void NodeGroup::nodeSpecificCodeDown(){
	glPushMatrix();
}

void NodeGroup::nodeSpecificCodeUp(){
	glPopMatrix();
}


void rayIntersection(vector<Node*> listOfnodes, Vector3D *rayStart, Vector3D *rayEnd){
}
