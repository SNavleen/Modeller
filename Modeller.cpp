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
	}else if(key == '7'){//Tetrahedron
		//objDrawShape.drawTetrahedron();
	}else if(key == '8'){//Octahedron
		//objDrawShape.drawOctahedron();
	}else if(key == '9'){//Dodecahedron
		//objDrawShape.drawDodecahedron();
	}else if(key == '0'){//Icosahedron
		//objDrawShape.drawIcosahedron();
	}
}

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

void drawWireFrameObject(){
  // TODO

  // go to the root node


  // go to all the children checking if they had got the collision


  // this is just a temp fix
  SG->goToRoot();
  SG->goToChild(0);
  SG->selectCurrentNode();
}

void MouseClickAction(int button, int state, int posX, int posY){
  switch(button){
    case GLUT_LEFT_BUTTON:
      if(state==0) drawWireFrameObject();
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

	//add various nodes
	//initializing our world
	//initGraph();
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
