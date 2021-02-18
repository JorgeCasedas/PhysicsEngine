
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
#include "Player.hpp"

class Door
{
private:
	Player* playerRef;
	btHingeConstraint* hinge;
	Level* levelRef;
public:
	Entity* entity;
public:
	Door(const string name, Level& level, btVector3 position, btVector3 scale, Player& player);
	void Update();
	void Activate();
};