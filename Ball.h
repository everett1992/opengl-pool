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
		btCollisionShape *shape;
		btMotionState *motionState;
		btRigidBody *rigidBody;
		btDiscreteDynamicsWorld *dynamicsWorld;
		btScalar ballMatrix[16];
	
	public:
		Ball();
		Ball(float x, float y, float z);
		void add(btDiscreteDynamicsWorld *dynamicsWorld);
		void draw();
		void update();
		btRigidBody* getBody();

		~Ball();
};

#endif
