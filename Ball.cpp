#if !defined(BALL_CPP) 
#define BALL_CPP

#include "Ball.h"

#define MASS 1
#define RADIUS 1.125

Ball::Ball()
{
	Ball(0,0,0);
}

Ball::Ball(float x, float y, float z)
{
	shape = new btSphereShape(RADIUS);
	motionState =
		new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(x,y,z)));
	btScalar mass = MASS;
	btVector3 inertia(0,0,0);
	shape->calculateLocalInertia(mass,inertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,shape,inertia);
	rigidBody = new btRigidBody(rigidBodyCI);
	//rigidBody->setDamping(0.2,0.0); // simulates friction
	rigidBody->setRestitution(1.0);
}
void Ball::add(btDiscreteDynamicsWorld *world)
{
	dynamicsWorld = world;
	dynamicsWorld->addRigidBody(rigidBody);
}


void Ball::draw(){
	glPushMatrix();
	glMultMatrixf(ballMatrix);
	// draws the sphere with a red stripe
	int j, i; // iterators
	int q = 5; // slices
	int p = 10; // stacks
	float R = RADIUS; // radius
	for(j = 0; j < q; j++)
	{
		if (j < q * .1) glColor3f(1.0, 0.0, 0.0);
		else glColor3f(0.0, 0.0, 0.0);

		glBegin(GL_TRIANGLE_STRIP);
		for(i = 0; i <= p; i++)
		{
			glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
					R * sin( (float)(j+1)/q * PI/2.0 ),
					R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
			glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
					R * sin( (float)j/q * PI/2.0 ),
					R * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );         
		}
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
		for(i = 0; i <= p; i++)
		{
			glVertex3f( -R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
					-R * sin( (float)(j+1)/q * PI/2.0 ),
					-R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
			glVertex3f( -R * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
					-R * sin( (float)j/q * PI/2.0 ),
					-R * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );         
		}
		glEnd();
	}
	glPopMatrix();
}

void Ball::update()
{
	btTransform trans;
	rigidBody->getMotionState()->getWorldTransform(trans);
	trans.getOpenGLMatrix(ballMatrix);
}

btRigidBody* Ball::getBody()
{
	return rigidBody;
}

Ball::~Ball()
{
	// dynamicsWorld->removeRigidBody(rigidBody);
	// delete shape;
	// delete rigidBody;
}
#endif

