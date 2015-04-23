#ifndef _CONST_H
#define	_CONST_H

#include "math3D.h"
/*
 * Definitions
 */
#define WINDOW_SIZE 1000
#define WORLD_SIZE 1000
#define BASIC_DIMENSION 10
const GLfloat SPHERE_R = 1.5f;
const int SPHERE_S = 20;

/*
 * Protoypes
 */
typedef struct _vector2D{
    float x;
    float y;
}vector2D;


void posinit();

void speedinit();

float getDistance(float x1, float y1, float x2, float y2);

void BallCollision(int b1, int b2);

void collisiondetect();

void drawObjects();

void RenderScene();

void SetupRC();

void ChangeSize(GLsizei w, GLsizei h);

void TimerFunction(int value);

#endif	/* _CONST_H */
