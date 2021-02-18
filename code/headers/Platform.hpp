
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

#include "Entity.hpp"

enum class PlatformType
{
	LOOP=0, //Movement will be looped
	ONTOUCH //Movement will activate on touch
};
enum class PlatformAxisRef
{
	X = 0,
	Y,
	Z
};

class Platform
{
private:

	shared_ptr<btGhostObject> activateButton;
	btTransform buttonTransform;
	shared_ptr< btCollisionShape > buttonShape;
	shared_ptr< btDefaultMotionState > buttonState;
	float scaleY; //for the ghost object positioning
	bool canMove;

	Entity* entity;
	btVector3 initialPos;
	btVector3 finalPos;

	PlatformType type;
	btVector3 forward;
	PlatformAxisRef axisRef;
	float initCoord;
	float finalCoord;
	float speed = 1;

	bool goFoward;

public:
	Platform(const string name, Level& level, btVector3 position, btVector3 scale, PlatformType type);
	void SetMovementVector(btVector3 finalPos);
	void Update();
};