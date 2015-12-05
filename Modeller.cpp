#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#  include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

/* #include "structs.h" */
#include "vector3d.h"
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeTransform.h"
#include "Window.h"
#include "DrawShape.h"

using namespace std;

//Object Variables
Window objWindow("perspective");
DrawShape objDrawShape("", 255, 255, 255);
SceneGraph *SG;

float camPos[] = {2.5, 2.5, 0.5};
float pos[] = {0,1,0};
float angle = 0.0f;

bool blRed = false, blGreen = false, blBlue = false;
int red = 255, green = 255, blue = 255;

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

//Window size
void CreateDisplayWindow(int width, int height){
	objWindow.setWidth(width);
	objWindow.setHeight(height);

	objWindow.setPosX((glutGet(GLUT_SCREEN_WIDTH)-objWindow.getWidth())/2);
	objWindow.setPosY((glutGet(GLUT_SCREEN_HEIGHT)-objWindow.getHeight())/2);

	//Set the Window Size
	glutInitWindowSize(objWindow.getWidth(), objWindow.getHeight());
	//Set Window position
	glutInitWindowPosition(objWindow.getPosX(), objWindow.getPosY());
	//glutCreateWindow("3D Terrain");
}

void Display(){
	float origin[3] = {0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	glColor3f(1,1,1);

	//draw the sceneGraph
	objDrawShape.drawAxis();
	SG->draw();

	glutSwapBuffers();
}
int decreaseColour(int colour){
	if(colour>0)
		return --colour;
	return colour;
}

int increaseColour(int colour){
	if(colour<256)
		return ++colour;
	return colour;
}
/*  KeyBoardAction -- the GLUT keyboard function
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void KeyBoardAction(unsigned char key, int x, int y){
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q'){
		exit(0);
	}else if(key == 'r' || key == 'R'){
	}else if(key == 's' || key == 'S'){
	}else if(key == 'l' || key == 'L'){
	}else if(key == ','){//Select the red colour to change
		blRed = true;
		blGreen = false;
		blBlue = false;
	}else if(key == '.'){//Select the green colour to change
		blRed = false;
		blGreen = true;
		blBlue = false;
	}else if(key == '/'){//Select the blue colour to change
		blRed = false;
		blGreen = false;
		blBlue = true;
	}else if(key == '-'){//Subtract 1 from the colour
		if(blRed)
			red = decreaseColour(red);
		else if(blGreen)
			green = decreaseColour(green);
		else if(blBlue)
			blue = decreaseColour(blue);
	}else if(key == '='){//Add 1 to the colour
		if(blRed)
			red = increaseColour(red);
		else if(blGreen)
			red = increaseColour(green);
		else if(blBlue)
			blue = increaseColour(blue);
	}

	if(key == '1'){//Cube
		DrawShape *drawCude = new DrawShape("Cube", red, green, blue);
		SG->insertChildNodeHere(drawCude);
		//cude = true;
	}else if(key == '2'){//Sphere
		DrawShape *drawSphere = new DrawShape("Sphere", red, green, blue);
		SG->insertChildNodeHere(drawSphere);
	}else if(key == '3'){//Cone
		DrawShape *drawCone = new DrawShape("Cone", red, green, blue);
		SG->insertChildNodeHere(drawCone);
	}else if(key == '4'){//Cylinder
		DrawShape *drawCylinder = new DrawShape("Cylinder", red, green, blue);
		SG->insertChildNodeHere(drawCylinder);
	}else if(key == '5'){//Torus
		DrawShape *drawTorus = new DrawShape("Torus", red, green, blue);
		SG->insertChildNodeHere(drawTorus);
	}else if(key == '6'){//Teapot
		DrawShape *drawTeapot = new DrawShape("Teapot", red, green, blue);
		SG->insertChildNodeHere(drawTeapot);
	}
}

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
// end of mouse Intersection stuff
//drawCube();         //
//drawSphere();       //
//drawCone();         //
//drawCylinder();     //
//drawTorus();        //
//drawTeapot();       //

void KeyBoardSpecial(int key, int x, int y){
  if(key == GLUT_KEY_LEFT){
    camPos[0]-=0.1;
  }else if(key == GLUT_KEY_RIGHT){
    camPos[0]+=0.1;
  }
  if(key == GLUT_KEY_UP){
    camPos[2]-=0.1;
  }else if(key == GLUT_KEY_DOWN){
    camPos[2]+=0.1;
  }
  if(key == GLUT_KEY_END){
    camPos[1]-=0.1;
  }else if(key == GLUT_KEY_HOME){
    camPos[1]+=0.1;
  }
  glutPostRedisplay();
}
void MouseClickAction(int button, int state, int posX, int posY){
  switch(button){
    case GLUT_LEFT_BUTTON:
      /* Intersect(posX, posY); */
      sphereIntersection(posX, posY);
      break;
    case GLUT_RIGHT_BUTTON:
      break;
    default:
      break;
  }
}

//Init
void glutCallbacks(){
	glutDisplayFunc(Display);
	glutKeyboardFunc(KeyBoardAction);
	glutSpecialFunc(KeyBoardSpecial);
	glutMouseFunc(MouseClickAction);
}
void init(void){
	GLuint id = 1;

	glEnable(GLUT_DEPTH);

	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	//init our scenegraph
	SG = new SceneGraph();
}

int main(int argc, char** argv){
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);


	CreateDisplayWindow(600, 600);
	//Creates the Terrain window
	glutCreateWindow("Modeller");
	glutCallbacks();
	init();

	//enable Z buffer test, otherwise things appear in the order they're drawn
	//glEnable(GL_DEPTH_TEST);
	objWindow.viewDisplay();

	glutMainLoop();

	return 0;
}
