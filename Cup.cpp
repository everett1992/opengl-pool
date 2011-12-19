/*
 * Caleb Everett
 * Graphics Final
 *
 * Cup.cpp
 */

#if !defined(CUP_CPP)
#define CUP_CPP

#include "Cup.h"

// not used
const float Cup::sideBottomVertex[sideBottom_length][3] = {
	{  15, 0, 1.5},
	{  15, 2, 1.5},
	{16.5, 0, 1.5},
	{16.5, 2, 1.5},
	{16.5, 0, -1.5},
	{16.5, 2, -1.5},
	{  15, 0, -1.5},
	{  15, 2, -1.5}
	};

const float Cup::sideWallVertex[sideWall_length][3] = {
	{  1.5,-2,  15},
	{  1.5, 2,  15},
	{  1.5,-2,19},
	{  1.5, 2,19},
	{ -1.5,-2,19},
	{ -1.5, 2,19},
	{ -1.5,-2,  15},
	{ -1.5, 2,  15}
	};

// not used
const float Cup::cornerBottomVertex[cornerBottom_length][3] = {
	{  15, 0, 1.5},
	{  15, 2, 1.5},
	{16.5, 0, 1.5},
	{16.5, 2, 1.5},
	{16.5, 0, -1.5},
	{16.5, 2, -1.5},
	{  15, 0, -1.5},
	{  15, 2, -1.5}
	};

const float Cup::cornerWallVertex[cornerWall_length][3] = {
	{27.878, -2, 15},
	{27.878,  2, 15},
	{30,     -2, 17.121},
	{30,      2, 17.121},
	{32.121, -2, 15},
	{32.121,  2, 15},
	{30    , -2, 12.878},
	{30    ,  2, 12.878},
	};

Cup::Cup()
{
	;
}

void Cup::add(btDiscreteDynamicsWorld *world)
{
	// builds a collison mesh out of the vertex arrays.
	btTriangleMesh *mWallTriMesh = new btTriangleMesh();
	for (int i = 0, length = sideWall_length - 2; i < length; i++)
	{
		mWallTriMesh->addTriangle(
				btVector3(sideWallVertex[i][0],     sideWallVertex[i][1],     sideWallVertex[i][2]),
				btVector3(sideWallVertex[i + 1][0], sideWallVertex[i + 1][1], sideWallVertex[i + 1][2]),
				btVector3(sideWallVertex[i + 2][0], sideWallVertex[i + 2][1], sideWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(sideWallVertex[i][0],     sideWallVertex[i][1],     -sideWallVertex[i][2]),
				btVector3(sideWallVertex[i + 1][0], sideWallVertex[i + 1][1], -sideWallVertex[i + 1][2]),
				btVector3(sideWallVertex[i + 2][0], sideWallVertex[i + 2][1], -sideWallVertex[i + 2][2])
				);
	}
	for (int i = 0, length = cornerWall_length - 2; i < length; i++)
	{
		mWallTriMesh->addTriangle(
				btVector3(cornerWallVertex[i][0],     cornerWallVertex[i][1],     cornerWallVertex[i][2]),
				btVector3(cornerWallVertex[i + 1][0], cornerWallVertex[i + 1][1], cornerWallVertex[i + 1][2]),
				btVector3(cornerWallVertex[i + 2][0], cornerWallVertex[i + 2][1], cornerWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(cornerWallVertex[i][0],     cornerWallVertex[i][1],     -cornerWallVertex[i][2]),
				btVector3(cornerWallVertex[i + 1][0], cornerWallVertex[i + 1][1], -cornerWallVertex[i + 1][2]),
				btVector3(cornerWallVertex[i + 2][0], cornerWallVertex[i + 2][1], -cornerWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(-cornerWallVertex[i][0],     cornerWallVertex[i][1],     cornerWallVertex[i][2]),
				btVector3(-cornerWallVertex[i + 1][0], cornerWallVertex[i + 1][1], cornerWallVertex[i + 1][2]),
				btVector3(-cornerWallVertex[i + 2][0], cornerWallVertex[i + 2][1], cornerWallVertex[i + 2][2])
				);
		mWallTriMesh->addTriangle(
				btVector3(-cornerWallVertex[i][0],     cornerWallVertex[i][1],     -cornerWallVertex[i][2]),
				btVector3(-cornerWallVertex[i + 1][0], cornerWallVertex[i + 1][1], -cornerWallVertex[i + 1][2]),
				btVector3(-cornerWallVertex[i + 2][0], cornerWallVertex[i + 2][1], -cornerWallVertex[i + 2][2])
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


void Cup::draw()
{
	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.5, 0.2, 0.0); // green
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < sideWall_length; i++)
	{
		glVertex3f( sideWallVertex[i][0], sideWallVertex[i][1], sideWallVertex[i][2]);	
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < sideWall_length; i++)
	{
		glVertex3f( sideWallVertex[i][0], sideWallVertex[i][1], -sideWallVertex[i][2]);	
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < cornerWall_length; i++)
	{
		glVertex3f( cornerWallVertex[i][0], cornerWallVertex[i][1], cornerWallVertex[i][2]);	
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < cornerWall_length; i++)
	{
		glVertex3f( cornerWallVertex[i][0], cornerWallVertex[i][1], -cornerWallVertex[i][2]);	
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < cornerWall_length; i++)
	{
		glVertex3f( -cornerWallVertex[i][0], cornerWallVertex[i][1], cornerWallVertex[i][2]);	
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < cornerWall_length; i++)
	{
		glVertex3f( -cornerWallVertex[i][0], cornerWallVertex[i][1], -cornerWallVertex[i][2]);	
	}
	glEnd();
	glPopMatrix();
}
#endif

