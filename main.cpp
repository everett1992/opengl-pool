#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <math.h>
#include "Timer.h"
#include "Ball.h"
#include "Table.h"

#define PI 3.14
#define MAX_BALLS 200

using namespace std;
 
static int height, width;

static Timer timer;
static double elapsed = 0.0;
static int animationPeriod = 10;

static btBroadphaseInterface *broadphase;
static btDefaultCollisionConfiguration *collisionConfiguration;
static btSequentialImpulseConstraintSolver *solver;
static btCollisionDispatcher *dispatcher;
static btDiscreteDynamicsWorld *dynamicsWorld;

static int ball_count = 0;
static Ball balls[MAX_BALLS];
static Table table;

static float camera_angle_x = 0;
static float camera_angle_y = 0.6;

void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	glEnable(GL_DEPTH_TEST); // Enable depth testing.

    // Build the broadphase
    broadphase = new btDbvtBroadphase();
 
    // Set up the collision configuration and dispatcher
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
    // The actual physics solver
    solver = new btSequentialImpulseConstraintSolver;
 
    // The world.
    dynamicsWorld =
		new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));
 

	table.add(dynamicsWorld);
	balls[0]= Ball(0,1,0);
	ball_count++;
	//balls[1] = Ball(-0.5,50,0);
	//ball_count++;
	for (int i = 0; i < ball_count; i++)
	{
		balls[i].add(dynamicsWorld);
	}
	timer.start_clock();
}

void cleanup(void)
{
    // Clean up behind ourselves like good little programmers
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}

void drawScene(void)
{
	timer.end_clock();
	elapsed = (timer.diff().tv_sec + timer.diff().tv_nsec/1000000000.0);
	timer.start_clock();

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(0.0, -20.0, -40.0);
	gluLookAt(40 * cos(camera_angle_x) * sin(camera_angle_y),
			  40 * cos(camera_angle_y),
			  40 * sin(camera_angle_x) * sin(camera_angle_y),
			  0, 0, 0, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	table.draw();
	glPopMatrix();

	for (int i = 0; i < ball_count;  i++)
	{
		balls[i].draw();
	}

	glutSwapBuffers();
}


void animate(int value)
{
	dynamicsWorld->stepSimulation(elapsed,1);

	for (int i = 0; i < ball_count; i++)
	{
		balls[i].update();
	}

	glutTimerFunc(animationPeriod, animate, 1); // reanimate
	glutPostRedisplay();
}

void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	// set the width and height
	width = w; height = h;

	glMatrixMode(GL_MODELVIEW);
}

void keyInput(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			exit(0);
			break;
		case 'c':
			if (ball_count < MAX_BALLS){
				balls[ball_count] = Ball(2,1,0);
				balls[ball_count].add(dynamicsWorld);
				ball_count++;
			}
			break;
		case 'd':
			balls[0].getBody()->applyCentralForce(btVector3(1000,0,0));
			break;
		default:
			break;
	}
}

void specialKeyInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			if (camera_angle_y + .05 < 1.5)
				camera_angle_y += .05;
			break;
		case GLUT_KEY_DOWN:
			if (camera_angle_y - .05 > 0)
				camera_angle_y -= .05;
			break;
		case GLUT_KEY_LEFT:
			camera_angle_x += 20 / PI;
			break;
		case GLUT_KEY_RIGHT:
			camera_angle_x -= 20 / PI;
			break;
		default:
			break;
	}

}

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("ballAndTorus.cpp"); 
	setup(); 
	glutDisplayFunc(drawScene); 
	glutReshapeFunc(resize);  
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	glutTimerFunc(5, animate, 1);
	glutMainLoop(); 


 	cleanup();
    return 0;
}
