
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


class Stairs
{
private:

	vector<Entity*> steps;

public:

	Stairs(Level& level, int numberOfStairs, float stepDistance, float width );
	void Update();
	
};