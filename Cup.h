/*
 * Caleb Everett
 * graphics final
 *
 * Header for Cup
 * Defines 6 pockets for balls to go in.
 */

#if !defined(CUP_H)
#define CUP_H

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <math.h>

#define sideBottom_length 8
#define sideWall_length 8
#define cornerBottom_length 8
#define cornerWall_length 8

using namespace std;

class Cup
{
	private:
		//bullet stuff
		btCollisionShape *bottomShape;
		btMotionState *bottomMotionState;
		btRigidBody *bottomRigidBody;

		btCollisionShape *wallShape;
		btMotionState *wallMotionState;
		btRigidBody *wallRigidBody;

		// vertex arrays for drawing the 6 cups. sideBottom and cornerBottom are not used, cups are just shutes, balls can fall out
		static const float sideBottomVertex[sideBottom_length][3];
		static const float sideWallVertex[sideWall_length][3];
		static const float cornerBottomVertex[cornerBottom_length][3];
		static const float cornerWallVertex[cornerWall_length][3];


	public:
		Cup();
		void add(btDiscreteDynamicsWorld *dynamicsWorld);
		void draw();
};

#endif

