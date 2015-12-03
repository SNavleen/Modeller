#ifndef __NODEMODEL_H__	//guard against cyclic dependancy
#define __NODEMODEL_H__

#include "node.h"
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

class NodeModel:public Node{
	public:
		NodeModel(char *modelType);	//constructor

		virtual void nodeSpecificCodeDown();

	private:
		char *modelType;
};

#endif