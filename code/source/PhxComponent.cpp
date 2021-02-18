
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

#include "PhxComponent.hpp"


PhxComponent::PhxComponent()
{
}

PhxComponent::PhxComponent(Level& level, EntityBodyType bodyType, BasicShape _shape, btVector3 initialPos)
{
	if (_shape == BasicShape::BOX)
		shape = shared_ptr< btCollisionShape >(new btBoxShape(btVector3(0.5, 0.5, 0.5)));
	else if (_shape == BasicShape::SPHERE)
		shape = shared_ptr< btCollisionShape >(new btSphereShape(btScalar(0.5)));
	else if (_shape == BasicShape::CAPSULE)
		shape = shared_ptr<btCollisionShape>(new btCapsuleShape(0.5, 1));

	transform.setIdentity();
	transform.setOrigin(initialPos);
	state = shared_ptr< btDefaultMotionState >(new btDefaultMotionState(transform));

	if (bodyType == EntityBodyType::DYNAMIC)
	{
		btScalar  mass = 1.f;
		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(mass, localInertia);

		btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get(), localInertia);
		body.reset(new btRigidBody(info));
		body->setRestitution(0);
		body->setFriction(1);
		body->setRollingFriction(1);
	}
	else if (bodyType == EntityBodyType::KINEMATIC)
	{
		btRigidBody::btRigidBodyConstructionInfo info(0, state.get(), shape.get());
		body.reset(new btRigidBody(info));
		body->setRestitution(0);
		body->setFriction(1);
		body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		//body->setActivationState(6);
	}
	else if (bodyType == EntityBodyType::TRIGGER) 
	{
		ghostObject =shared_ptr<btGhostObject>( new btGhostObject());
		ghostObject->setCollisionShape(shape.get());
		ghostObject->setWorldTransform(transform);
		ghostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		level.dynamicsWorld->addCollisionObject(ghostObject.get(), btBroadphaseProxy::SensorTrigger, btBroadphaseProxy::AllFilter & ~btBroadphaseProxy::SensorTrigger);
	}
	this->bodyType = bodyType;
	
	if(body!=nullptr)
		level.dynamicsWorld->addRigidBody(body.get());

	// Save the smart pointers for automatic cleanup.

	if (body != nullptr)
		level.rigidBodies.push_back(body);
	if (state != nullptr)
		level.motionStates.push_back(state);
	if (shape != nullptr)
		level.collisionShapes.push_back(shape);
}

void PhxComponent::SetPosition(btVector3 newPos)
{
	if (body != nullptr)
	{
		transform.setIdentity();
		transform.setOrigin(newPos);
		body->setWorldTransform(transform);
	}
	else if (ghostObject != nullptr)
	{
		transform.setIdentity();
		transform.setOrigin(newPos);
		ghostObject->setWorldTransform(transform);
	}
}

void PhxComponent::SetScale(btVector3 scale)
{
	shape->setLocalScaling(scale);
}

btVector3 PhxComponent::GetScale()
{
	return shape->getLocalScaling();
}
