
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

#include "Door.hpp"

Door::Door(const string name, Level& level, btVector3 position, btVector3 scale, Player& player)
{
	//Player reference
	playerRef = &player;

	//Level reference
	levelRef = &level;

	//Set entity
	entity = new Entity(name, level, "../../assets/Door.obj", EntityBodyType::DYNAMIC, BasicShape::BOX); 

	//Adjust entity
	entity->SetPosition(position);
	entity->SetScale(scale);

	//Set hinge constrain
	const btVector3 btPivotA(0, 0, scale.getZ() / 2 +0.3);  // right at the limit of the door
	btVector3 btAxisA(0.0f, 1.0f, 0.0f);
	hinge = new btHingeConstraint(*(entity->physics->body.get()), btPivotA, btAxisA);
	hinge->setLimit(0, SIMD_PI * 0.5f);
	level.dynamicsWorld->addConstraint(hinge);

	//Set Door Unmovable
	hinge->enableAngularMotor(true, 0, 1);
	entity->physics->body->setAngularFactor(btVector3(0, 0, 0));
}
 
void Door::Update()
{	
	entity->Update();
	hinge->setDbgDrawSize(btScalar(5.f));
	btVector3 pPos = playerRef->entity->GetPosition();
	btVector3 thisPos = entity->GetPosition();

	//Get distance between the player and the door
	float playerDoorDistance = sqrt(pow(pPos.getX() - thisPos.getX(), 2) + pow(pPos.getY() - thisPos.getY(), 2) + pow(pPos.getZ() - thisPos.getZ(), 2));
	if (playerDoorDistance <= 1 && playerRef->hasKey)
	{
		Activate();
	}
	
}

void Door::Activate()
{
	hinge->enableAngularMotor(true, 10, 1);
	entity->physics->body->setAngularFactor(btVector3(0, 1, 0));

	playerRef->canShrink = true;
	
}
