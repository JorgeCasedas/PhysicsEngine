
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

#include "Level.hpp"

Level::Level() : 
    collisionDispatcher(&collisionConfiguration)
{
	CreateScene();
    PhysicsSetUp();
}

void Level::CreateScene()
{

	shared_ptr< Render_Node > _scene(new Render_Node);
	shared_ptr< Camera      > camera(new Camera(20.f, 1.f, 500.f, 1.f));
	shared_ptr< Light       > light(new Light);

	// Se añaden los nodos a la escena:

	_scene->add("camera", camera);
	_scene->add("light", light);

	scene = _scene;

	cameraOffset = btVector3(0, 5, 10);
	cameraPosition = cameraOffset;
	(*scene)["light"]->translate(glt::Vector3(10.f, 10.f, 10.f));
	(*scene)["camera"]->translate(glt::Vector3(cameraPosition.getX(), cameraPosition.getY(), cameraPosition.getZ()));

}

void Level::ResetViewport(const sf::Window& window)
{
	GLsizei width = GLsizei(window.getSize().x);
	GLsizei height = GLsizei(window.getSize().y);

	scene->get_active_camera()->set_aspect_ratio(float(width) / height);

	glViewport(0, 0, width, height);
}

void Level::PhysicsSetUp()
{
    dynamicsWorld = shared_ptr< btDiscreteDynamicsWorld>
        (
            new btDiscreteDynamicsWorld
            (
                &collisionDispatcher,
                &overlappingPairCache,
                &constraintSolver,
                &collisionConfiguration
            )
        );

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

	ghostCall = new btGhostPairCallback();
	dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(ghostCall);
	dynamicsWorld->performDiscreteCollisionDetection();
}

void Level::Add(const std::string& name, std::shared_ptr<Node> node)
{
	scene->add(name, node);
}

Node* Level::GetEntity(const std::string& name)
{
    return scene->get(name);
}

void Level::Update()
{
    scene->render();
}

void Level::MoveCamera(btVector3 vec)
{
	vec += cameraOffset;
	glt::Vector3 newCameraPos = glt::Vector3(vec.getX() - cameraPosition.getX(), 0  , vec.getZ() - cameraPosition.getZ());
	cameraPosition = vec;
	(*scene)["camera"]->translate(newCameraPos);
}

void Level::DebugMethod()
{
	return; //Method use for checking if things work adding a breakpoint, if the project enters here, it means the test works
}

void Level::DeactivateObject(const string name)
{
	(*scene)[name]->set_visible(false);
}

