#include "sceneGraph.h"
#include "node.h"
#include "Vector3D.h"
#include <stdio.h>

//temporary
#include "nodeTransform.h"
#include "DrawShape.h"

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



bool SceneGraph::isSelectednodeNull(){ return (selectedNode==NULL); }


void SceneGraph::selectnodeAtPos(int x, int y){
  if(selectedNode != NULL) selectedNode->isSelected = false; // make it so that if you attempt to select another node it will make the first one false

  vector<Node*> listOfnodes = vector<Node*>();
  vector<double> listOfIntersectionDistances = vector<double>();
  /* Node *curnodeLocal = rootNode;// go to the root node */
  /* printf("starting the for loop with all the children\n"); */
  // go to all the children checking if they had got the collision
  /* for(int i = 0; i < curnodeLocal->children->size(); i++){ */
    /* printf("going to the child at i:%i\n",i); */
    /* Node *node =  curnodeLocal->children->at(i); */
    /* node->rayIntersection(&listOfnodes,&listOfIntersectionDistances); */
  /* } */
  /* printf("done the selectnodeatpos\n\n"); */

  // reddid the recursion
  rootNode->rayIntersection(&listOfnodes, &listOfIntersectionDistances, x,y);

  /* printf("the size of the list of distances is %li\n",listOfIntersectionDistances.size()); */
  // go through the list to find the smallset element
  if(listOfIntersectionDistances.size()==0){
    selectedNode=NULL;
    /* printf("no Intersection\n"); */
    return;
  } // if there are no elements then just end the function
  /* printf("Intersection detected\n"); */
  int minDistanceIndex = 0; // this is the index which points to the node that is the closest to the screen
  for(int i = 1; i < listOfIntersectionDistances.size();i++){
    if(listOfIntersectionDistances.at(i) < listOfIntersectionDistances.at(minDistanceIndex) && listOfIntersectionDistances.at(i) > 0) minDistanceIndex = i;
  }

  // make the selected node equal to the node that is closest to the screen and intersects the ray
  selectedNode = listOfnodes.at(minDistanceIndex);
  selectedNode->isSelected = true;
  /* printf("the selected node is at a distance of %f\n\n\n",  listOfIntersectionDistances.at(minDistanceIndex)); */
}


SceneGraph::SceneGraph(){
  rootNode = new Node();
  currentNode = rootNode;
  selectedNode = NULL;
  startRayD = NULL;
  endRayD = NULL;
  /* useCustomSettings(); */
}

void SceneGraph::drawRay(){
  if(startRayD == NULL || endRayD == NULL) return;
  /* printf("drawing the ray at (%f,%f,%f) to (%f,%f,%f)\n", startRayD->x,startRayD->y,startRayD->z, endRayD->x,endRayD->y,endRayD->z); */
  glBegin(GL_LINES);
  glColor3f(1,0,0);
  glVertex3f(startRayD->x, startRayD->x, startRayD->z);
  glVertex3f(endRayD->x, endRayD->y, endRayD->z);
  glEnd();
}

void SceneGraph::useCustomSettings(){
  // this is just a plane to test if plane intersection is working
  DrawShape *plane = new DrawShape("Plane", 255,255, 255);
  rootNode->children->push_back(plane);


  // this is the transformed sphere
  /* DrawShape *drawSphere = new DrawShape("Sphere", 255,255,255); */
  /* NodeTransform * transformnode = new NodeTransform(Scale, Vector3D(2,2,2)); */
  /* NodeTransform * translatenode = new NodeTransform(Translate, Vector3D(5,0,0)); */
  /* translatenode->children->push_back(transformnode); */
  /* transformnode->children->push_back(drawSphere); */
  /* /1* rootNode->children->push_back(transformnode); *1/ */
  /* rootNode->children->push_back(translatenode); */
}
void SceneGraph::selectFirstnode()
{
  if(rootNode->children->size() == 0) return;
  selectedNode = rootNode->children->at(0);
  selectedNode->isSelected = true;
}

//Scene Graph Navigation
//resets the current node to the root of the graph
void SceneGraph::goToRoot(){
  currentNode = rootNode;
}

//moves to a child node i
void SceneGraph::goToChild(int i){
  if (i < currentNode->children->size() && i >= 0)
    currentNode = currentNode->children->at(i);
  else
    printf("child out of range\n");
}

void SceneGraph::goToParent(){
  if (currentNode->parent != 0)
    currentNode = currentNode->parent;
}

//inserts a child node into the current node
void SceneGraph::insertChildNodeHere(Node *node){
  node->parent = currentNode;
  currentNode->children->push_back(node);
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode(){
  if(selectedNode!=NULL){
    selectedNode->isSelected = false;
    Node *parentSelectedNode = selectedNode->parent;

    vector<Node*> *parentsChildren = parentSelectedNode->children;
    vector<Node*> *selectedNodesChildren = selectedNode->children;

    //find the selected nodes index
    int indexOfSelectedNode = 0;
    for(indexOfSelectedNode = 0; indexOfSelectedNode < parentSelectedNode->children->size(); indexOfSelectedNode++){
      if(parentSelectedNode->children->at(indexOfSelectedNode) == selectedNode) break;
    }

    //Delete the selected node
    parentSelectedNode->children->erase(parentsChildren->begin()+indexOfSelectedNode);

    //Put all the children of the selected not to the parent
    for(int i = 0; i < selectedNodesChildren->size(); i++){
      parentSelectedNode->children->push_back(selectedNodesChildren->at(i));
    }

    //set the selected element to nothing
    selectedNode = NULL;
  }
}
//deletes the current node, relinking the children as necessary
void SceneGraph::resetScene(){
  goToParent();
  while(!currentNode->children->empty()){
    currentNode->children->pop_back();
  }

  selectedNode = NULL;
}

//draw the scenegraph
void SceneGraph::draw(){
  rootNode->draw();
}


void SceneGraph::addTransformationToCurrentNode(Node * transform){
  if(selectedNode == NULL) return;
  transformNode = selectedNode;
  currentNode = selectedNode->parent;
  insertChildNodeHere(transform);

  deleteThisNode();

  insertChildNodeHere(transformNode);
  selectedNode = transformNode;
  selectedNode->isSelected = true;
}




