#include "Engine.hpp"

#include <glm/glm.hpp>

#include "System.hpp"
#include "RenderSystem.hpp"
#include "Entity.hpp"
#include "Mesh.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "ComponentType.hpp"
#include "Random.hpp"

namespace Rae
{

Engine::Engine(GLFWwindow* set_window)
: m_window(set_window)
{
	m_currentTime = glfwGetTime();
	m_previousTime = m_currentTime;

	// TODO: now we only have 1 system... :)
	//m_inputSystem = new InputSystem(window, &m_objectFactory);
	//m_systems.push_back(g_input);
	
	m_renderSystem = new RenderSystem(&m_objectFactory, m_window);
	m_systems.push_back(m_renderSystem);
	
	// Load model
	Mesh& mesh = m_objectFactory.createMesh();
	mesh.loadModel("./data/models/bunny.obj");
	m_modelID = mesh.id();

	m_meshID     = m_renderSystem->createBox().id();
	m_materialID = m_renderSystem->createAnimatingMaterial(0).id();
	m_buttonMaterialID = m_renderSystem->createAnimatingMaterial(1).id();
	
	createEmptyEntity(); // hack at index 0

	createAddObjectButton(); // at index 1
	/*
	for(unsigned i = 0; i < 50; ++i)
	{
		Entity& entity = createEmptyEntity();
		//entity.addComponent( (int)ComponentType::TRANSFORM, m_objectFactory.createTransform(float(i) - 25.0f, float(i % 10) - 5.0f, 10.0f + (i % 10)).id() );
		entity.addComponent( (int)ComponentType::TRANSFORM, m_objectFactory.createTransform(getRandom(-10.0f, 10.0f), getRandom(-10.0f, 10.0f), getRandom(4.0f, 50.0f)).id() );
		if(i % 2 == 1)
			entity.addComponent( (int)ComponentType::MATERIAL, m_materialID );
		entity.addComponent( (int)ComponentType::MESH, m_meshID );
	}
	*/
}

void Engine::run()
{
	do{
		// Measure speed
		m_currentTime = glfwGetTime();
		double deltaTime = m_currentTime - m_previousTime;

		update(m_currentTime, deltaTime);

		// Swap buffers
		glfwSwapBuffers(m_window);
		glfwPollEvents();

		m_previousTime = m_currentTime;

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(m_window) == 0 );
}

void Engine::update(double time, double delta_time)
{
	if (glfwGetKey( m_window, GLFW_KEY_I ) == GLFW_PRESS)
	{
		createRandomBunnyEntity();
		/*Entity& entity = createEmptyEntity();
		entity.addComponent( (int)ComponentType::TRANSFORM, m_objectFactory.createTransform(getRandom(-10.0f, 10.0f), getRandom(-10.0f, 10.0f), getRandom(4.0f, 50.0f)).id() );
		entity.addComponent( (int)ComponentType::MATERIAL, m_materialID );
		entity.addComponent( (int)ComponentType::MESH, m_meshID );
		*/
	}

	if (glfwGetKey( m_window, GLFW_KEY_O ) == GLFW_PRESS)
	{
		m_objectFactory.destroyEntity(getRandomInt(2, m_objectFactory.entityCount() )); // Hmm. Magic number 2 is the first index with created box entities.
	}

	for(auto system : m_systems)
	{
		system->update(time, delta_time, m_objectFactory.entities() );
	}	
}

Entity& Engine::createAddObjectButton()
{
	Entity& entity = createEmptyEntity();
	Transform& transform = m_objectFactory.createTransform(0.0f, 0.0f, 5.0f);
	transform.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	entity.addComponent( (int)ComponentType::TRANSFORM, transform.id() );
	entity.addComponent( (int)ComponentType::MATERIAL, m_buttonMaterialID );
	entity.addComponent( (int)ComponentType::MESH, m_meshID );
	return entity;
}

Entity& Engine::createRandomBunnyEntity()
{
	Entity& entity = createEmptyEntity();
	entity.addComponent( (int)ComponentType::TRANSFORM, m_objectFactory.createTransform(getRandom(-10.0f, 10.0f), getRandom(-10.0f, 10.0f), getRandom(4.0f, 50.0f)).id() );
	entity.addComponent( (int)ComponentType::MATERIAL, m_materialID );
	entity.addComponent( (int)ComponentType::MESH, m_modelID );
	
	return entity;
}
	
Entity& Engine::createRandomCubeEntity()
{
	Entity& entity = createEmptyEntity();
	entity.addComponent( (int)ComponentType::TRANSFORM, m_objectFactory.createTransform(getRandom(-10.0f, 10.0f), getRandom(-10.0f, 10.0f), getRandom(4.0f, 50.0f)).id() );
	entity.addComponent( (int)ComponentType::MATERIAL, m_materialID );
	entity.addComponent( (int)ComponentType::MESH, m_meshID );
	return entity;
}

Entity& Engine::createEmptyEntity()
{
	return m_objectFactory.createEmptyEntity();			
}

void Engine::osEventResizeWindow(int width, int height)
{
	m_renderSystem->osEventResizeWindow(width, height);
}

void Engine::osEventResizeWindowPixels(int width, int height)
{
	m_renderSystem->osEventResizeWindowPixels(width, height);
}

void Engine::onMouseButtonPress(int set_button, double x, double y)
{
	//cout<<"mouse press: x: "<< x << " y: " << y <<"\n";
	
	// Have to scale input on retina screens:
	x = x * m_renderSystem->screenPixelRatio();
	y = y * m_renderSystem->screenPixelRatio();
	
	unsigned char res[4];

	m_renderSystem->renderPicking( m_objectFactory.entities() );

	//glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels((int)x, m_renderSystem->windowPixelHeight() - (int)y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

	// Decode entity ID from red and green channels!
	int pickedID = res[0] + (res[1] * 256);

	//m_renderSystem->m_pickedString = std::to_string(pickedID) + " is " + std::to_string(res[0]) + " and " + std::to_string(res[1]);

	if( pickedID == 0)
	{
		// do nothing, it's the background.
	}
	else if( pickedID == 1)
	{
		//createRandomCubeEntity(); // Hmm, we have no proper event handling yet, so entity 1 is the Add Object button!
		createRandomBunnyEntity();
	}
	else
	{
		m_objectFactory.destroyEntity( pickedID );
	}
}

} // end namespace Rae

