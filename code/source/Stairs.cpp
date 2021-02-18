
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

#include "Stairs.hpp"

Stairs::Stairs(Level& level, int numberOfStairs, float stepDistance, float width)
{

	for (int i = 0; i < numberOfStairs; i++)
	{
		string name = "stair" + to_string(i);
		Entity* step = new Entity(name, level, "../../assets/cube.obj", EntityBodyType::KINEMATIC, BasicShape::BOX);
		step->SetPosition(btVector3(1+(stepDistance*i), 0.1*i, 0));
		step->SetScale(btVector3(1, 1, width));
		steps.push_back(step);
	}

}

void Stairs::Update()
{
	for (int i = 0; i < steps.size(); i++)
	{
		steps[i]->Update();
	}
}
