
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

using namespace sf;
class Player
{
private:
	
public:
	Level* levelRef;
	Entity* entity;
	bool hasKey;
	float shrinkCountDown;
	bool canShrink;
	
public:
	Player(const string name, Level& level, btVector3 position, btVector3 scale = btVector3(1,1,1));
	void AddKey();
	void Update();
	void Jump();
	void StartShrinking();
};