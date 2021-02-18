
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
class Entity;

#pragma once

#include <iostream>

#include <SFML/Window.hpp>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>
#include <Node.hpp>
//#include "Entity.hpp" cant do this so i will do a forward declaration

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>


using namespace glt;
using namespace std;

class Level
{
private:

	shared_ptr< Render_Node > scene;

	//Physics;

	btDefaultCollisionConfiguration collisionConfiguration;
	btCollisionDispatcher collisionDispatcher;
	btDbvtBroadphase overlappingPairCache;
	btSequentialImpulseConstraintSolver constraintSolver;

	btVector3 cameraOffset;
	btVector3 cameraPosition;

	btGhostPairCallback* ghostCall;

public:
	vector<Entity*> levelEntities;
	shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld;

	//----- Rigidbodies
	vector< shared_ptr< btRigidBody          > > rigidBodies;
	vector< shared_ptr< btDefaultMotionState > > motionStates;
	vector< shared_ptr< btCollisionShape     > > collisionShapes;

	bool readyToFinish;
	bool playerNotMoving;

public:
	
	Level();

	void CreateScene();
	void ResetViewport(const sf::Window& window);

	void PhysicsSetUp();

	void Add(const std::string& name, std::shared_ptr< Node > node);
	Node* GetEntity(const std::string& name);
	
	void Update();
	void MoveCamera(btVector3 vec);

	void DebugMethod();

	void DeactivateObject(const string name);
};

