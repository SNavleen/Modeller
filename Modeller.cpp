#ifdef __APPLE__
#  	include <OpenGL/gl.h>
#  	include <OpenGL/glu.h>
#  	include <GLUT/glut.h>
#else
#  	include <GL/gl.h>
#  	include <GL/glu.h>
#   include <GL/freeglut.h>
#	include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "structs.h"
#include "sceneGraph.h"
#include "nodeGroup.h"
//#include "nodeModel.h"
#include "nodeTransform.h"
#include "Window.h"
#include "DrawShape.h"

using namespace std;

//Object Variables
Window objWindow("perspective");
DrawShape objDrawShape("");
SceneGraph *SG;

float camPos[] = {2.5, 2.5, 0.5};
float pos[] = {0,1,0};
float angle = 0.0f;

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

/*bool cube = false, sphere = false, cone = false, 
	cylinder = false, torus = false, teapot = false, 
	tetrahedron = false, octahedron = false, dodecahedron = false,
	icosahedron = false;*/


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

//function which will populate a sample graph 
/*void initGraph(){

	NodeModel *M1 = new NodeModel(Teapot);
	//insert the node into the graph
	SG->insertChildNodeHere(M1);
}*/


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
	}

	if(key == '1'){//Cube
		DrawShape *drawCude = new DrawShape("Cube");
		SG->insertChildNodeHere(drawCude);
		//cude = true;
	}else if(key == '2'){//Sphere
		DrawShape *drawSphere = new DrawShape("Sphere");
		SG->insertChildNodeHere(drawSphere);
	}else if(key == '3'){//Cone
		//objDrawShape.drawCone();
	}else if(key == '4'){//Cylinder
		//objDrawShape.drawCylinder();
	}else if(key == '5'){//Torus
		//objDrawShape.drawTorus();
	}else if(key == '6'){//Teapot
		DrawShape *drawTeapot = new DrawShape("Teapot");
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
void MouseClickAction(int button, int state, int posX, int posY){
	/*switch(button){
		case GLUT_LEFT_BUTTON:
			break;

		case GLUT_RIGHT_BUTTON:
			break;

		default:
			break;
	}*/
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
