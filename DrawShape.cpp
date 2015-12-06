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
  if(modelType == "Teapot"){
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



//function which preforms intersection test
bool sphereIntersection(vector<double> *listOfDoubles, Vector3D *rayStart, Vector3D *rayEnd){
  printf("  2. rayStart:(%f,%f,%f)  rayEnd:(%f,%f,%f)\n",rayStart->x,rayStart->y, rayStart->z,rayEnd->x, rayEnd->y, rayEnd->z);
  //just to check if it this method works
  double A, B, C;
  double R0x, R0y, R0z;
  double Rdx, Rdy, Rdz;
  R0x = rayStart->x;
  R0y = rayStart->y;
  R0z = rayStart->z;


  Rdx = rayEnd->x - rayStart->x;
  Rdy = rayEnd->y - rayStart->y;
  Rdz = rayEnd->z - rayStart->z;
  printf("  2. rdx:%f rdy:%f rdz:%f\n",Rdx,Rdy,Rdz);

  //magnitude!
  double M = sqrt(Rdx*Rdx + Rdy*Rdy + Rdz* Rdz);

  //unit vector!
  Rdx /= M;
  Rdy /= M;
  Rdz /= M;
  printf("  2. unit vector rdx:%f rdy:%f rdz:%f\n",Rdx,Rdy,Rdz);


  //A = Rd dot Rd
  A = Rdx*Rdx + Rdy*Rdy + Rdz*Rdz;
  printf("  2. a) A: %f\n", A);
  double Btempx, Btempy, Btempz;
  Btempx = R0x;
  Btempy = R0y;
  Btempz = R0z;
  printf("  2. b) btempx:%f btempy:%f btempz:%f\n",Btempx, Btempy, Btempz);
  B = Btempx * Rdx + Btempy * Rdy + Btempz *Rdz;
  B *= 2.0;
  C = R0x*R0x + R0y*R0y + R0z* R0z - 1;
  printf("  2. c) B:%f C:%f\n",B,C);

  double sq = B*B  - 4*A*C;
  double t0 = 0, t1 = 0;
  printf("sq: %f\n",sq);
  if(sq < 0) printf("no Intersection!!!\n");
  else{
    t0 = ((-1) * B + sqrt(sq))/(2*A);
    t1 = ((-1) * B - sqrt(sq))/(2*A);
    listOfDoubles->push_back((t0<t1)? t0:t1);

    printf("Intersection at: t = %f, and t = %f\n", t0, t1);
  }
  // else returns false
  return (sq>=0);
}
bool isPointInsideBoxInPlane(Vector3D point, Vector3D p0, Vector3D p1, Vector3D p2, Vector3D p3){
  printf("t0:(%f,%f,%f) t1:(%f,%f,%f) t2:(%f,%f,%f) t3:(%f,%f,%f)\n",t0.x,t0.y,t0.z,  t1.x,t1.y,t1.z,  t2.x,t2.y,t2.z,  t3.x,t3.y,t3.z);
  Vector3D v0 = p0 - p3;
  Vector3D v1 = p1 - p0;
  Vector3D v2 = p2 - p1;
  Vector3D v3 = p3 - p2;

  //line 1
  printf("first \n");
  Vector3D pToP2 = point -p2;
  double result = v2.dotVector3D(pToP2);
  if(result > 0) return false;

  //line 2
  printf("second \n");
  Vector3D pToP1 = point - p1;
  result = v1.dotVector3D(pToP1);
  if(result > 0) return false;

  //line 3
  printf("third \n");
  Vector3D pToP3 = point - p3;
  result = v3.dotVector3D(pToP1);
  if(result > 0) return false;

  //line 4
  printf("fourth \n");
  Vector3D pToP0 = point - p0;
  result = v0.dotVector3D(pToP0);
  if(result > 0) return false;

  printf("done everything, returning true\n");
  return true;
}
//function which preforms intersection test
/* bool planeIntersection(vector<double> *listOfDistances, Vector3D rd, Vector3D r0, Vector3D planeNormal, Vector3D *rayStart, Vector3D *rayEnd){ */
bool planeIntersection(vector<double> *listOfDistances, Vector3D p0, Vector3D p1, Vector3D p2, Vector3D p3, Vector3D rayStart, Vector3D rayEnd){
  printf(">>>>> testing purposes\n");
  Vector3D t0 = Vector3D(0,0,0);
  Vector3D t1 = Vector3D(1,0,0);
  Vector3D t2 = Vector3D(1,-1,0);
  Vector3D t3 = Vector3D(0,-1,0);
  Vector3D point= Vector3D(1,1,1);
  printf("checking if the point is inside the box result is %i should be %i \n", isPointInsideBoxInPlane(point, t0,t1,t2,t3), 0);
  printf("checking if the point is inside the box result is %i should be %i \n", isPointInsideBoxInPlane(Vector3D(1,-2,0), t0,t1,t2,t3), 0);
  printf("checking if the point is inside the box result is %i should be %i \n", isPointInsideBoxInPlane(Vector3D(0,0,0), t0,t1,t2,t3), 1);
  printf("checking if the point is inside the box result is %i should be %i \n", isPointInsideBoxInPlane(Vector3D(0.5,-0.5,0), t0,t1,t2,t3), 1);
  printf(">>>>> done testing purposes\n");


  // calculate these values
  Vector3D planeNormal = (p1-p0).crossVector3D(p2-p1);
  Vector3D r0 = rayStart;
  Vector3D rd = rayEnd-rayStart;
  double D = 0;
  double denom = planeNormal.dotVector3D(rd); // get the denomenator of the equation
  // may have some double == 0 errors
  if(denom == 0) return false; // because the plane is at 90 degrees so there is no intersection
  if(fabs(denom) < 0.001) return false; // because the plane is at 90 degrees so there is no intersection

  // t = -(N * R0 + D) / (N * Rd);
  double t = (((planeNormal.dotVector3D(r0)) + D) * -1) / (denom);
  Vector3D intersectingPoint = r0 + (rd * t);
  if(!isPointInsideBoxInPlane(intersectingPoint, p0,p1,p2,p3)) return false;
  listOfDistances->push_back(t);
  return true; // the plane intersects the ray
}

void DrawShape::rayIntersection(vector<Node*> *listOfnodes, vector<double> *listOfDistances, Vector3D *rayStart, Vector3D*rayEnd){
  printf("calling the stupid plane intersection\n");
  planeIntersection(listOfDistances, Vector3D(),Vector3D(),Vector3D(),Vector3D(), Vector3D(), Vector3D());
  printf("done testing the plane intersection \n");


  printf("  1. rayintersection in the draw shape \n");
  if(modelType=="Sphere"){
    printf("  1. it is a sphere, running the sphere intersection\n");
    if(sphereIntersection(listOfDistances, rayStart, rayEnd)){
      listOfnodes->push_back(this);;
    }
    return;
  }
  double minX=-1,minY=-1,minZ=-1;
  double maxX=1,maxY=1,maxZ=1;
  if(modelType == "Teapot"){
    minX=-1.5;minY=-1;minZ=-1;
    maxX=1.5;maxY=1;maxZ=1;
  }else if(modelType == "Cone"){
    minX=-0.5;minY=-0.5;minZ=-0;
    maxX=0.5;maxY=0.5;maxZ=1;
  }else if(modelType == "Torus"){
    minX=-1.2,minY=-1.2,minZ=-0.5;
    maxX=1.2,maxY=1.2,maxZ=0.5;
  }
  // get the vertex values
  Vector3D v1 = Vector3D(maxX,maxY,maxZ);
  Vector3D v2 = Vector3D(maxX,minY,maxZ);
  Vector3D v3 = Vector3D(minX,minY,maxZ);
  Vector3D v4 = Vector3D(minX,maxY,maxZ);
  Vector3D v5 = Vector3D(maxX,maxY,minZ);
  Vector3D v6 = Vector3D(maxX,minY,minZ);
  Vector3D v7 = Vector3D(minX,minY,minZ);
  Vector3D v8 = Vector3D(minX,maxY,minZ);

}


