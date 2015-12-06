
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

#include "node.h"
#include <stdio.h>

Node::Node(){	//constructor
	ID = getID();
	nodeType = root; //base class will be only really our root node, so lets do that
	isDrawable = false;
	children = new vector<Node*>();
	parent = 0;
	currentChild = 0;
}

//==================================================================
//function which does all the heavy lifting
void Node::draw(){
	nodeSpecificCodeDown();

	//recursively call our children
	const int numberOfChildren = children->size();
	if (numberOfChildren > 0){
		for (int i = 0; i < numberOfChildren; i++){
			children->at(i)->draw();
		}
	}

	//we are exiting the node, so execute the commands
	//ie. pop matrix, etc.
	nodeSpecificCodeUp();
}


//====================================================================
//FUNCTION THAT DOES THE ACTUAL STUFF IN
//DERIVED CLASSES

//TO BE OVERRIDDEN IN CHILD CLASSES AS NEEDED
//code where we add what the node will do when moving down the tree
void Node::nodeSpecificCodeDown(){}

//code where we add what the node will do when moving up the tree
void Node::nodeSpecificCodeUp(){}

// code where it draws the wireframe of the object being selected
void Node::drawWireFrame(){}

// handle the ray intersection
void Node::rayIntersection(vector<Node*> *listOfnodes, vector<double> *listOfDistances, Vector3D *rayStart, Vector3D *rayEnd){
  printf("  inside the ray intersection for the node. going to run it for all the children\n");
  for(int i =0; i < this->children->size(); i++){
    this->children->at(i)->rayIntersection(listOfnodes, listOfDistances,rayStart, rayEnd);
  }
  if(this->children->size()==0) printf("  there are no children\n");
  printf("  done for this node, going up the scene graph\n");
}

