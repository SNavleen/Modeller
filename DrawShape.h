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
        DrawShape(char *modelType);

        //Deconstructor
        ~DrawShape();

        //Public variables
        //Public function
        virtual void nodeSpecificCodeDown();
        void drawAxis();

    private:

        char *modelType;

        /*DrawShape drawCube();*/
        void drawCube();
        /*DrawShape drawSphere();*/
        void drawSphere();
        /*DrawShape drawCone();*/
        void drawCone();
        /*DrawShape drawCylinder();*/
        void drawCylinder();
        /*DrawShape drawTorus();*/
        void drawTorus();
        /*DrawShape drawTeapot();*/
        void drawTeapot();
        /*DrawShape drawTetrahedron();*/
        void drawTetrahedron();
        /*DrawShape drawOctahedron();*/
        void drawOctahedron();
        /*DrawShape drawDodecahedron();*/
        void drawDodecahedron();
        /*DrawShape drawIcosahedron();*/
        void drawIcosahedron();
};

#endif
