#if !defined(BALL_CPP) 
#define BALL_CPP

#include "Ball.h"

#define MASS .6
#define RADIUS 1.125

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

Ball::Ball()
{
	Ball(0,RADIUS,0, WHITE, SOLID);
}

Ball::Ball(float xTmp, float yTmp, float zTmp, int colorTmp, int typeTmp)
{
	x = xTmp;
	y = yTmp;
	z = zTmp;

	color = colorTmp;
	type = typeTmp;

}
void Ball::add(btDiscreteDynamicsWorld *world)
{
	shape = new btSphereShape(RADIUS);
	motionState =
		new btDefaultMotionState(btTransform(btQuaternion(rand(),rand(),rand(),1), btVector3(x,y,z)));
	btScalar mass = MASS;
	btVector3 inertia(0,0,0);
	shape->calculateLocalInertia(mass,inertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,shape,inertia);
	rigidBody = new btRigidBody(rigidBodyCI);
	rigidBody->setRestitution(0.8);
	rigidBody->setDamping(0,0.8);
	world->addRigidBody(rigidBody);
}


void Ball::draw(){
	glPushMatrix();
	glMultMatrixf(ballMatrix);
	// draws the sphere with a red stripe
	int j, i; // iterators
	int q = 5; // slices
	int p = 10; // stacks
	float R = RADIUS; // radius

	float Color[3] = {0, 0, 0};
	switch(color)
	{
		case WHITE:
			Color[0] = 1.0; Color[1] = 1.0; Color[2] = 1.0;
			break;
		case YELLOW:
			Color[0] = 1.0; Color[1] = 1.0; Color[2] = 0.0;
			break;
		case BLUE:
			Color[0] = 0.0; Color[1] = 0.0; Color[2] = 1.0;
			break;
		case RED:
			Color[0] = 1.0; Color[1] = 0.0; Color[2] = 0.0;
			break;
		case PURPLE:
			Color[0] = 0.5; Color[1] = 0.0; Color[2] = 0.5;
			break;
		case ORANGE:
			Color[0] = 1.0; Color[1] = 0.5; Color[2] = 0.0;
			break;
		case GREEN:
			Color[0] = 0.0; Color[1] = 1.0; Color[2] = 0.0;
			break;
		case BROWN:
			Color[0] = 0.4; Color[1] = 0.2; Color[2] = 0.0;
			break;
		case BLACK:
			Color[0] = 0.0; Color[1] = 0.0; Color[2] = 0.0;
			break;
		default:
			break;
	}

	for(j = 0; j < q; j++)
	{
		if ((j < q * .25) || type == SOLID) glColor3f(Color[0], Color[1], Color[2]);
		else glColor3f(1.0, 1.0, 1.0); // white for outer area
		
		if (type == SOLID && (j > q * .55)) glColor3f(1.0, 1.0, 1.0);
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
		if (type == SOLID && (j > q * .5)) glColor3f(Color[0], Color[1],Color[2]);
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
	trans.getOpenGLMatrix(ballMatrix); // set ballMatrix to the matrix from opengl
}

void Ball::reset()
{
	rigidBody->setLinearVelocity(btVector3(0, 0, 0));
	rigidBody->setAngularVelocity(btVector3(0, 0, 0));
	delete rigidBody->getMotionState();
	motionState =
		new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(x, y, z)));
	rigidBody->setMotionState(motionState);
}

btRigidBody* Ball::getBody()
{
	return rigidBody;
}

btTransform Ball::getTrans()
{
	btTransform trans;
	rigidBody->getMotionState()->getWorldTransform(trans);
	return trans;
}

Ball::~Ball()
{
	// dynamicsWorld->removeRigidBody(rigidBody);
	// delete shape;
	// delete rigidBody;
}
#endif

