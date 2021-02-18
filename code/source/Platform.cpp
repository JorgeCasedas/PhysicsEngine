
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

#include "Platform.hpp"

Platform::Platform(const string name, Level& level, btVector3 position, btVector3 scale, PlatformType type):
	scaleY(scale.getY()), canMove(true)
{
	Entity* platform = new Entity(name, level, "../../assets/cube.obj", EntityBodyType::DYNAMIC, BasicShape::BOX);
	entity = platform;
	platform->SetPosition(position);
	initialPos = position;
	platform->SetScale(scale);
	entity->physics ->body->setFriction(1);
	entity->physics->body->setRollingFriction(0);
	entity->physics->body->setGravity(btVector3(0, 0, 0));
	//entity->physics->body->setLinearFactor(btVector3(0, 0, 0));
	entity->physics->body->setAngularFactor(btVector3(0, 0, 0));
	entity->physics->body->setMassProps(1000, btVector3(0, 0, 0));
	this->type = type;

	if (type == PlatformType::ONTOUCH)
	{
		buttonShape = shared_ptr< btCollisionShape >(new btBoxShape(btVector3(0.1, 0.1, 0.1)));
		buttonTransform.setIdentity();
		buttonTransform.setOrigin(position + btVector3(0, scaleY + 0.1, 0));
		buttonState = shared_ptr< btDefaultMotionState >(new btDefaultMotionState(buttonTransform));
		activateButton = shared_ptr<btGhostObject>(new btGhostObject());
		activateButton->setCollisionShape(buttonShape.get());
		activateButton->setWorldTransform(buttonTransform);
		activateButton->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		level.dynamicsWorld->addCollisionObject(activateButton.get(), btBroadphaseProxy::SensorTrigger, btBroadphaseProxy::AllFilter & ~btBroadphaseProxy::SensorTrigger);
	}
	else
	{
		activateButton = nullptr;
		buttonShape = nullptr;
		buttonState = nullptr;
	}

}

void Platform::SetMovementVector(btVector3 finalPos)
{
	this->finalPos = finalPos;
	btVector3 rawVector = finalPos - initialPos;
	forward = rawVector / sqrtf( rawVector.getX()*rawVector.getX() + rawVector.getY() * rawVector.getY()); //Normalized vector

	//Choosing the axis to have as reference when moving the platform
	if (initialPos.getX() != finalPos.getX())
	{
		if (initialPos.getX() < finalPos.getX())
		{
			initCoord = initialPos.getX();
			finalCoord = finalPos.getX();
		}
		else
		{
			finalCoord = initialPos.getX();
			initCoord = finalPos.getX();
		}
		axisRef = PlatformAxisRef::X;
	}
	else if (initialPos.getY() != finalPos.getY())
	{
		if (initialPos.getY() < finalPos.getY())
		{
			initCoord = initialPos.getY();
			finalCoord = finalPos.getY();
		}
		else
		{
			finalCoord = initialPos.getY();
			initCoord = finalPos.getY();
		}
		axisRef = PlatformAxisRef::Y;
	}
	else if (initialPos.getZ() != finalPos.getZ())
	{
		if (initialPos.getZ() < finalPos.getZ())
		{
			initCoord = initialPos.getZ();
			finalCoord = finalPos.getZ();
		}
		else
		{
			finalCoord = initialPos.getZ();
			initCoord = finalPos.getZ();
		}
		axisRef = PlatformAxisRef::Z;
	}
}

void Platform::Update()
{

	if (axisRef == PlatformAxisRef::X) 
	{
		if (this->type == PlatformType::LOOP)
		{
			if (entity->GetPosition().getX() < initCoord + 0.1)
			{
				goFoward = true;
			}
			else if (entity->GetPosition().getX() > finalCoord - 0.1)
			{
				goFoward = false;
			}
		}
		else if (this->type == PlatformType::ONTOUCH)
		{
			if(activateButton->getNumOverlappingObjects()> 0)
			{
				goFoward = true;
			}
			else 
			{
				goFoward = false;
			}
			if (
				goFoward && entity->GetPosition().getX() < finalCoord + 0.01 ||
				!goFoward && entity->GetPosition().getX() > initCoord - 0.01
				)
				canMove = true;
			else
				canMove = false;
		}
		
	}else if (axisRef == PlatformAxisRef::Y)
	{
		if (this->type == PlatformType::LOOP)
		{
			if (entity->GetPosition().getY() < initCoord + 0.1)
			{
				goFoward = true;
			}
			else if (entity->GetPosition().getY() > finalCoord - 0.1)
			{
				goFoward = false;
			}
		}
		else if (this->type == PlatformType::ONTOUCH)
		{
			if (activateButton->getNumOverlappingObjects() > 0)
			{
				goFoward = true;
			}
			else
			{
				goFoward = false;
			}
			if (
				goFoward && entity->GetPosition().getY() < finalCoord + 0.01 ||
				!goFoward && entity->GetPosition().getY() > initCoord - 0.01
				)
				canMove = true;
			else
				canMove = false;
		}
	}
	else if (axisRef == PlatformAxisRef::Z)
	{
		if (this->type == PlatformType::LOOP)
		{
			if (entity->GetPosition().getZ() < initCoord + 0.01)
			{
				goFoward = true;
			}
			else if (entity->GetPosition().getZ() > finalCoord - 0.01)
			{
				goFoward = false;
			}
		}
		else if (this->type == PlatformType::ONTOUCH)
		{
			if (entity->GetPosition().getZ() > initCoord + 0.01)
			{
				goFoward = true;
			}
			else if (entity->GetPosition().getZ() > finalCoord - 0.01)
			{
				goFoward = false;
			}
			if (activateButton->getNumOverlappingObjects() > 0)
			{
				goFoward = true;
			}
			else
			{
				goFoward = false;
			}
			if(	
			  goFoward && entity->GetPosition().getZ() < finalCoord + 0.01 ||
			  !goFoward && entity->GetPosition().getZ() > initCoord - 0.01
			  )
				canMove = true;
			else 
				canMove = false;
		}
	}

	if (goFoward && canMove)
	{
		entity->SetTotalVelocity(forward * speed);

		if (this->type == PlatformType::ONTOUCH)
		{
			buttonTransform.setIdentity();
			buttonTransform.setOrigin(entity->GetPosition() + btVector3(0, scaleY + 0.3, 0));
			activateButton->setWorldTransform(buttonTransform);
		}
	}
	else if(!goFoward && canMove)
	{
		entity->SetTotalVelocity(-forward * speed);

		if (this->type == PlatformType::ONTOUCH)
		{
			buttonTransform.setIdentity();
			buttonTransform.setOrigin(entity->GetPosition() + btVector3(0, scaleY + 0.3, 0));
			activateButton->setWorldTransform(buttonTransform);
		}
	}
	else if (!canMove) 
	{
		entity->SetTotalVelocity(btVector3(0,0,0));
	}

	entity->Update();
}

