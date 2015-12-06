#include "sceneGraph.h"
#include "node.h"
#include "Vector3D.h"
#include <limits>
#include <stdio.h>

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



//---------------------------------mouse ray intersection stuff--------------------------------------

// mouse Intersection stuff
void getMouseRay(int x, int y, Vector3D *start, Vector3D *end){
  printf("%i, %i\n", x, y);
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
  printf("near point: %f,%f,%f\n", start->x, start->y, start->z);
  printf("far point: %f,%f,%f\n", end->x, end->y, end->z);
}
bool rayBoxIntersection(){
  return false;
}
//function which preforms intersection test
bool sphereIntersection(int x, int y){
  //Vector3D start = {0,0,0};
  //Vector3D end ={1,1,1};
  Vector3D start = Vector3D(0,0,0);
  Vector3D end = Vector3D(1,1,1);
  getMouseRay(x,y,&start, &end); // get the ray for the mouse

  double A, B, C;
  double R0x, R0y, R0z;
  double Rdx, Rdy, Rdz;

  Rdx = end.x - start.x; //end[0] - start[0];
  Rdy = end.y - start.y; //end[1] - start[1];
  Rdz = end.z - start.z;  //end[2] - start[2];

  //magnitude!
  double M = sqrt(Rdx*Rdx + Rdy*Rdy + Rdz* Rdz);

  //unit vector!
  Rdx /= M;
  Rdy /= M;
  Rdz /= M;

  //A = Rd dot Rd
  A = Rdx*Rdx + Rdy*Rdy + Rdz*Rdz;
  double Btempx, Btempy, Btempz;
  Btempx = R0x;
  Btempy =  R0y;
  Btempz =  R0z;
  B = Btempx * Rdx + Btempy * Rdy + Btempz *Rdz;
  B *= 2.0;
  C = R0x*R0x + R0y*R0y + R0z* R0z - 1;

  double sq = B*B  - 4*A*C;
  double t0 = 0, t1 = 0;
  if(sq < 0) printf("no Intersection!!!\n");
  else{
    t0 = ((-1) * B + sqrt(sq))/(2*A);
    t1 = ((-1) * B - sqrt(sq))/(2*A);

    printf("Intersection at: t = %f, and t = %f\n", t0, t1);
  }
  // else returns false
  return (sq<0);
}
bool isPointInsideBoxInPlane(Vector3D point, Vector3D planenormal, Vector3D minPoint, Vector3D maxPoint){
  return false;
}
bool isPointInsideBox(double xp, double yp, double minx, double maxx, double miny, double maxy){ return (minx < xp && xp < maxx && miny < yp && yp < maxy); }
//function which preforms intersection test
bool planeIntersection(int x, int y, Vector3D normalVector){
  // check if denomenator is 0, n * Rd = 0
    // if yes no intersection because plane is at a 90 degree angle
  // otherwise intersection point is at P = R0 + t * Rd
  /* Vector3D start = {0,0,0}; */
  /* Vector3D end ={1,1,1}; */
  Vector3D start = Vector3D(0,0,0);
  Vector3D end  = Vector3D(0,0,0);
  getMouseRay(x,y,&start, &end); // get the ray for the mouse
  /* Vector3D n = {}; */
  /* Vector3D r0 = {}; */
  /* Vector3D rd = {}; */
  Vector3D n = Vector3D();
  Vector3D r0 = Vector3D();
  Vector3D rd = Vector3D();
  double D = 0;
  double denom = n.dotVector3D(rd); // get the denomenator of the equation
  // may have some double == 0 errors
  if(denom == 0) return false; // because the plane is at 90 degrees so there is no intersection
  if(fabs(denom) < 0.0001) return false; // because the plane is at 90 degrees so there is no intersection

  // t = -(N * R0 + D) / (N * Rd);
  /* Vector3D tvector = ((n.dotProduct(r0)).addScaler(D).multiplyScaler(-1)) / (denom); */
  /* Vector3D intersectingPoint = r0.addScaler(tvector.dotProduct(rd)); */
  Vector3D tvector = (((n.dotVector3D(r0)) + D) * -1) / (denom);
  Vector3D intersectingPoint = r0 + (tvector.dotVector3D(rd));

  // check if that point is inside the bounds of the plane
  /* if(isPointInsideBoxInPlane(intersectingPoint, normalVector, )) return true; */
  /* if(isPointInsideBoxInPlane()) return true; */
  /* if(isPointInsideBoxInPlane()) return true; */
  return false;
}

//---------------------------------mouse ray intersection stuff--------------------------------------



SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
    selectedNode = NULL;
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
	currentNode->children->push_back(node);
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode(){
	//TODO
}

void SceneGraph::selectnodeAtPos(int x, int y){
  // go to the root node
  // go to all the children checking if they had got the collision
  Node *curnodeLocal = rootNode;
  Node *closestToScreenIntersection = NULL; // this is the node that is closest to the screen
  double closestToScreenZValue = std::numeric_limits<double>::lowest();
  for(int i = 0; i < currentNode->children->size(); i++){
    if(rayBoxIntersection()){
      Node *node =  curnodeLocal->children->at(i);
      /* if(closestToScreenZValue < node.getZValue){ */
        /* closestToScreenZValue=node.getZValue; */
        node = closestToScreenIntersection;
      /* } */
      /* curnodeLocal.getPosition(); */
      // compare the closesttoscreenintersection's z value with the new found value and store
    }
  }

  // make the selected node equal to the node that is closest to the screen and intersects the ray
  selectedNode = closestToScreenIntersection;
}

//draw the scenegraph
void SceneGraph::draw(){
	rootNode->draw();
    /* printf("is selected node null: %i\n",(selectedNode!=NULL)); */
    if(selectedNode != NULL) selectedNode->drawWireFrame();
}


