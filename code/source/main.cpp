
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

#include <memory>
#include <vector>
#include <iostream>

#include <SFML/Window.hpp>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <btBulletDynamicsCommon.h>

#include "Entity.hpp"
#include "Stairs.hpp"
#include "Platform.hpp"
#include "Door.hpp"
#include "Player.hpp"
#include "Key.hpp"

using namespace sf;
using namespace std;
using namespace glt;


int main()
{
    // Se crea la ventana y el contexto de OpenGL asociado a ella:

    sf::Window window
    (
        sf::VideoMode(1500, 720),
        "Physics Second Task",
        sf::Style::Default,
        sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core)      // Se usa OpenGL 3.2 core profile
        );

    // Se determinan las características de OpenGL disponibles en la máquina:

    if (!glt::initialize_opengl_extensions())
    {
        exit(-1);
    }

    // Se activa la sincronización vertical:

    window.setVerticalSyncEnabled(true);

    // Se crea y se configura la escena:

    shared_ptr<Level> level(new Level());

    shared_ptr<Entity> ground(new Entity("ground",*level,"../../assets/cube.obj", EntityBodyType::KINEMATIC, BasicShape::BOX));
    ground->SetScale(btVector3(8, 1, 5));
    ground->SetPosition(btVector3(-3.5, 0, 0));
    
    shared_ptr<Entity> wall1(new Entity("wall1", *level, "../../assets/cube.obj", EntityBodyType::KINEMATIC, BasicShape::BOX));
    wall1->SetScale(btVector3(0.2, 3, 1.5));
    wall1->SetPosition(btVector3(-3, 2, 1.75));

    shared_ptr<Entity> wall2(new Entity("wall2", *level, "../../assets/cube.obj", EntityBodyType::KINEMATIC, BasicShape::BOX));
    wall2->SetScale(btVector3(0.2, 1, 5));
    wall2->SetPosition(btVector3(-3, 4, 0));

    shared_ptr<Entity> wall3(new Entity("wall3", *level, "../../assets/cube.obj", EntityBodyType::KINEMATIC, BasicShape::BOX));
    wall3->SetScale(btVector3(0.2, 3, 1.5));
    wall3->SetPosition(btVector3(-3, 2, -1.75));

    shared_ptr<Entity> ground2(new Entity("ground2", *level, "../../assets/cube.obj", EntityBodyType::KINEMATIC, BasicShape::BOX));
    ground2->SetScale(btVector3(5, 0.2, 3));
    ground2->SetPosition(btVector3(15, 5, 0));

    shared_ptr<Player> player(new Player("player", *level, btVector3(0, 1, 0)));

    shared_ptr < Stairs > stairs(new Stairs(*level, 10, 0.3,2));
    
    shared_ptr < Platform > platform1(new Platform("platform1", *level, btVector3(5, 1, 0), btVector3(1, 0.2, 1), PlatformType::ONTOUCH));
    platform1->SetMovementVector(btVector3(5, 5, 0));
    
    shared_ptr < Platform > platform2(new Platform("platform2", *level, btVector3(6, 5, 0), btVector3(1, 0.2, 1), PlatformType::LOOP));
    platform2->SetMovementVector(btVector3(11, 5, 0));

    shared_ptr<Door> door(new Door("door", *level, btVector3(-3, 1, 0), btVector3(1, 1, 1), *(player.get())));
    door->entity->SetColliderScale(btVector3(0.3, 1, 1));

    shared_ptr<Key> key(new Key("key", *level, btVector3(17, 6.5, 0), *(player.get())));
 
    // Se inicializan algunos elementos de OpenGL:

    level->ResetViewport(window);

    glClearColor(0.2f, 0.2f, 0.2f, 1.f);

    bool running = true;
    int  frame = 0;

    //EVENT::KEYPRESSED will be done when pressing the key once and not while pressing
    window.setKeyRepeatEnabled(false); 

    do
    {
        // Read the user input:

        sf::Event _event;

        while (window.pollEvent(_event))
        {
            switch (_event.type)
            {
                case sf::Event::Closed:
                {
                    running = false;
                    break;
                }
                case sf::Event::Resized:
                {
                    level->ResetViewport(window);
                    break;
                }
                case sf::Event::KeyPressed: //JUMP
                {  
                    if(_event.key.code == Keyboard::Space)
                        player->Jump();
                }
            }
        }
        // Perform the simulation:

        level->dynamicsWorld->stepSimulation(1.f / 60.f);
        level->MoveCamera(player->entity->GetPosition());

        // Render the scene:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Update 
        ground->Update();
        wall1->Update();
        wall2->Update();
        wall3->Update();
        ground2->Update();
        stairs->Update();
        platform1->Update();
        platform2->Update();
        door->Update();
        player->Update();
        key->Update();
        level->Update();

        window.display();
    } while (running);

    // Se debe destruir el mundo físico antes de que se destruyan los cuerpos rígidos:

    level->dynamicsWorld.reset();

    return EXIT_SUCCESS;
}