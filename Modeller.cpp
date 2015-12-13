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
#include <fstream>

#include "structs.h"
#include "vector3d.h"
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeTransform.h"
#include "Window.h"
#include "DrawShape.h"

using namespace std;

//Object Variables
Window objWindow("perspective");
DrawShape objDrawShape("", 1, 1, 1);
SceneGraph *SG;

float camPos[] = {2.5, 2.5, 0.5};
float pos[] = {0,1,0};
float angle = 0.0f;

bool blRed = false, blGreen = false, blBlue = false, showlight = true;
int red = 1, green = 1, blue = 1, lightCounter = 1, lightX = 0, lightZ = 0;

bool blnZ = false, blnX = false, blnY = false, blnAngle = false;
Vector3D v3S, v3T;
Vector4D v4R;
ofstream sceneFile;

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

    objDrawShape.setLight(lightX, lightZ);
    objDrawShape.lighting();
    //objDrawShape.material();
}

void Display(){
    float origin[3] = {0,0,0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    LightingAndMaterial();

    gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
    glClearColor(1, 1, 0.9, 0);

    //draw the sceneGraph
    objDrawShape.drawAxis();
    SG->draw();
    //printf("V3S: %f, %f, %f\n", v3S.x, v3S.y, v3S.z);
    //printf("V3T: %f, %f, %f\n", v3T.x, v3T.y, v3T.z);
    //printf("V3R: %f, %f, %f, %f\n", v4R.x, v4R.y, v4R.z, v4R.w);

    /* SG->drawRay(); */
    glutSwapBuffers();
}

int decreaseColour(int colour){
    if(colour>1)
        return --colour;
    return colour;
}

int increaseColour(int colour){
    if(colour<256)
        return ++colour;
    return colour;
}

Vector3D increase3D(Vector3D v3){
    if(blnZ)
        v3.z+=0.1;
    if(blnX)
        v3.x+=0.1;
    if(blnY)
        v3.y+=0.1;
    return v3;
}
Vector3D decrease3D(Vector3D v3){
    if(blnZ)
        v3.z-=0.1;
    if(blnX)
        v3.x-=0.1;
    if(blnY)
        v3.y-=0.1;
    return v3;
}

void transformationv3(char *transformation, Vector3D v3){
    NodeTransform *transform;

    if(transformation == "Translate")
        transform = new NodeTransform(Translate, v3);
    else if(transformation == "Scale")
        transform = new NodeTransform(Scale, v3);
    SG->addTransformationToCurrentNode(transformation, transform);
}

void transformationv4(char *transformation, Vector4D v4){
    NodeTransform *transform;

    if(transformation == "Rotate")
        transform = new NodeTransform(Rotate, v4);
    SG->addTransformationToCurrentNode(transformation, transform);
}
void resetRotate(){
    v4R.x = 0;
    v4R.y = 0;
    v4R.z = 0;
    v4R.w = 0;
}

void insertDefaultTransformations(NodeTransform *rotate, NodeTransform *translate, NodeTransform *scale){
    //Insert default Rotate node to scene graph
    SG->insertChildNodeHere(rotate);
    SG->goToChild(0);

    //Insert default Translate node to scene graph
    SG->insertChildNodeHere(translate);
    SG->goToChild(0);

    //Insert default Scale node to scene graph
    SG->insertChildNodeHere(scale);
    SG->goToChild(0);
}

/*  KeyBoardAction -- the GLUT keyboard function
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void KeyBoardAction(unsigned char key, int x, int y){
    int mod = glutGetModifiers();
    //printf("%i, %u\n", mod, key);
    //printf("%u\n", key);
    //Keys for general commands; such as quiting, reseting, loading, saving and lighting/material toggle
    //if the "q" key is pressed, quit the program
    if(key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }else if(key == 127 || key == 8){
        SG->resetScene();
    }else if(mod == 2 && key == 19){
        SG->goToRoot();
        sceneFile.open("Scene-Graph.csv");
        SG->saveFile(&sceneFile);
        sceneFile.close();
    }else if(mod == 2 && key == 15){
    }else if(key == 'w'){
        lightCounter++;
        if (lightCounter % 2 == 0){
            showlight = false;
        }else{
            showlight = true;
        }
    }

    if(key == 'u'){
        lightZ +=5;
    }else if(key == 'j'){
        lightZ -=5;
    }
    if(key == 'k'){
        lightX +=5;
    }else if(key == 'h'){
        lightX -=5;
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

    Vector3D v3s = Vector3D(1,1,1), v3t = Vector3D(0,0,0);
    Vector4D v4r = {0,0,0,0};
    printf("v4r: (%f,%f,%f,%f)\n",v4r.x,v4r.y,v4r.z,v4r.w);

    NodeTransform *rotate = new NodeTransform (Rotate, v4r);
    NodeTransform *translate = new NodeTransform (Translate, v3t);
    NodeTransform *scale = new NodeTransform (Scale, v3s);

    //Keys to draw a shpae
    if(key == '1'){//Cube
        insertDefaultTransformations(rotate, translate, scale);

        DrawShape *drawCude = new DrawShape("Cube", red, green, blue);
        SG->insertChildNodeHere(drawCude);
        //cude = true;
    }else if(key == '2'){//Sphere
        insertDefaultTransformations(rotate, translate, scale);

        DrawShape *drawSphere = new DrawShape("Sphere", red, green, blue);
        SG->insertChildNodeHere(drawSphere);
    }else if(key == '3'){//Cone
        insertDefaultTransformations(rotate, translate, scale);

        DrawShape *drawCone = new DrawShape("Cone", red, green, blue);
        SG->insertChildNodeHere(drawCone);
    }else if(key == '4'){//Torus
        insertDefaultTransformations(rotate, translate, scale);

        DrawShape *drawTorus = new DrawShape("Torus", red, green, blue);
        SG->insertChildNodeHere(drawTorus);
    }else if(key == '5'){//Teapot
        insertDefaultTransformations(rotate, translate, scale);

        DrawShape *drawTeapot = new DrawShape("Teapot", red, green, blue);
        SG->insertChildNodeHere(drawTeapot);
    }

    //Keys for what axis the transformation will be applied to
    if(key == 'z'){
        blnZ = true;
        blnX = false;
        blnY = false;
        blnAngle = false;
    }else if(key == 'x'){
        blnZ = false;
        blnX = true;
        blnY = false;
        blnAngle = false;
    }else if(key == 'y'){
        blnZ = false;
        blnX = false;
        blnY = true;
        blnAngle = false;
    }else if(key == 'Z'){
        blnZ = false;
        blnX = true;
        blnY = true;
        blnAngle = false;
    }else if(key == 'X'){
        blnZ = true;
        blnX = false;
        blnY = true;
        blnAngle = false;
    }else if(key == 'Y'){
        blnZ = true;
        blnX = true;
        blnY = false;
        blnAngle = false;
    }else if(key == 'a'){
        blnZ = false;
        blnX = false;
        blnY = false;
        blnAngle = true;
    }

    Vector3D v3;
    //Keys for what type of transformation will be applied
    if(mod == 1){
        if(key == 'S'){
            v3S = increase3D(v3);
            transformationv3("Scale", v3S);
        }else if(key == 'R'){
            resetRotate();
            if(blnZ)
                v4R.z+=1;
            if(blnX)
                v4R.x+=1;
            if(blnY)
                v4R.y+=1;
            if(blnAngle)
                v4R.w+=1;
            transformationv4("Rotate", v4R);
        }else if(key == 'T'){
            v3T = increase3D(v3);
            transformationv3("Translate", v3T);
        }
    }else if(mod == 4){
        if(key == 's'){
            v3S = decrease3D(v3);
            transformationv3("Scale", v3S);
        }else if(key == 'r'){
            resetRotate();
            if(blnZ)
                v4R.z-=1;
            if(blnX)
                v4R.x-=1;
            if(blnY)
                v4R.y-=1;
            if(blnAngle)
                v4R.w-=1;
            transformationv4("Rotate", v4R);
        }else if(key == 't'){
            v3T = decrease3D(v3);
            transformationv3("Translate", v3T);
        }
    }

    glutPostRedisplay();
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
    /*if(key == GLUT_KEY_DELETE){
      SG->resetScene();
      }*/
    glutPostRedisplay();
}

void MouseClickAction(int button, int state, int posX, int posY){
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state==0) SG->selectnodeAtPos(posX, posY);
            break;
        case GLUT_RIGHT_BUTTON:
            SG->deleteThisNode();
            break;
        default:
            break;
    }
    Display();
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

    glClearColor(1, 1, 0.9, 0);
    glColor3f(1, 1, 1);

    //init our scenegraph
    SG = new SceneGraph();
}

int main(int argc, char** argv){
    //glut initialization stuff:
    // set the window size, display mode, and create the window
    glutInit(&argc, argv);

    cout << "-------------------------- MENU COMMANDS --------------------------" << endl;
    cout << "RIGHT CLICK -------------------------- DELETE SELECTED NODE" << endl;
    cout << "ARROW KEYS -------------------------- ROTATE CAMERA" << endl;
    cout << "END KEY -------------------------- DECREASE THE HIGHT OF THE CAMERA" << endl;
    cout << "HOME KEY -------------------------- INCREASE THE HIGHT OF THE CAMERA" << endl;
    cout << "u KEY -------------------------- MOVE LIGHTS UP" << endl;
    cout << "j KEY -------------------------- MOVE LIGHTS DOWN" << endl;
    cout << "k KEY -------------------------- MOVE LIGHTS RIGHT" << endl;
    cout << "h KEY -------------------------- MOVE LIGHTS LEFT" << endl;
    cout << ", -------------------------- SELECT THE COLOUR/MATERIAL RED" << endl;
    cout << ". -------------------------- SELECT THE COLOUR/MATERIAL GREEN" << endl;
    cout << "/ -------------------------- SELECT THE COLOUR/MATERIAL BLUE" << endl;
    cout << "- -------------------------- DECREASE THE SELECTED COLOUR/MATERIAL" << endl;
    cout << "= -------------------------- INCREASE THE SELECTED COLOUR/MATERIAL" << endl;
    cout << "w KEY -------------------------- TOGGLE LIGHTING AND MATERIAL" << endl;
    cout << "o KEY -------------------------- LOAD SAVED SECNE" << endl;
    cout << "p KEY -------------------------- SAVE SECNE INTO FILE" << endl;
    cout << "DELETE/BACKSPACE KEY -------------------------- RESET SECNE" << endl;
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
    cout << "z KEY -------------------------- SELECT Z AXIS" << endl;
    cout << "x KEY -------------------------- SELECT X AXIS" << endl;
    cout << "y KEY -------------------------- SELECT Y AXIS" << endl;
    cout << "a KEY -------------------------- SELECT THE ANGLE" << endl;
    cout << "SHIFT z KEY -------------------------- SELECT X AND Y AXIS" << endl;
    cout << "SHIFT x KEY -------------------------- SELECT Z AND Y AXIS" << endl;
    cout << "SHIFT y KEY -------------------------- SELECT X AND Z AXIS" << endl;
    cout << "ALT s KEY -------------------------- DECREASE SCALE" << endl;
    cout << "ALT r KEY -------------------------- DECREASE ROTATE" << endl;
    cout << "ALT t KEY -------------------------- DECREASE TRANSLATE" << endl;
    cout << "SHIFT s KEY -------------------------- INCREASE SCALE" << endl;
    cout << "SHIFT r KEY -------------------------- INCREASE ROTATE" << endl;
    cout << "SHIFT t KEY -------------------------- INCREASE TRANSLATE" << endl;

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
