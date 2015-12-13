#include "sceneGraph.h"
#include "node.h"
#include "Vector3D.h"
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>

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

// mouse Intersection stuff
void getMouseRay2(int x, int y, Vector3D *start, Vector3D *end){
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

  /* printf("printing the mouseRay2\n"); */
  /* for(int i =0; i < 4; i++){ */
  /*   for(int j=0; j < 4; j++){ */
  /*     printf("%f, ",matModelView[i+j*4]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

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
void SceneGraph::printScene(){ this->printScene(rootNode, 0);  }
void SceneGraph::printScene(Node * curNode, int depth){
  for(int i = 0; i < depth; i++) printf("  ");
  if(this->currentNode == curNode) printf("<current node> ");
  printf("number of children:%li \n",curNode->children->size());
  for(int i = 0;i < curNode->children->size(); i++){
    printScene(curNode->children->at(i), depth+1);
  }
  for(int i = 0; i < depth; i++) printf("  ");
  printf("going up\n");
}
void SceneGraph::selectnodeAtPos(int x, int y){
  if(selectedNode != NULL) selectedNode->isSelected = false; // make it so that if you attempt to select another node it will make the first one false
  Vector3D rayStart = Vector3D();
  Vector3D rayEnd   = Vector3D();

  /* printf("\n\n\n started ray intersetion"); */
  /* getMouseRay2(x,y,&rayStart,&rayEnd); */
  /* printf("scene graph = rayStart:(%f,%f,%f)  endRay:(%f,%f,%f)\n",rayStart.x, rayStart.y,rayStart.z,  rayEnd.x,rayEnd.y,rayEnd.z); */

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


  /* printf("starting the ray intersection: made the vectors. print scene graph\n"); */
  /* printScene(rootNode, 0); */
  /* printf("going to load the identity\n"); */

  // reddid the recursion

  /* double mat[16]; */
  /* printf("===========OLDMATH============="); */
  /* glGetDoublev(GL_MODELVIEW_MATRIX, oldMat); */
  /* for(int i =0;i<16;i++){ */
     /* printf("%f, ", oldMat[i]); */
  /* } */
  /* glGetDoublev(GL_MODELVIEW_MATRIX, mat); */
  /* glLoadMatrixd(mat); */

  /* glLoadIdentity(); */

  rootNode->rayIntersection(&listOfnodes, &listOfIntersectionDistances, x,y);
  /* printf("done doing the ray intersection the length of the listOfnodes is:%li, listOfDistances:%li\n", listOfnodes.size(), listOfIntersectionDistances.size()); */

  /* printf("the size of the list of distances is %li\n",listOfIntersectionDistances.size()); */
  // go through the list to find the smallset element
  if(listOfIntersectionDistances.size()==0){
    selectedNode=NULL;
    /* printf("no Intersection\n"); */
    return;
  } // if there are no elements then just end the function
  /* printf("Intersection detected\n"); */
  int minDistanceIndex = 0; // this is the index which points to the node that is the closest to the screen
    /* printf("mindistance is %f for %i\n",listOfIntersectionDistances.at(0), 0); */
  for(int i = 1; i < listOfIntersectionDistances.size();i++){
    /* printf("mindistance is %f for %i\n",listOfIntersectionDistances.at(i), i); */
    if(listOfIntersectionDistances.at(i) < listOfIntersectionDistances.at(minDistanceIndex) && listOfIntersectionDistances.at(i) > 0) minDistanceIndex = i;
  }

  // make the selected node equal to the node that is closest to the screen and intersects the ray
  selectedNode = listOfnodes.at(minDistanceIndex);
  selectedNode->isSelected = true;
  /* printf("the selected node is at a distance of %f\n\n\n",  listOfIntersectionDistances.at(minDistanceIndex)); */
  /* printf("\n\n"); */
}


SceneGraph::SceneGraph(){
  rootNode = new Node();
  currentNode = rootNode;
  selectedNode = NULL;
  startRayD = NULL;
  endRayD = NULL;
  /* useCustomSettings(); */

  /* for(int i =0; i< 16; i++) oldMat[i] = 0.0f; */
}

void SceneGraph::printModelMatrix(){
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
  if (i < currentNode->children->size() && i >= -1)
    currentNode = currentNode->children->at(i);
  else
    printf("child out of range\n");
}
void SceneGraph::goToMaxChild(){
  currentNode = currentNode->children->at(currentNode->children->size()-1);
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
  goToRoot();
  while(!currentNode->children->empty()){
    currentNode->children->pop_back();
  }

  selectedNode = NULL;
}

void SceneGraph::saveFile(ofstream *sceneFile){
    printf("ID: %i\n", currentNode->ID);
    //*sceneFile << currentNode->ID << ",";
    if(currentNode->nodeType == 0){
        printf("root\n");
        *sceneFile << "root";
    }
    else if(currentNode->nodeType == 1){
        *sceneFile << "group";
    }
    else if(currentNode->nodeType == 2){
        *sceneFile << "transformation" << ",";
        NodeTransform *nodeTransform = static_cast<NodeTransform *>(currentNode);
        printf("%i\n",nodeTransform->transformationType);
        *sceneFile << nodeTransform->transformationType << ",";
        if(nodeTransform->transformationType == 0){
            printf("Translate: %f, %f, %f\n", nodeTransform->amount3.x, nodeTransform->amount3.y, nodeTransform->amount3.z);
            *sceneFile << nodeTransform->amount3.x << "," << nodeTransform->amount3.y << "," << nodeTransform->amount3.z;
        }else if(nodeTransform->transformationType == 1){
             printf("Rotate: %f, %f, %f, %f\n", nodeTransform->amount4.x, nodeTransform->amount4.y, nodeTransform->amount4.z, nodeTransform->amount4.w);
            *sceneFile << nodeTransform->amount4.x << "," << nodeTransform->amount4.y << "," << nodeTransform->amount4.z << "," << nodeTransform->amount4.w;
        }else if(nodeTransform->transformationType == 2){
             printf("Scale: %f, %f, %f\n", nodeTransform->amount3.x, nodeTransform->amount3.y, nodeTransform->amount3.z);
            *sceneFile << nodeTransform->amount3.x << "," << nodeTransform->amount3.y << "," << nodeTransform->amount3.z;
        }
    }
    else if(currentNode->nodeType == 3){
        *sceneFile << "model" << ",";
        DrawShape *drawShape = static_cast<DrawShape *>(currentNode);
        printf("Shape: %s\n", drawShape->modelType);
        *sceneFile << drawShape->modelType << ",";
        printf("Colour: %f, %f, %f\n", drawShape->red, drawShape->green, drawShape->blue);
        *sceneFile << drawShape->red << "," << drawShape->green << "," << drawShape->blue;
    }
    *sceneFile << " " << "\n";

    int indexOfSelectedNode;
    for(indexOfSelectedNode = 0; indexOfSelectedNode < currentNode->children->size(); indexOfSelectedNode++){
        goToChild(indexOfSelectedNode);
        saveFile(sceneFile);
        goToParent();
    }
}

void SceneGraph::loadFile(ifstream *sceneFile){
    if(*sceneFile){
         string line;
         while(getline(*sceneFile, line)){
            string row;
            stringstream streamRow(line);
            while(getline(streamRow, row, ' ')){
                string cell;
                stringstream streamCell(row);
                getline(streamCell, cell, ',');
                /* printf("%s\n", cell.c_str()); */
                if(cell == "root"){

                }else if(cell == "group"){

                }else if(cell == "transformation"){
                    getline(streamCell, cell, ',');
                    NodeTransform *transform;
                    if(cell == "0"){
                        Vector3D v3;
                        getline(streamCell, cell, ',');
                        v3.x = atof(cell.c_str());
                        getline(streamCell, cell, ',');
                        v3.y = atof(cell.c_str());
                        getline(streamCell, cell, ',');
                        v3.z = atof(cell.c_str());
                        transform = new NodeTransform(Translate, v3);
                    }else if(cell == "1"){
                        Vector4D v4;
                        getline(streamCell, cell, ',');
                        v4.x = atof(cell.c_str());
                        getline(streamCell, cell, ',');
                        v4.y = atof(cell.c_str());
                        getline(streamCell, cell, ',');
                        v4.z = atof(cell.c_str());
                        getline(streamCell, cell, ',');
                        v4.w = atof(cell.c_str());
                        transform = new NodeTransform(Rotate, v4);

                    }else if(cell == "2"){
                        Vector3D v3;
                        getline(streamCell, cell, ',');
                        v3.x = atof(cell.c_str());
                        getline(streamCell, cell, ',');
                        v3.y = atof(cell.c_str());
                        getline(streamCell, cell, ',');
                        v3.z = atof(cell.c_str());
                        transform = new NodeTransform(Scale, v3);
                    }
                    insertChildNodeHere(transform);
                    goToChild(0);
                }else if(cell == "model"){
                    int red, green, blue;
                    char *model;
                    getline(streamCell, cell, ',');
                    model = new char[cell.length() + 1];
                    strcpy(model, cell.c_str());
                    getline(streamCell, cell, ',');
                    red = atof(cell.c_str());
                    getline(streamCell, cell, ',');
                    green = atof(cell.c_str());
                    getline(streamCell, cell, ',');
                    blue = atof(cell.c_str());
                    DrawShape *drawShape = new DrawShape(model, red, green, blue);
                    insertChildNodeHere(drawShape);
                }

            }
         }
    }
}

//draw the scenegraph
void SceneGraph::draw(){
  /* printf("\n\nstart drawing\n"); */
  rootNode->draw();
}


void SceneGraph::addTransformationToCurrentNode(char *transformation, Node * transform){
    Vector3D v3;
    Vector4D v4;

    if(transformation == "Rotate"){
        transformNode = selectedNode->parent->parent->parent;
        static_cast<NodeTransform *>(transformNode)->amount4.x += static_cast<NodeTransform *>(transform)->amount4.x;
        static_cast<NodeTransform *>(transformNode)->amount4.y += static_cast<NodeTransform *>(transform)->amount4.y;
        static_cast<NodeTransform *>(transformNode)->amount4.z += static_cast<NodeTransform *>(transform)->amount4.z;
        static_cast<NodeTransform *>(transformNode)->amount4.w += static_cast<NodeTransform *>(transform)->amount4.w;
    }else if(transformation == "Translate"){
        transformNode = selectedNode->parent->parent;
        static_cast<NodeTransform *>(transformNode)->amount3.x += static_cast<NodeTransform *>(transform)->amount3.x;
        static_cast<NodeTransform *>(transformNode)->amount3.y += static_cast<NodeTransform *>(transform)->amount3.y;
        static_cast<NodeTransform *>(transformNode)->amount3.z += static_cast<NodeTransform *>(transform)->amount3.z;
    }else if(transformation == "Scale"){
        transformNode = selectedNode->parent;
        static_cast<NodeTransform *>(transformNode)->amount3.x += static_cast<NodeTransform *>(transform)->amount3.x;
        static_cast<NodeTransform *>(transformNode)->amount3.y += static_cast<NodeTransform *>(transform)->amount3.y;
        static_cast<NodeTransform *>(transformNode)->amount3.z += static_cast<NodeTransform *>(transform)->amount3.z;
    }
}




