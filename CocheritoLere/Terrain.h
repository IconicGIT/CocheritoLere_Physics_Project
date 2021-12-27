#pragma once
#include "Bullet/include/btBulletDynamicsCommon.h"
#include "Bullet/include/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

//https://github.com/bulletphysics/bullet3/blob/master/examples/Heightfield/HeightfieldExample.cpp

typedef unsigned char byte_t;

class Terrain
{
public :
	int						upAxis;
	PHY_ScalarType			type;
	byte_t*					rawHeightfieldData;
	btScalar				minHeight;
	btScalar				maxHeight;
	btHeightfieldTerrainShape* heightfieldShape;

	static byte_t*  GetRawHeightfieldData(PHY_ScalarType type,btScalar& minHeight,btScalar& maxHeight);

};

