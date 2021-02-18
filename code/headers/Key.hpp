
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

class Key
{
private:
	Entity* entity;
	Player* playerRef;
	Level* level;
	bool active;
public:
	Key(const string name, Level& level, btVector3 position, Player& player);
	void Update();
};