
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

//Forward declaration
#pragma once
#include "PhxComponent.hpp"


class Entity
{
private:
	btVector3 scale;

	float collideTime;
	btVector3 InitialShrinkPos;
	

public:
	Level* level;

	PhxComponent* physics;
	//GfxComponent* graphics;

	Node* model;

	bool active;
	bool startShrink;
public:
	Entity(const std::string& EntityName, Level& level, const std::string& obj_file_path, EntityBodyType bodyType, BasicShape shape, btVector3 initialPos = btVector3(0, 0, 0));
	
public:
	void Update(); //Calls UpdatePos from the gfx component and the phx component
	void SetPosition(btVector3 newPos);

	void SetAxisVelocity(btVector3 vel);
	void SetTotalVelocity(btVector3 vel);
	void AddImpulse(btVector3 force);
	btVector3 GetPosition();
	btVector3 GetScale();
	void SetScale(btVector3 newScale);
	void SetColliderScale(btVector3 newScale);

	//Final animation method
	void ShrinkToCenter();
};