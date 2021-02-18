
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

#include "Entity.hpp"

Entity::Entity(const std::string& EntityName, Level& _level, const std::string& obj_file_path, EntityBodyType bodyType, BasicShape shape, btVector3 initialPos)
	: level(nullptr), scale(1,1,1), active(true), collideTime(0)
{
	level = &_level;
	shared_ptr<Model> _model(new Model_Obj(obj_file_path));
	level->Add(EntityName, _model);
	model = _level.GetEntity(EntityName);

	physics = new PhxComponent(_level,bodyType, shape, initialPos);

	_level.levelEntities.push_back(this); //Save entity in a vector for final shrink animation
}

void Entity::Update()
{
	if (active) 
	{
		btTransform physics_transform;
		glm::mat4 graphics_transform;
		if (physics->body != nullptr) 
		{
			physics_transform = physics->body->getCenterOfMassTransform();
		}
		else if (physics->ghostObject != nullptr)
		{
			physics_transform = physics->ghostObject->getWorldTransform();
		}


		//physics->body->getMotionState()->getWorldTransform(physics_transform); Not working with mass 0 objects

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		model->set_transformation(graphics_transform);


		model->translate(glt::Vector3(0, -scale.getY() / 2, 0));
		model->scale(scale.getX(), scale.getY(), scale.getZ());
		if (startShrink)
		{
			if (collideTime < 1)
				collideTime += 0.01;
			ShrinkToCenter();
		}
		else
			InitialShrinkPos = GetPosition();	
	}
}

void Entity::SetPosition(btVector3 newPos)
{	
	physics->SetPosition(newPos);
}

void Entity::SetAxisVelocity(btVector3 vel)
{
	btScalar x;
	btScalar y;
	btScalar z;

	if (vel.getX() != 0)
		x = vel.getX();
	else
		x = physics->body->getLinearVelocity().getX();

	if(vel.getY() != 0)
		y = vel.getY();
	else
		y = physics->body->getLinearVelocity().getY();

	if (vel.getZ() != 0)
		z = vel.getZ();
	else
		z = physics->body->getLinearVelocity().getZ();

	physics->body->setLinearVelocity(btVector3(x, y, z));
}

void Entity::SetTotalVelocity(btVector3 vel)
{
	physics->body->setLinearVelocity(vel);
}

void Entity::AddImpulse(btVector3 force)
{
	physics->body->applyCentralImpulse(force);
}

btVector3 Entity::GetPosition()
{
	if (physics->body != nullptr)
		return physics->body->getWorldTransform().getOrigin();
	else 
		return btVector3(0, 0, 0);
}
btVector3 Entity::GetScale()
{
	return physics->GetScale();
}

void Entity::SetScale(btVector3 newScale)
{
	physics->SetScale(newScale);
	scale = newScale;
	
}
void Entity::SetColliderScale(btVector3 newScale)
{
	physics->SetScale(newScale);
}

void Entity::ShrinkToCenter()
{
	SetPosition(lerp(InitialShrinkPos, btVector3(0,5,7), collideTime));
	SetScale(lerp(GetScale(), btVector3(0, 0, 0), 0.03* collideTime));
}
