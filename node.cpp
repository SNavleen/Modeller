
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

Node::Node(){//constructor
  ID = getID();
  nodeType = root; //base class will be only really our root node, so lets do that
  isDrawable = false;
  children = new vector<Node*>();
  parent = 0;
  currentChild = 0;
  isSelected = false;
}

void printModelMatrix(){
  double matModelView[16];
  glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);

  printf("printing the modelview matrix in the draw shape\n");
  for(int i =0; i < 4; i++){
    for(int j=0; j < 4; j++){
      printf("%f, ",matModelView[i+j*4]);
    }
    printf("\n");
  }
  printf("\n");
}



//==================================================================
//function which does all the heavy lifting
void Node::draw(){
  nodeSpecificCodeDown();

  printf("got down tot he node\n");

  printf("drawing self object\n");
  drawSelf();

  //recursively call our children
  const int numberOfChildren = children->size();
  if (numberOfChildren > 0){
    for (int i = 0; i < numberOfChildren; i++){
      printf("going to node at %i so going down a node\n", i);
      children->at(i)->draw();
    }
  }

  //we are exiting the node, so execute the commands
  //ie. pop matrix, etc.
  nodeSpecificCodeUp();

  printf("done node\n");
}


//====================================================================
//FUNCTION THAT DOES THE ACTUAL STUFF IN
//DERIVED CLASSES

//
void Node::drawSelf(){}

//TO BE OVERRIDDEN IN CHILD CLASSES AS NEEDED
//code where we add what the node will do when moving down the tree
void Node::nodeSpecificCodeDown(){}

//code where we add what the node will do when moving up the tree
void Node::nodeSpecificCodeUp(){}

// code where it draws the wireframe of the object being selected
void Node::drawWireFrame(){}

// handle the ray intersection
void Node::rayIntersection(vector<Node*> *listOfnodes, vector<double> *listOfDistances, int mx,int my){
  /* printf("inside a node that is not a draw node, going to the children\n"); */
  /* printf("going to print the matrix before down\n"); */
  /* printModelMatrix(); */

  /* printf("  inside the ray intersection for the node. going to run it for all the children\n"); */
  this->nodeSpecificCodeDown();
  /* printf("going to print the matrix after down\n"); */
  /* printModelMatrix(); */

  for(int i =0; i < this->children->size(); i++){
    /* printf("going through the loop at i:%i\n",i); */
    this->children->at(i)->rayIntersection(listOfnodes, listOfDistances,mx,my);
  }

  /* printf("just came back, going to print the model matrix\n"); */
  /* printModelMatrix(); */

  this->nodeSpecificCodeUp();
  /* printf("printing model matrix after the code up\n"); */
  /* printModelMatrix(); */


  /* printf("going up a node\n"); */
  /* if(this->children->size()==0) printf("  there are no children\n"); */
  /* printf("  done for this node, going up the scene graph\n"); */
}

