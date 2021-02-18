
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

#include "Player.hpp"

Player::Player(const string name, Level& level, btVector3 position, btVector3 scale):
	hasKey(false)
{
	entity = new Entity(name, level, "../../assets/Stich.obj", EntityBodyType::DYNAMIC, BasicShape::SPHERE);
	entity->SetPosition(position);
	entity->physics->body->setAngularFactor(0);//Disable object rotations
	levelRef = &level;
}
void Player::AddKey() 
{
	hasKey = true;
}
void Player::Update()
{
	bool left = Keyboard::isKeyPressed(sf::Keyboard::A);
	bool right = Keyboard::isKeyPressed(sf::Keyboard::D);
	bool forward = Keyboard::isKeyPressed(sf::Keyboard::W);
	bool backwards = Keyboard::isKeyPressed(sf::Keyboard::S);
	bool jump = Keyboard::isKeyPressed(sf::Keyboard::Space);


	if (right)
		entity->SetAxisVelocity(btVector3(2, 0, 0));
	if (left)
		entity->SetAxisVelocity(btVector3(-2, 0, 0));
	if (forward)
		entity->SetAxisVelocity(btVector3(0, 0, -2));
	if (backwards)
		entity->SetAxisVelocity(btVector3(0, 0, 2));
	entity->physics->body->setActivationState(1); //Activation of object

	entity->Update();
	if (canShrink)
	{
		btVector3 velocity = entity->physics->body->getLinearVelocity();

		if (trunc(velocity.getX()) == 0 && trunc(velocity.getY()) == 0 && trunc(velocity.getZ()) == 0)
		{
			shrinkCountDown += 0.01;
			if (shrinkCountDown >= 1)
			{
				StartShrinking();
			}
		}
		else 
		{
			shrinkCountDown = 0;
		}
	}
}

void Player::StartShrinking()
{
	//Cant do this loop in the level because of forward declaration
	for (int i = 0; i < levelRef->levelEntities.size(); i++)
	{
		levelRef->levelEntities[i]->startShrink = true;
	}
}

void Player::Jump()
{
	entity->AddImpulse(btVector3(0, 5, 0));
}
