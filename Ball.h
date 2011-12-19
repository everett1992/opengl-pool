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
		btScalar ballMatrix[16];
		int color;
		int type;
		float x, y, z; // the original position of the ball
	
	public:
		Ball();
		Ball(float x, float y, float z, int color, int type);
		void add(btDiscreteDynamicsWorld *dynamicsWorld);
		void draw();
		void update();
		void reset();
		btRigidBody* getBody();
		btTransform  getTrans();

		~Ball();
};

#endif
