#if !defined(TABLE_CPP) 
#define TABLE_CPP

#include "Table.h"


const float Table::bottomVertex[bottomVertex_length][3] = {
	{-27.878, 0,     -15},
	{ 27.878, 0,     -15},
	{-30    , 0, -12.878},
	{ 30    , 0, -12.878},
	{-30    , 0,  12.878},
	{ 30    , 0,  12.878},
	{-27.878    , 0,  15},
	{ 27.878    , 0,  15}
	};

const float Table::shortWallVertex[shortWallVertex_length][3] = {
	{30, 0, -12.878},
	{30, 0,  12.878},
	{30, 2, -12.878},
	{30, 2,  12.878},
	{32.121, 2, -15},
	{32.121, 2,  15}
	};

const float Table::longWallVertex[longWallVertex_length][3] = {
	{27.878, 0, 15},
	{   1.5, 0, 15},
	{27.878, 2, 15},
	{   1.5, 2, 15},
	{30, 2, 17.121},
	{   1.5, 2, 19}
	};

Table::Table()
{
	;
}

void Table::add(btDiscreteDynamicsWorld *world)
{
	btTriangleMesh *mTriMesh = new btTriangleMesh();
	for (int i = 0, length = bottomVertex_length - 2; i < length; i++)
	{
		mTriMesh->addTriangle(
				btVector3(bottomVertex[i][0], bottomVertex[i][1], bottomVertex[i][2]),
				btVector3(bottomVertex[i + 1][0], bottomVertex[i + 1][1], bottomVertex[i + 1][2]),
				btVector3(bottomVertex[i + 2][0], bottomVertex[i + 2][1], bottomVertex[i + 2][2])
				);
	}
	bottomShape = new btBvhTriangleMeshShape(mTriMesh,true);
 
	bottomMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));

	btRigidBody::btRigidBodyConstructionInfo
		bottomRigidBodyCI(0,bottomMotionState,bottomShape,btVector3(0,0,0));
	bottomRigidBody = new btRigidBody(bottomRigidBodyCI);

	bottomRigidBody->setFriction(10000.0); // high friction so that the ball rolls without sliding
	bottomRigidBody->setRestitution(0.0); // explicitly set to 0 dont know bullet default.
	                                      // makes table surface not bouncy
	
	world->addRigidBody(bottomRigidBody);
	
	
	// builds a collison mesh out of the vertex arrays.
	btTriangleMesh *mWallTriMesh = new btTriangleMesh();
	for (int i = 0, length = shortWallVertex_length - 2; i < length; i++)
	{
		mWallTriMesh->addTriangle(
				btVector3(-shortWallVertex[i][0], shortWallVertex[i][1], shortWallVertex[i][2]),
				btVector3(-shortWallVertex[i + 1][0], shortWallVertex[i + 1][1], shortWallVertex[i + 1][2]),
				btVector3(-shortWallVertex[i + 2][0], shortWallVertex[i + 2][1], shortWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(shortWallVertex[i][0], shortWallVertex[i][1], shortWallVertex[i][2]),
				btVector3(shortWallVertex[i + 1][0], shortWallVertex[i + 1][1], shortWallVertex[i + 1][2]),
				btVector3(shortWallVertex[i + 2][0], shortWallVertex[i + 2][1], shortWallVertex[i + 2][2])
				);
	}
	for (int i = 0, length = longWallVertex_length - 2; i < length; i++)
	{
		mWallTriMesh->addTriangle(
				btVector3(-longWallVertex[i][0], longWallVertex[i][1],         -longWallVertex[i][2]),
				btVector3(-longWallVertex[i + 1][0], longWallVertex[i + 1][1], -longWallVertex[i + 1][2]),
				btVector3(-longWallVertex[i + 2][0], longWallVertex[i + 2][1], -longWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(-longWallVertex[i][0], longWallVertex[i][1],         longWallVertex[i][2]),
				btVector3(-longWallVertex[i + 1][0], longWallVertex[i + 1][1], longWallVertex[i + 1][2]),
				btVector3(-longWallVertex[i + 2][0], longWallVertex[i + 2][1], longWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(longWallVertex[i][0], longWallVertex[i][1],         longWallVertex[i][2]),
				btVector3(longWallVertex[i + 1][0], longWallVertex[i + 1][1], longWallVertex[i + 1][2]),
				btVector3(longWallVertex[i + 2][0], longWallVertex[i + 2][1], longWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(longWallVertex[i][0], longWallVertex[i][1],         -longWallVertex[i][2]),
				btVector3(longWallVertex[i + 1][0], longWallVertex[i + 1][1], -longWallVertex[i + 1][2]),
				btVector3(longWallVertex[i + 2][0], longWallVertex[i + 2][1], -longWallVertex[i + 2][2])
				);
	}

	wallShape = new btBvhTriangleMeshShape(mWallTriMesh,true);
 
	wallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));

	btRigidBody::btRigidBodyConstructionInfo
		wallRigidBodyCI(0,wallMotionState,wallShape,btVector3(0,0,0));
	wallRigidBody = new btRigidBody(wallRigidBodyCI);
	wallRigidBody->setRestitution(1.0); // sets it so that the balls bounce off
	wallRigidBody->setFriction(0.0); // low friction so the balls do not stop rotating when they hit the wall
	
	world->addRigidBody(wallRigidBody);
}


void Table::draw()
{
	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLE_STRIP);
	// draws the base of the table
	glColor3f(0.0, 0.5, 0.0); // green
	for (int i = 0, length = bottomVertex_length; i < length; i++)
	{
		glVertex3f( bottomVertex[i][0], bottomVertex[i][1], bottomVertex[i][2]);	
	}
	glEnd();

	// draws the bumpers
	glColor3f(0.5, 0.2, 0.0); // brown
	for (int j = 0; j < 2; j++) // do once positive, and once negative
	{
		int n = 1;
		if (j == 0) n = -1;
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0, length = shortWallVertex_length; i < length; i++)
		{
				glVertex3f( n * shortWallVertex[i][0], shortWallVertex[i][1], shortWallVertex[i][2]);	
		}
		glEnd();
	}

	for (int j = 0; j < 2; j++) // do once positive, once negative
	{
		int n = 1;
		if (j == 0) n = -1;
		for (int m = 0; m < 2; m++)
		{
			glBegin(GL_TRIANGLE_STRIP);
			int k = 1;
			if (m == 0) k = -1;
			for (int i = 0, length = longWallVertex_length; i < length; i++)
			{
				glVertex3f( n * longWallVertex[i][0], longWallVertex[i][1], k * longWallVertex[i][2]);	
			}
			glEnd();
		}
	}
	glPopMatrix();
}

Table::~Table()
{
	// delete shape;
	// delete bottomRigidBody;
}
#endif

