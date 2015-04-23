/*
 *Alexander Olesen
 *CMPT 370
 *Assignment 3
 *Solar System
 */
/**
 * This module is part of the "Solar System" series.
 * Module No.: 001
 */
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include "math3D.h"
#include "camera.h"

/*
 * Definitions
 */

/*
 * "Constants"
 */
const int BASIC_DIMENSION = 10;
const GLfloat SMALL_ANGLE_INCR = 2.2f;
const GLfloat BIG_ANGLE_INCR = 0.02f;
const GLfloat DIST_INCR = 1000.0f;
const GLfloat RADII_INCR = 20.0f;
const int TIME_INTERVAL = 10;
const GLfloat SOLAR_SYSTEM_SIZE = 10000.0f;
const int WINDOW_SIZE = 800;

/*
 * New types
 */

/*
 * Color
 */
typedef struct
{
	GLfloat r, g, b;
} Color;

/*
 * Star
 */
typedef struct
{
	M3DVector3f position;
	Color color;
	GLfloat radius;
	GLfloat angle;
} Star;

/*
 * Planet
 */
typedef struct
{
	M3DVector3f position;
	Color color;
	GLfloat radius;
	GLfloat speed;
	GLfloat angle;
} Planet;

typedef Planet Satellite;

/*
 * Global variables
 */
/* Lighting values */
GLfloat whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

/* Celestial bodies */
Star theSun;
Planet Mercury;
Planet Venus;
Planet theEarth;
Satellite theMoon;
Planet Mars;

Planet Jupiter;
Satellite Io;
Satellite Europa;
Satellite Ganymede;
Satellite Callisto;

Planet Saturn;
Satellite Titan;

Planet Uranus;
Planet Neptune;

/* Visualization parameters */
int solidMode;

Camera theCamera;

/*
 * Protoypes
 */
void RenderScene();
void SetupRC();
void ChangeSize(GLsizei w, GLsizei h);
void KeyPressedStd(unsigned char key, int x, int y);

void doPaint();
void initialize();
void TimerFunc(int value);


void resetCamera(Camera *theCamera);

/*
 * Function definitions
 */


/*
 *Reset the Camera
 */
void resetCamera(Camera *camera)
{
    M3DVector4f k = { 0.0f, 0.0f, -1.0f, 0.0f };
	
    /* Initialize the camera */
    m3dLoadVector3f(camera->position, 0.0f, BASIC_DIMENSION, 0.0f);
    m3dLoadVector3f(camera->target, 0.0f, BASIC_DIMENSION, -SOLAR_SYSTEM_SIZE);
    m3dLoadIdentity44f(camera->basis);
    m3dSetMatrixColumn44f(camera->basis, k, 2);
}

/*
 * Initialize the model.
 */
void initialize()
{
	/* Celestial bodies */
	theSun.color.r = 1.0f;
	theSun.color.g = 1.0f;
	theSun.color.b = 0.0f;
	theSun.position[0] =
	theSun.position[1] =
	theSun.position[2] = 0.0f;
	theSun.radius = RADII_INCR * 10.0f;
	theSun.angle = 1.0f;
        
        /*mercury*/
	Mercury.color.r = 0.5f;
	Mercury.color.g = 0.5f;
	Mercury.color.b = 0.6f;
	Mercury.position[0] = DIST_INCR * 0.467f;
	Mercury.position[1] =
	Mercury.position[2] = 0.0f;
	Mercury.radius = RADII_INCR * 0.383f;
	Mercury.angle = 5.0f;
        
        /*venus*/
        Venus.color.r = 1.0f;
	Venus.color.g = 1.0f;
	Venus.color.b = 1.0f;
	Venus.position[0] = DIST_INCR * 0.723f;
	Venus.position[1] =
	Venus.position[2] = 0.0f;
	Venus.radius = RADII_INCR * 0.950f;
	Venus.angle = 5.0f;
        
        /*earth*/
        theEarth.color.r = 0.6f;
	theEarth.color.g = 0.8f;
	theEarth.color.b = 1.0f;
	theEarth.position[0] = DIST_INCR;
	theEarth.position[1] =
	theEarth.position[2] = 0.0f;
	theEarth.radius = RADII_INCR;
	theEarth.angle = 5.0f;

        /*moon luna*/
	theMoon.color.r = 0.4f;
	theMoon.color.g = 0.4f;
	theMoon.color.b = 0.6f; 
	theMoon.position[0] = DIST_INCR * 0.00257 + theEarth.radius;
	theMoon.position[1] =
	theMoon.position[2] = 0.0f;
	theMoon.radius = RADII_INCR * 0.273f;
	theMoon.angle = 1.0f;

        /*mars*/
        Mars.color.r = 0.6f;
	Mars.color.g = 0.8f;
	Mars.color.b = 1.0f;
	Mars.position[0] = DIST_INCR * 1.534f;
	Mars.position[1] =
	Mars.position[2] = 0.0f;
	Mars.radius = RADII_INCR * 0.532f;
	Mars.angle = 5.0f;
        
        /*jupiter*/
        Jupiter.color.r = 1.0f;
	Jupiter.color.g = 1.0f;
	Jupiter.color.b = 0.8f;
	Jupiter.position[0] = DIST_INCR * 5.2f;
	Jupiter.position[1] =
	Jupiter.position[2] = 0.0f;
	Jupiter.radius = RADII_INCR * 10.882f;
	Jupiter.angle = 5.0f;
        
        /*io*/
        Io.color.r = 1.0f;
	Io.color.g = 1.0f;
	Io.color.b = 0.2f;
	Io.position[0] = DIST_INCR * 0.002820f + Jupiter.radius;
	Io.position[1] =
	Io.position[2] = 0.0f;
	Io.radius = RADII_INCR * 0.245f;
	Io.angle = 5.0f;
        
        /*europa*/
        Europa.color.r = 0.8f;
	Europa.color.g = 0.8f;
	Europa.color.b = 0.8f;
	Europa.position[0] = DIST_INCR * 0.00448f + Jupiter.radius;
	Europa.position[1] =
	Europa.position[2] = 0.0f;
	Europa.radius = RADII_INCR * 0.245f;
	Europa.angle = 2.0f;
        
        /*ganymede*/
        Ganymede.color.r = 0.6f;
	Ganymede.color.g = 0.7f;
	Ganymede.color.b = 0.6f;
	Ganymede.position[0] = DIST_INCR * 0.00715f + Jupiter.radius;
	Ganymede.position[1] =
	Ganymede.position[2] = 0.0f;
	Ganymede.radius = RADII_INCR * 0.413f;
	Ganymede.angle = 3.0f;
        
        /*callisto*/
        Callisto.color.r = 0.5f;
	Callisto.color.g = 0.5f;
	Callisto.color.b = 0.6f;
	Callisto.position[0] = DIST_INCR * 0.0126f + Jupiter.radius;
	Callisto.position[1] =
	Callisto.position[2] = 0.0f;
	Callisto.radius = RADII_INCR * 0.378f;
	Callisto.angle = 4.0f;
        
        /*saturn*/
        Saturn.color.r = 0.8f;
	Saturn.color.g = 0.8f;
	Saturn.color.b = 0.6f;
	Saturn.position[0] = DIST_INCR * 9.582f;
	Saturn.position[1] =
	Saturn.position[2] = 0.0f;
	Saturn.radius = RADII_INCR * 9.449f;
	Saturn.angle = 5.0f;
        
        /*titan*/
        Titan.color.r = 0.9f;
	Titan.color.g = 0.8f;
	Titan.color.b = 0.5f;
	Titan.position[0] = DIST_INCR * 0.00817f + Saturn.radius;
	Titan.position[1] =
	Titan.position[2] = 0.0f;
	Titan.radius = RADII_INCR * 0.404f;
	Titan.angle = 5.0f;
        
        /*uranus*/
        Uranus.color.r = 0.6f;
	Uranus.color.g = 0.7f;
	Uranus.color.b = 1.0f;
	Uranus.position[0] = DIST_INCR * 19.229f;
	Uranus.position[1] =
	Uranus.position[2] = 0.0f;
	Uranus.radius = RADII_INCR * 3.929f;
	Uranus.angle = 5.0f;
        
        /*neptune*/
        Neptune.color.r = 0.5f;
	Neptune.color.g = 0.6f;
	Neptune.color.b = 1.0f;
	Neptune.position[0] = DIST_INCR * 30.103f;
	Neptune.position[1] =
	Neptune.position[2] = 0.0f;
	Neptune.radius = RADII_INCR * 3.883f;
	Neptune.angle = 5.0f;
        
        
	/* Additional parameters/variables */
	solidMode = 1;
         /* Initialize the camera */
         resetCamera(&theCamera);
	
}

/*
 * Paints the "model".
 */
void doPaint()
{
    /* Taking care of the viewing/camera transformation */
    glPushMatrix();

    /* Paint the sun */
    glRotated(theSun.angle, 0.0, 1.0, 0.0);
    glDisable(GL_LIGHTING);
    glColor3f(theSun.color.r, theSun.color.g, theSun.color.b);
    if (solidMode)
	glutSolidSphere(theSun.radius, 20, 20);
    else
        glutWireSphere(theSun.radius, 20, 20);
    glEnable(GL_LIGHTING);

    /* Move the light after we draw the sun! */
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

    
    
    
/*-----------------------------------------------------------------------*/
    
    /*paint mercury*/
    glPushMatrix();
    glRotated(Mercury.angle, 0.0, 1.0, 0.0);
    glTranslated(Mercury.position[0], Mercury.position[1], Mercury.position[2]);
    glRotated(Mercury.angle, 0.0, 1.0, 0.0);
    glColor3f(Mercury.color.r, Mercury.color.g, Mercury.color.b);
    if (solidMode)
	glutSolidSphere(Mercury.radius, 20, 20);
    else
	glutWireSphere(Mercury.radius, 20, 20);
    glPopMatrix();/*pop mercury*/
    
    
    /*paint venus*/
    glPushMatrix();
    glRotated(Venus.angle, 0.0, 1.0, 0.0);
    glTranslated(Venus.position[0], Venus.position[1], Venus.position[2]);
    glRotated(Venus.angle, 0.0, 1.0, 0.0);
    glColor3f(Venus.color.r, Venus.color.g, Venus.color.b);
    if (solidMode)
	glutSolidSphere(Venus.radius, 20, 20);
    else
	glutWireSphere(Venus.radius, 20, 20);
    glPopMatrix();/*pop venus*/
    
    
    /* Paint the earth */
    glPushMatrix();
    glRotated(theEarth.angle, 0.0, 1.0, 0.0);
    glTranslated(theEarth.position[0], theEarth.position[1], theEarth.position[2]);
    glRotated(theEarth.angle, 0.0, 1.0, 0.0);
    glColor3f(theEarth.color.r, theEarth.color.g, theEarth.color.b);
    if (solidMode)
	glutSolidSphere(theEarth.radius, 20, 20);
    else
	glutWireSphere(theEarth.radius, 20, 20);

    
    /* Paint the moon */
    glPushMatrix();
    glRotated(45.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    glRotated(theMoon.angle, 0.0, 1.0, 0.0);
    glTranslated(theMoon.position[0], theMoon.position[1], theMoon.position[2]);
    glColor3f(theMoon.color.r, theMoon.color.g, theMoon.color.b);
    if (solidMode)
	glutSolidSphere(theMoon.radius, 20, 20);
    else
	glutWireSphere(theMoon.radius, 20, 20);
    glPopMatrix();/*pop moon*/
    glPopMatrix();/*pop moon*/
    glPopMatrix();/*pop earth*/
    
    /*paint mars*/
    glPushMatrix();
    glRotated(Mars.angle, 0.0, 1.0, 0.0);
    glTranslated(Mars.position[0], Mars.position[1], Mars.position[2]);
    glRotated(Mars.angle, 0.0, 1.0, 0.0);
    glColor3f(Mars.color.r, Mars.color.g, Mars.color.b);
    if (solidMode)
	glutSolidSphere(Mars.radius, 20, 20);
    else
	glutWireSphere(Mars.radius, 20, 20);
    glPopMatrix(); /*pop mars*/
    
    
    /*paint jupiter*/
    glPushMatrix();
    glRotated(Jupiter.angle, 0.0, 1.0, 0.0);
    glTranslated(Jupiter.position[0], Jupiter.position[1], Jupiter.position[2]);
    glRotated(Jupiter.angle, 0.0, 1.0, 0.0);
    glColor3f(Jupiter.color.r, Jupiter.color.g, Jupiter.color.b);
    if (solidMode)
	glutSolidSphere(Jupiter.radius, 20, 20);
    else
	glutWireSphere(Jupiter.radius, 20, 20);
    
    /*paint io*/
    glPushMatrix();
    glRotated(12.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    glRotated(Io.angle, 0.0, 1.0, 0.0);
    glTranslated(Io.position[0], Io.position[1], Io.position[2]);
    glColor3f(Io.color.r, Io.color.g, Io.color.b);
    if (solidMode)
	glutSolidSphere(Io.radius, 20, 20);
    else
	glutWireSphere(Io.radius, 20, 20);
    glPopMatrix();/*pop moon*/
    
    /*paint europa*/
    glPushMatrix();
    glRotated(5.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    glRotated(Europa.angle, 0.0, 1.0, 0.0);
    glTranslated(Europa.position[0], Europa.position[1], Europa.position[2]);
    glColor3f(Europa.color.r, Europa.color.g, Europa.color.b);
    if (solidMode)
	glutSolidSphere(Europa.radius, 20, 20);
    else
	glutWireSphere(Europa.radius, 20, 20);
    glPopMatrix();/*pop moon*/
    
    /*paint ganymede*/
    glPushMatrix();
    glRotated(15.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    glRotated(Ganymede.angle, 0.0, 1.0, 0.0);
    glTranslated(Ganymede.position[0], Ganymede.position[1], Ganymede.position[2]);
    glColor3f(Ganymede.color.r, Ganymede.color.g, Ganymede.color.b);
    if (solidMode)
	glutSolidSphere(Ganymede.radius, 20, 20);
    else
	glutWireSphere(Ganymede.radius, 20, 20);
    glPopMatrix();/*pop moon*/
    
    /*paint callisto*/
    glPushMatrix();
    glRotated(20.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    glRotated(Callisto.angle, 0.0, 1.0, 0.0);
    glTranslated(Callisto.position[0], Callisto.position[1], Callisto.position[2]);
    glColor3f(Callisto.color.r, Callisto.color.g, Callisto.color.b);
    if (solidMode)
	glutSolidSphere(Callisto.radius, 20, 20);
    else
	glutWireSphere(Callisto.radius, 20, 20);
    glPopMatrix();/*pop moon*/
    glPopMatrix();/*pop jupiter*/
    
    /*paint saturn*/
    glPushMatrix();
    glRotated(Saturn.angle, 0.0, 1.0, 0.0);
    glTranslated(Saturn.position[0], Saturn.position[1], Saturn.position[2]);
    glRotated(Saturn.angle, 0.0, 1.0, 0.0);
    glColor3f(Saturn.color.r, Saturn.color.g, Saturn.color.b);
    if (solidMode)
	glutSolidSphere(Saturn.radius, 20, 20);
    else
	glutWireSphere(Saturn.radius, 20, 20);
    /*Rings*/
  
    /*glPushMatrix();
    glRotated(0.0, 90.0, 0.0, 1.0);
    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);     	
      glColor4f(1.0f, 1.0f, 1.0f, 0.6);
      glVertex3f(Saturn.radius + 30 + 120.0f,  0, 0);
      glColor4f(1.0f, 1.0f, 1.0f, 0.6);
      glVertex3f(Saturn.radius + 120 + 30.0f,  0, 0);
      
      glEnd();
    
    glPopMatrix();*/
    
    /*paint titan*/
    glPushMatrix();
    glRotated(15.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    glRotated(Titan.angle, 0.0, 1.0, 0.0);
    glTranslated(Titan.position[0], Titan.position[1], Titan.position[2]);
    glColor3f(Titan.color.r, Titan.color.g, Titan.color.b);
    if (solidMode)
	glutSolidSphere(Titan.radius, 20, 20);
    else
	glutWireSphere(Titan.radius, 20, 20);
    glPopMatrix();/*pop moon*/
    
    
    glPopMatrix();/*pop saturn*/
    
    /*paint uranus*/
    glPushMatrix();
    glRotated(Uranus.angle, 0.0, 1.0, 0.0);
    glTranslated(Uranus.position[0], Uranus.position[1], Uranus.position[2]);
    glRotated(Uranus.angle, 0.0, 1.0, 0.0);
    glColor3f(Uranus.color.r, Uranus.color.g, Uranus.color.b);
    if (solidMode)
	glutSolidSphere(Uranus.radius, 20, 20);
    else
	glutWireSphere(Neptune.radius, 20, 20);
    glPopMatrix();/*pop uranus*/
    
    /*paint neptune*/
    glPushMatrix();
    glRotated(Neptune.angle, 0.0, 1.0, 0.0);
    glTranslated(Neptune.position[0], Neptune.position[1], Neptune.position[2]);
    glRotated(Neptune.angle, 0.0, 1.0, 0.0);
    glColor3f(Neptune.color.r, Neptune.color.g, Neptune.color.b);
    if (solidMode)
	glutSolidSphere(Neptune.radius, 20, 20);
    else
	glutWireSphere(Neptune.radius, 20, 20);
    glPopMatrix();/*pop neptune*/
    
    
    glPopMatrix();/*pop sun*/
    glPopMatrix();
}

/*
 * Renders the model/scene.
 */
void RenderScene()
{
    /* Clear the color buffer and depth buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Draw the object(s) */
    doPaint();

    /* Update the screen */
    glutSwapBuffers();
}

/*
 * Initializes the rendering context.
 */
void SetupRC()
{
    /* Set the background color */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /* Set color shading model to flat */
    glShadeModel(GL_SMOOTH);

    /* Counter-clockwise polygons are front facing */
    glFrontFace(GL_CCW);

	/* Enable depth buffer test */
	glEnable(GL_DEPTH_TEST);

	/* Enable culling */
	glEnable(GL_CULL_FACE);

	/* Lighting stuff */
	/* Enable lighting */
	glEnable(GL_LIGHTING);

	/* Set light model to use ambient light specified by ambientLight[] */
	/* Setup and enable light 0 */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	/* Enable material color tracking */
	glEnable(GL_COLOR_MATERIAL);

	/* Front material ambient and diffuse colors track glColor */
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
}

/*
 * Resizes the window.
 * @param w Width of the window.
 * @param h Height of the window.
 */
void ChangeSize(GLsizei w, GLsizei h)
{ glutKeyboardFunc(KeyPressedStd);
    GLdouble zNear = 1.0;
    GLdouble zFar = 3*SOLAR_SYSTEM_SIZE;
	GLdouble angle = 45.0;
    GLdouble aspectRatio;

    /* Prevent a divide by zero, when window is too short you cant make a
     * window of zero width)
     */
    if (h == 0)
    	h = 1;

    /* Set the viewport to be the entire window */
    glViewport(0, 0, w, h);

    /* Select the projection matrix */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Calculate the aspect ratio of the window */
    aspectRatio = (GLfloat)w / (GLfloat)h;

    /* Set the projection */
    gluPerspective(angle, aspectRatio, zNear, zFar);

    /* Select the modelviw matrix */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Look at... */
    cmrLookAt(&theCamera);

    /* Select the modelview matrix */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * Callback used for key pressed event.
 * @param key ASCII code of the key.
 * @param x X-coordinate of the mouse in the window.
 * @param y Y-coordinate of the mouse in the window.
 */
void KeyPressedStd(unsigned char key, int x, int y)
{
    if (key == '1'){
        solidMode = 1;
    }
    else if (key == '2'){
        solidMode = 0;
    }

    /* Check the key pressed */
    if (key == 'r') {
        /* Reset visualization parameters */
		resetCamera(&theCamera);		
    }
    else if (key == 'w') {
		/* Move camera forward */
		cmrMove(&theCamera, Z_LOCAL_AXIS, BASIC_DIMENSION*5);
    }
    else if (key == 'W') {
    /* Move camera forward FAST*/
		cmrMove(&theCamera, Z_LOCAL_AXIS, BASIC_DIMENSION*100);
    }    
    else if (key == 's') {
		/* Move camera backward */
		cmrMove(&theCamera, Z_LOCAL_AXIS, -BASIC_DIMENSION*5);
    }
    else if (key == 'q') {
		/* Move camera left */
		cmrMove(&theCamera, X_LOCAL_AXIS, -BASIC_DIMENSION*5);
    }
    else if (key == 'e') {
		/* Move camera right */
		cmrMove(&theCamera, X_LOCAL_AXIS, BASIC_DIMENSION*5);
    }
    else if (key == 'm') {
		/* Move camera up */
		cmrMove(&theCamera, Y_LOCAL_AXIS, BASIC_DIMENSION);
    }
    else if (key == 'n') {
		/* Move camera down */
		cmrMove(&theCamera, Y_LOCAL_AXIS, -BASIC_DIMENSION);
    }
    else if (key == 'a') {
		/* Turn camera left */
		cmrTurn(&theCamera, Y_LOCAL_AXIS, SMALL_ANGLE_INCR);
    }
    else if (key == 'd') {
		/* Turn camera right */
		cmrTurn(&theCamera, Y_LOCAL_AXIS, -SMALL_ANGLE_INCR);
    }
    else if (key == 'g') {
		/* Turn camera up */
		cmrTurn(&theCamera, X_LOCAL_AXIS, SMALL_ANGLE_INCR);
    }
    else if (key == 't') {
		/* Turn camera down */
		cmrTurn(&theCamera, X_LOCAL_AXIS, -SMALL_ANGLE_INCR);
    }
    else if (key == 'v') {
		/* Turn camera CCW */
		cmrTurn(&theCamera, Z_LOCAL_AXIS, -SMALL_ANGLE_INCR);
    }
    else if (key == 'b') {
		/* Turn camera CW */
		cmrTurn(&theCamera, Z_LOCAL_AXIS, SMALL_ANGLE_INCR);
    }
    else if (key == '1') {
        solidMode = 1;
    }
    else if (key == '2') {
	solidMode = 0;
    }
    else if (key == 'x') {
		exit(0);
    }
    else {
		return;
    }
    cmrLookAt(&theCamera);	
    glutPostRedisplay();
}
/*
 * Timer function.
 */
void TimerFunc(int value)
{
    /* Update angles */
    //theSun.angle += SMALL_ANGLE_INCR;
    
    Mercury.angle += BIG_ANGLE_INCR / 0.241f;
    Venus.angle += BIG_ANGLE_INCR / 0.615f;
            
    theEarth.angle += BIG_ANGLE_INCR;
    theMoon.angle += BIG_ANGLE_INCR /0.0795;
    
    Mars.angle += BIG_ANGLE_INCR / 1.881f;
    
    Jupiter.angle += BIG_ANGLE_INCR / 11.862f;
    Io.angle += BIG_ANGLE_INCR / 0.00489;
    Europa.angle += BIG_ANGLE_INCR / 0.00972;
    Ganymede.angle += BIG_ANGLE_INCR / 0.0196;
    Callisto.angle += BIG_ANGLE_INCR / 0.457;        
    
    Saturn.angle += BIG_ANGLE_INCR / 29.457f;
    Titan.angle += BIG_ANGLE_INCR / 0.0437;
    
    Uranus.angle += BIG_ANGLE_INCR / 84.323f;
    
    Neptune.angle += BIG_ANGLE_INCR / 164.79f;
	/* Force it to redisplay */
	glutPostRedisplay();

	/* Do it again... */
	glutTimerFunc(TIME_INTERVAL, TimerFunc, 1);
}

/*
 * Main function.
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return Status code.
 */
int main (int argc, char **argv)
{
	/* Initialize the model */
	initialize();

    /* Initialization process */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutCreateWindow("Solar System");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(KeyPressedStd);
    glutTimerFunc(TIME_INTERVAL, TimerFunc, 1);

    SetupRC();

    /* "Main" loop */
    glutMainLoop();

    return EXIT_SUCCESS;
}
/* End of file -------------------------------------------------------------- */


