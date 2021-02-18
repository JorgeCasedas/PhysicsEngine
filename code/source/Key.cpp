
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

#include "Key.hpp"

Key::Key(const string name, Level& level, btVector3 position, Player& player)
{
	entity = new Entity("key", level, "../../assets/key.obj", EntityBodyType::TRIGGER, BasicShape::BOX);
	entity->SetPosition(position);
	this->level = &level;
	playerRef = &player;
	active = true;
}

void Key::Update()
{
	if (active)
	{
		if (entity->physics->ghostObject->getNumOverlappingObjects() > 0)
		{
			level->DeactivateObject("key");
			playerRef->AddKey();
			active = false;
		}
		entity->Update();
	}
}
