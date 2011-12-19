/*
 * Caleb Everett
 * Graphics final
 *
 * Header for Table.
 * Class draws a static table with bumpers and holes for pockets.
 */
#if !defined(TABLE_H)
#define TABLE_H

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <math.h>

#define bottomVertex_length 8
#define shortWallVertex_length 6
#define longWallVertex_length 6

using namespace std;

class Table
{
	private:
		// bullet stuff
		btCollisionShape *bottomShape;
		btMotionState *bottomMotionState;
		btRigidBody *bottomRigidBody;

		btCollisionShape *wallShape;
		btMotionState *wallMotionState;
		btRigidBody *wallRigidBody;

		// vertex arrays for different parts of the table
		static const float bottomVertex[bottomVertex_length][3];
		static const float shortWallVertex[shortWallVertex_length][3];
		static const float longWallVertex[longWallVertex_length][3];

	public:
		Table();
		void add(btDiscreteDynamicsWorld *dynamicsWorld);
		void draw();

		~Table();
};

#endif

