
/**********************************************************************
*Project           : PhysicsTask
*
* Author : Jorge Cásedas
*
*Starting date : 25/05/2020
*
*Ending date : 29/05/2020
*
*Purpose : Controlling player that moves around a responsive enviroment.
*
**********************************************************************/

#pragma once
#include <memory>
#include <btBulletDynamicsCommon.h>
#include "Level.hpp"
using namespace std;

enum class EntityBodyType
{
	KINEMATIC,
	DYNAMIC,
	TRIGGER
};
enum class BasicShape
{
	BOX,
	SPHERE,
	CAPSULE
};

class PhxComponent
{

private:
	
	shared_ptr< btCollisionShape > shape;
	
	shared_ptr< btDefaultMotionState > state;

public:
	shared_ptr< btRigidBody > body;				//For collision object
	shared_ptr< btGhostObject > ghostObject;	//For trigger object
	EntityBodyType bodyType;
	btTransform transform;
public:
	PhxComponent();

	PhxComponent(Level& level,EntityBodyType bodyType, BasicShape shape, btVector3 initialPos = btVector3(0, 0, 0));

	void SetPosition(btVector3 newPos);
	void SetScale(btVector3 scale);
	btVector3 GetScale();
};