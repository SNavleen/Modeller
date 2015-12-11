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


// mouse Intersection stuff
void getMouseRay(int x, int y, Vector3D *start, Vector3D *end){
  /* printf("%i, %i\n", x, y); */
  //allocate matricies memory
  double matModelView[16], matProjection[16];
  int viewport[4];

  //vectors

  //grab the matricies
  glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
  glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
  glGetIntegerv(GL_VIEWPORT, viewport);

  //unproject the values
  double winX = (double)x;
  double winY = viewport[3] - (double)y;

  // get point on the 'near' plane (third param is set to 0.0)
  gluUnProject(winX, winY, 0.0, matModelView, matProjection, viewport,
      &start->x, &start->y, &start->z);

  // get point on the 'far' plane (third param is set to 1.0)
  gluUnProject(winX, winY, 1.0, matModelView, matProjection,
      viewport, &end->x, &end->y, &end->z);

  // print out the near and far stuff
  /* printf("near point: %f,%f,%f\n", start->x, start->y, start->z); */
  /* printf("far point: %f,%f,%f\n", end->x, end->y, end->z); */
}


Node* SceneGraph::getSelectedNode(){
  return selectedNode;
}

void SceneGraph::selectnodeAtPos(int x, int y){
  /* printf("\n\nstarting the select node at pos\n"); */
  Vector3D start = Vector3D(); // this is the point of the ray vector at the front
  Vector3D end = Vector3D();  // this is the point of the ray vector at the end
  getMouseRay(x,y,&start,&end); // actually calculate the following values
  this->startRayD = new Vector3D(start.x, start.y, start.z);
  this->endRayD = new Vector3D(end.x, end.y, end.z);
  /* printf("get the mouse ray\n"); */

  vector<Node*> listOfnodes = vector<Node*>();
  vector<double> listOfIntersectionDistances = vector<double>();
  Node *curnodeLocal = rootNode;// go to the root node
  /* printf("starting the for loop with all the children\n"); */
  // go to all the children checking if they had got the collision
  for(int i = 0; i < curnodeLocal->children->size(); i++){
    /* printf("going to the child at i:%i\n",i); */
    Node *node =  curnodeLocal->children->at(i);
    node->rayIntersection(&listOfnodes,&listOfIntersectionDistances,start,end);
  }
  /* printf("done the selectnodeatpos\n\n"); */

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
{ if(rootNode->children->size() > 0) selectedNode = rootNode->children->at(0);}

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
  /* printf("is selected node null: %i\n",(selectedNode!=NULL)); */
  /* printf("the selected node is null () (selectenode==null):? %i\n", (selectedNode==NULL)); */
  if(selectedNode != NULL) selectedNode->drawWireFrame();
}


void SceneGraph::addTransformationToCurrentNode(Node * transform){


  Node * parentSelectedNode = selectedNode->parent;
/*-  vector<Node*> * parentsChildren = selectedNode->children;
-  parentSelectedNode->children = new vector<Node*>();
-  parentSelectedNode->children->push_back(transform);
-  transform->children = parentsChildren;*/


  transformNode = selectedNode;
  //vector<Node*> * parentsChildren = selectedNode->children;
  //parentSelectedNode->children = new vector<Node*>();
  currentNode = selectedNode->parent;
  insertChildNodeHere(transform);

  //find the selected nodes index
  /*int indexOfSelectedNode = 0;
  for(indexOfSelectedNode = 0; indexOfSelectedNode < parentSelectedNode->children->size(); indexOfSelectedNode++){
    if(parentSelectedNode->children->at(indexOfSelectedNode) == selectedNode) break;
  }

  printf("%i\n", indexOfSelectedNode);
  goToParent();
  goToChild(indexOfSelectedNode);*/
  //goToParent();
  /*while(!currentNode->children->empty()){
    currentNode->children->pop_back();
  }*/
  //selectedNode = NULL;
  deleteThisNode();

  insertChildNodeHere(transformNode);
  selectedNode = transformNode;
  //parentSelectedNode->children->push_back(transform);
  //transform->children = parentsChildren;
}




