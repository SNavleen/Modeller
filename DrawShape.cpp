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
  if(modelType == "Cube"){
    printf("going to draw the wireframe of the cube\n");
    glutWireCube(2);
  }
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


/* // mouse Intersection stuff */
/* void getMouseRay(int x, int y, Vector3D *start, Vector3D *end){ */
/*   printf("%i, %i\n", x, y); */
/*   //allocate matricies memory */
/*   double matModelView[16], matProjection[16]; */
/*   int viewport[4]; */

/*   //vectors */

/*   //grab the matricies */
/*   glGetDoublev(GL_MODELVIEW_MATRIX, matModelView); */
/*   glGetDoublev(GL_PROJECTION_MATRIX, matProjection); */
/*   glGetIntegerv(GL_VIEWPORT, viewport); */

/*   //unproject the values */
/*   double winX = (double)x; */
/*   double winY = viewport[3] - (double)y; */

/*   // get point on the 'near' plane (third param is set to 0.0) */
/*   gluUnProject(winX, winY, 0.0, matModelView, matProjection, viewport, */
/*       &start->x, &start->y, &start->z); */

/*   // get point on the 'far' plane (third param is set to 1.0) */
/*   gluUnProject(winX, winY, 1.0, matModelView, matProjection, */
/*       viewport, &end->x, &end->y, &end->z); */

/*   // print out the near and far stuff */
/*   printf("near point: %f,%f,%f\n", start->x, start->y, start->z); */
/*   printf("far point: %f,%f,%f\n", end->x, end->y, end->z); */
/* } */
/* //function which preforms intersection test */
/* bool sphereIntersection(int x, int y){ */
/*   //Vector3D start = {0,0,0}; */
/*   //Vector3D end ={1,1,1}; */
/*   Vector3D start = Vector3D(0,0,0); */
/*   Vector3D end = Vector3D(1,1,1); */
/*   getMouseRay(x,y,&start, &end); // get the ray for the mouse */

/*   double A, B, C; */
/*   double R0x, R0y, R0z; */
/*   double Rdx, Rdy, Rdz; */

/*   Rdx = end.x - start.x; //end[0] - start[0]; */
/*   Rdy = end.y - start.y; //end[1] - start[1]; */
/*   Rdz = end.z - start.z;  //end[2] - start[2]; */

/*   //magnitude! */
/*   double M = sqrt(Rdx*Rdx + Rdy*Rdy + Rdz* Rdz); */

/*   //unit vector! */
/*   Rdx /= M; */
/*   Rdy /= M; */
/*   Rdz /= M; */

/*   //A = Rd dot Rd */
/*   A = Rdx*Rdx + Rdy*Rdy + Rdz*Rdz; */
/*   double Btempx, Btempy, Btempz; */
/*   Btempx = R0x; */
/*   Btempy =  R0y; */
/*   Btempz =  R0z; */
/*   B = Btempx * Rdx + Btempy * Rdy + Btempz *Rdz; */
/*   B *= 2.0; */
/*   C = R0x*R0x + R0y*R0y + R0z* R0z - 1; */

/*   double sq = B*B  - 4*A*C; */
/*   double t0 = 0, t1 = 0; */
/*   if(sq < 0) printf("no Intersection!!!\n"); */
/*   else{ */
/*     t0 = ((-1) * B + sqrt(sq))/(2*A); */
/*     t1 = ((-1) * B - sqrt(sq))/(2*A); */

/*     printf("Intersection at: t = %f, and t = %f\n", t0, t1); */
/*   } */
/*   // else returns false */
/*   return (sq<0); */
/* } */
/* bool isPointInsideBoxInPlane(Vector3D point, Vector3D planenormal, Vector3D minPoint, Vector3D maxPoint){ */
/*   return false; */
/* } */
/* bool isPointInsideBox(double xp, double yp, double minx, double maxx, double miny, double maxy){ return (minx < xp && xp < maxx && miny < yp && yp < maxy); } */
/* //function which preforms intersection test */
/* bool planeIntersection(int x, int y, Vector3D normalVector){ */
/*   // check if denomenator is 0, n * Rd = 0 */
/*     // if yes no intersection because plane is at a 90 degree angle */
/*   // otherwise intersection point is at P = R0 + t * Rd */
/*   /1* Vector3D start = {0,0,0}; *1/ */
/*   /1* Vector3D end ={1,1,1}; *1/ */
/*   Vector3D start = Vector3D(0,0,0); */
/*   Vector3D end  = Vector3D(0,0,0); */
/*   getMouseRay(x,y,&start, &end); // get the ray for the mouse */
/*   /1* Vector3D n = {}; *1/ */
/*   /1* Vector3D r0 = {}; *1/ */
/*   /1* Vector3D rd = {}; *1/ */
/*   Vector3D n = Vector3D(); */
/*   Vector3D r0 = Vector3D(); */
/*   Vector3D rd = Vector3D(); */
/*   double D = 0; */
/*   double denom = n.dotVector3D(rd); // get the denomenator of the equation */
/*   // may have some double == 0 errors */
/*   if(denom == 0) return false; // because the plane is at 90 degrees so there is no intersection */
/*   if(fabs(denom) < 0.0001) return false; // because the plane is at 90 degrees so there is no intersection */

/*   // t = -(N * R0 + D) / (N * Rd); */
/*   /1* Vector3D tvector = ((n.dotProduct(r0)).addScaler(D).multiplyScaler(-1)) / (denom); *1/ */
/*   /1* Vector3D intersectingPoint = r0.addScaler(tvector.dotProduct(rd)); *1/ */
/*   Vector3D tvector = (((n.dotVector3D(r0)) + D) * -1) / (denom); */
/*   Vector3D intersectingPoint = r0 + (tvector.dotVector3D(rd)); */

/*   // check if that point is inside the bounds of the plane */
/*   /1* if(isPointInsideBoxInPlane(intersectingPoint, normalVector, )) return true; *1/ */
/*   /1* if(isPointInsideBoxInPlane()) return true; *1/ */
/*   /1* if(isPointInsideBoxInPlane()) return true; *1/ */
/*   return false; */
/* } */


