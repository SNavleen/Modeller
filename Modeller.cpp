#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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

#include "Window.h"
#include "DrawShape.h"
using namespace std;

//Object Variables
Window objWindow("perspective");
DrawShape objDrawShape;


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

/*  display() - the OpenGL display function, this draws the screen
 *  it displays a spinning cube
 */
 void Display(){
 	//clear the screen
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 	//swap buffers - rendering is done to the back buffer, bring it forward to display
 	glutSwapBuffers();
 	//force a redisplay, to keep the animation running
 	glutPostRedisplay();
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
		objDrawShape.drawCube();
	}else if(key == '2'){//Sphere
		objDrawShape.drawSphere();
	}else if(key == '3'){//Cone
		objDrawShape.drawCone();
	}else if(key == '4'){//Cylinder
		objDrawShape.drawCylinder();
	}else if(key == '5'){//Torus
		objDrawShape.drawTorus();
	}else if(key == '6'){//Teapot
		objDrawShape.drawTeapot();
	}else if(key == '7'){//Tetrahedron
		objDrawShape.drawTetrahedron();
	}else if(key == '8'){//Octahedron
		objDrawShape.drawOctahedron();
	}else if(key == '9'){//Dodecahedron
		objDrawShape.drawDodecahedron();
	}else if(key == '0'){//Icosahedron
		objDrawShape.drawIcosahedron();
	}
}

void KeyBoardSpecial(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
	}else if(key == GLUT_KEY_RIGHT){
	}
	if(key == GLUT_KEY_UP){
	}else if(key == GLUT_KEY_DOWN){
	}
	glutPostRedisplay();
}
void MouseClickAction(int button, int state, int posX, int posY){
	switch(button){
		case GLUT_LEFT_BUTTON:
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
int main(int argc, char** argv){

	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);


	CreateDisplayWindow(600, 600);
	//Creates the Terrain window
	glutCreateWindow("Modeller");
	glutCallbacks();
	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);
	objWindow.viewDisplay();
	
	glutMainLoop();

	return 0;
}
