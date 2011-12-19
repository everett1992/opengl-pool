/*
 * Caleb Everett
 * graphics final
 *
 * header file for Ball class
 */

#if !defined(BALL_H)
#define BALL_H

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <math.h>

#define PI 3.14

using namespace std;

class Ball
{
	private:
		// bullet objects
		btCollisionShape *shape;
		btMotionState *motionState;
		btRigidBody *rigidBody;
		btScalar ballMatrix[16];

		// color, type and position of the ball
		int color;
		int type;
		float x, y, z; // the original position of the ball
	
	public:
		Ball(); // defaults to 0, 0, 0, BLACK, STRIPE
		Ball(float x, float y, float z, int color, int type);
		void add(btDiscreteDynamicsWorld *dynamicsWorld); // add the ball to the physics world
		void draw(); // draw the ball
		void update(); // update the balls physical properties
		void reset();  // Reset the ball to it's initial position
		btRigidBody* getBody(); // Return the rigid body, used to get phyiscal properties
		btTransform  getTrans(); // Return more specific phyisc properties than getBody()

		~Ball(); // deconstructor, empty, could not debug
};

#endif

