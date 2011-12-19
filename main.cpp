#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <math.h>
#include "Cup.h"
#include "Timer.h"
#include "Ball.h"
#include "Table.h"

#define PI 3.14
#define RADIUS 1.125
#define MAX_BALLS 200

#define SOLID  0
#define STRIPE 1
#define CUE    2
#define EIGHT  3

#define WHITE  0
#define YELLOW 1
#define BLUE   2
#define RED    3
#define PURPLE 4
#define ORANGE 5
#define GREEN  6
#define BROWN  7
#define BLACK  8


using namespace std;
 
static int height, width;

static int mouseX, mouseY, deltaMouseX, deltaMouseY;
static bool mouse_down = false;

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
static Cup cup;

static float camera_angle_x = 0;
static float camera_angle_y = 0.6;

void rackBalls(void)
{
	balls[0]= Ball(20, RADIUS, 0, WHITE, CUE); // Ball zero acts as the cue ball
	balls[0].add(dynamicsWorld);
	ball_count++;

	float fudge = RADIUS + .08;
	float step = pow(3 * fudge, 0.5);
	int i = 0; // 15 balls to place
	float x, z;

	int types[][2] = {
		{BLUE  , STRIPE},
		{YELLOW,  SOLID},
		{GREEN , STRIPE},
		{PURPLE,  SOLID},
		{BLACK ,  SOLID}, // 8 ball
		{ORANGE,  SOLID},
		{GREEN ,  SOLID},
		{ORANGE, STRIPE},
		{BROWN ,  SOLID},
		{YELLOW, STRIPE},
		{BLUE  ,  SOLID},
		{RED   , STRIPE},
		{PURPLE, STRIPE},
		{RED   ,  SOLID},
		{BROWN , STRIPE}
		};
		
		
		
	for (int row = 0; row < 5; row++)
	{
		x = -step * row;
		z = 0 - fudge * row;
		for (int ball = 0; ball < row + 1; ball++)
		{
			balls[ball_count] = Ball(x - 10, RADIUS, z, types[i][0],types[i][1]);
			balls[ball_count].add(dynamicsWorld);
			ball_count++;
			i++;
			z += 2 * fudge;
		}
	}
}

void myTickCallback(btDynamicsWorld *world, btScalar timeStep) {
	for (int i = 0; i < ball_count; i++)
	{
		btVector3 vel = balls[i].getBody()->getLinearVelocity();
		if (vel.getY() > 0){
			vel.setY(0);
		}
		balls[i].getBody()->setLinearVelocity(vel);
	}
}

void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); 
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
    dynamicsWorld->setGravity(btVector3(0,-20,0));
	dynamicsWorld->setInternalTickCallback(myTickCallback);
 

	cup.add(dynamicsWorld);
	table.add(dynamicsWorld);
	rackBalls();

	timer.start_clock();
}

void cleanup(void)
{
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}

void drawScene(void)
{
	timer.end_clock();
	elapsed = timer.seconds();
	timer.start_clock();

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(40 * cos(camera_angle_x) * sin(camera_angle_y),
			  40 * cos(camera_angle_y),
			  40 * sin(camera_angle_x) * sin(camera_angle_y),
			  0, 0, 0, 0, 1, 0);


	glPushMatrix();
	table.draw();
	cup.draw();
	glPopMatrix();

	if (balls[0].getBody()->getLinearVelocity().length() < 0.01 &&
		balls[0].getBody()->getLinearVelocity().length() > -0.01 && 
		mouse_down){
		glPushMatrix();
		glLineWidth(3.0);
		glColor3f(0.0, 0.0, 0.5);
		float x = balls[0].getTrans().getOrigin().getX();
		float z = balls[0].getTrans().getOrigin().getZ();
		glBegin(GL_LINES);
		glVertex3f( x, RADIUS, z);
		glVertex3f(x + deltaMouseX/10.0, RADIUS, z + deltaMouseY/10.0);
		glEnd();
		glPopMatrix();

	}

	for (int i = 0; i < ball_count;  i++)
	{
		balls[i].draw();
	}

	glutSwapBuffers();
}


void animate(int value)
{
	dynamicsWorld->stepSimulation(elapsed,7);

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

void mouseControll(int button, int state, int x, int y){
	cout << "clickity" << endl;
	cout << balls[0].getBody()->getLinearVelocity().length() << endl;
	if (balls[0].getBody()->getLinearVelocity().length() < 0.01 &&
		balls[0].getBody()->getLinearVelocity().length() > -0.01){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			mouseX = x; mouseY = y;
			mouse_down = true;
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
			mouse_down = false;
			balls[0].getBody()->activate(true);
			balls[0].getBody()->applyCentralForce(btVector3(-deltaMouseX * 10, 0, -deltaMouseY * 10));
		}
	}

}

void mouseActiveControll(int x, int y)
{
	if (mouse_down)
	{
		deltaMouseX = mouseX - x;
		deltaMouseY = mouseY - y;
	}
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
				balls[ball_count] = Ball(2, 1.125, 0, BLACK, STRIPE);
				balls[ball_count].add(dynamicsWorld);
				ball_count++;
			}
			break;
		case 'd':
			balls[0].reset();
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
	glutMouseFunc(mouseControll);
	glutMotionFunc(mouseActiveControll);
	glutTimerFunc(5, animate, 1);
	glutMainLoop(); 


 	cleanup();
    return 0;
}
