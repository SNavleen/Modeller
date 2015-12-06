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

bool blRed = false, blGreen = false, blBlue = false, showlight = true;
int red = 255, green = 255, blue = 255, lightCounter = 1;

bool blnZ = false, blnX = false, blnY = false;
float Z = 255, X = 255, Y = 255;

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
void LightingAndMaterial(){
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	if(showlight){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}else{
		glDisable(GL_LIGHTING);
	}

	objDrawShape.lighting();

	objDrawShape.material();
}

void Display(){
	float origin[3] = {0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	LightingAndMaterial();

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
void decreasAxies(){
	if(blnZ)
		Z=-0.01;
	if(blnX)
		X=-0.01;
	if(blnY)
		Y=-0.01;
	printf("decrease: %f, %f, %f\n", X, Y, Z);
}
void increaseAxies(){
	if(blnZ)
		Z=+0.01;
	if(blnX)
		X=+0.01;
	if(blnY)
		Y=+0.01;
	printf("increase: %f, %f, %f\n", X, Y, Z);
}

void transformationv3(char *transformation, Vector3D v3){
	v3.x = X;
	v3.y = Y;
	v3.z = Z;
	NodeTransform *transform;
	//printf("%s: %f, %f, %f\n", transformation, X, Y, Z);

	if(transformation == "Translate")
		transform = new NodeTransform(Translate, v3);
	else if(transformation == "Scale")
		transform = new NodeTransform(Scale, v3);
	SG->insertChildNodeHere(transform);
	SG->goToChild(0);
}

void transformationv4(char *transformation, Vector4D v4){
	//v4.w = 1;
	v4.x = X;
	v4.y = Y;
	v4.z = Z;
	NodeTransform *transform;
	//printf("%s: %f, %f, %f\n", transformation, X, Y, Z);

	if(transformation == "Rotate")
		transform = new NodeTransform(Rotate, v4);
	SG->insertChildNodeHere(transform);
	SG->goToChild(0);
}

/*  KeyBoardAction -- the GLUT keyboard function
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void KeyBoardAction(unsigned char key, int x, int y){
	int mod = glutGetModifiers();
	//Keys for general commands; such as quiting, reseting, loading, saving and lighting/material toggle
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q'){
		exit(0);
	}else if(key == 'r' || key == 'R'){
	}else if(key == 's' || key == 'S'){
	}else if(key == 'l' || key == 'L'){
	}else if(key == 'w' || key == 'W'){
		lightCounter++;
		if (lightCounter % 2 == 0){
			showlight = false;
		}else{
			showlight = true;
		}
	}

	//Keys to select a colour
	if(key == ','){//Select the red colour to change
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
	}

	//Keys for increasing and decreasing selected colour
	if(key == '-'){//Subtract 1 from the colour
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

	//Keys to draw a shpae
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
	}else if(key == '4'){//Torus
		DrawShape *drawTorus = new DrawShape("Torus", red, green, blue);
		SG->insertChildNodeHere(drawTorus);
	}else if(key == '5'){//Teapot
		DrawShape *drawTeapot = new DrawShape("Teapot", red, green, blue);
		SG->insertChildNodeHere(drawTeapot);
	}

	//Keys for what axis the transformation will be applied to
	if(key == 'z' || key == 'Z'){
		blnZ = true;
		blnX = false;
		blnY = false;
	}else if(key == 'x' || key == 'X'){
		blnZ = false;
		blnX = true;
		blnY = false;
	}else if(key == 'y' || key == 'Y'){
		blnZ = false;
		blnX = false;
		blnY = true;
	}else if(mod == 1 && (key == 'z' || key == 'Z')){
		blnZ = false;
		blnX = true;
		blnY = true;
	}else if(mod == 1 && (key == 'x' || key == 'X')){
		blnZ = true;
		blnX = false;
		blnY = true;
	}else if(mod == 1 && (key == 'y' || key == 'Y')){
		blnZ = true;
		blnX = true;
		blnY = false;
	}
	
	Vector3D v3;
	Vector4D v4;

	//Keys for what type of transformation will be applied
	if(mod == 1){
		if(key == 's' || key == 'S'){
			increaseAxies();
			transformationv3("Scale", v3);
		}else if(key == 'r' || key == 'R'){
			increaseAxies();
			transformationv4("Rotate", v4);
		}else if(key == 't' || key == 'T'){
			increaseAxies();
			transformationv3("Translate", v3);
		}
	}else if(mod == 4){
		if(key == 's' || key == 'S'){
			decreasAxies();
			transformationv3("Scale", v3);
		}else if(key == 'r' || key == 'R'){
			decreasAxies();
			transformationv4("Rotate", v4);
		}else if(key == 't' || key == 'T'){
			decreasAxies();
			transformationv3("Translate", v3);
		}
	}


	Display();
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
  printf("going to select the first node \n");
  SG->goToRoot();
  SG->goToChild(0);
  SG->selectCurrentNode();
  printf("done selecting the first node\n");
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
}

int main(int argc, char** argv){
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);

	cout << "-------------------------- MENU COMMANDS --------------------------" << endl;
	cout << "ARROW KEYS -------------------------- ROTATE CAMERA" << endl;
	cout << "END KEY -------------------------- DECREASE THE HIGHT OF THE CAMERA" << endl;
	cout << "HOME KEY -------------------------- INCREASE THE HIGHT OF THE CAMERA" << endl;
	cout << ", -------------------------- SELECT THE COLOUR RED" << endl;
	cout << ". -------------------------- SELECT THE COLOUR GREEN" << endl;
	cout << "/ -------------------------- SELECT THE COLOUR BLUE" << endl;
	cout << "- -------------------------- DECREASE THE SELECTED COLOUR" << endl;
	cout << "= -------------------------- INCREASE THE SELECTED COLOUR" << endl;
	cout << "w/W KEY -------------------------- TOGGLE LIGHTING AND MATERIAL" << endl;
	cout << "l/L KEY -------------------------- LOAD SAVED SECNE" << endl;
	cout << "s/S KEY -------------------------- SAVE SECNE INTO FILE" << endl;
	cout << "r/R KEY -------------------------- RESET SECNE" << endl;
	cout << "q -------------------------- EXIT" << endl;
	cout << "" << endl;

	cout << "-------------------------- DRAWING SHAPE COMMANDS --------------------------" << endl;
	cout << "1 KEY -------------------------- CUBE" << endl;
	cout << "2 KEY -------------------------- SPHERE" << endl;
	cout << "3 KEY -------------------------- CONE" << endl;
	cout << "4 KEY -------------------------- TORUS" << endl;
	cout << "5 KEY -------------------------- TEAPOT" << endl;
	cout << "" << endl;

	cout << "-------------------------- SHAPE MODIFICATION COMMANDS --------------------------" << endl;
	cout << "z/Z KEY -------------------------- SELECT Z AXIS" << endl;
	cout << "x/X KEY -------------------------- SELECT X AXIS" << endl;
	cout << "y/Y KEY -------------------------- SELECT Y AXIS" << endl;
	cout << "SHIFT z/Z KEY -------------------------- SELECT X AND Y AXIS" << endl;
	cout << "SHIFT x/X KEY -------------------------- SELECT Z AND Y AXIS" << endl;
	cout << "SHIFT y/Y KEY -------------------------- SELECT X AND Z AXIS" << endl;
	cout << "ALT s/S KEY -------------------------- DECREASE SCALE" << endl;
	cout << "ALT r/R KEY -------------------------- DECREASE ROTATE" << endl;
	cout << "ALT t/T KEY -------------------------- DECREASE TRANSLATE" << endl;
	cout << "SHIFT s/S KEY -------------------------- INCREASE SCALE" << endl;
	cout << "SHIFT r/R KEY -------------------------- INCREASE ROTATE" << endl;
	cout << "SHIFT t/T KEY -------------------------- INCREASE TRANSLATE" << endl;


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
