#ifndef __DRAWSHAPE_H__
#define __DRAWSHAPE_H__

#include "node.h"
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

class DrawShape:public Node{
    public:
        //Constructors
        DrawShape(char *modelType, int red, int green, int blue);

        //Deconstructor
        ~DrawShape();

        //Public variables
        //Public function
        virtual void nodeSpecificCodeDown();
        void drawAxis();  // draws the axis
        void drawWireFrame(); // this draws the wireframe of the object
        virtual void nodeSpecificCodeUp();
        void lighting();
        void material();

    private:

        char *modelType;
        float red, green, blue;

        /*DrawShape drawCube();*/
        void drawCube();
        /*DrawShape drawSphere();*/
        void drawSphere();
        /*DrawShape drawCone();*/
        void drawCone();
        /*DrawShape drawTorus();*/
        void drawTorus();
        /*DrawShape drawTeapot();*/
        void drawTeapot();
};

#endif
