#ifndef RAE_ENGINE_HPP
#define RAE_ENGINE_HPP

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ObjectFactory.hpp"

namespace Rae
{

class System;
class RenderSystem;
class Entity;

class Engine
{
public:
	Engine(GLFWwindow* set_window); // TODO move the GLFWwindow into it's own Window class.

	void run();
	void update(double time, double delta_time);
	Entity& createAddObjectButton();
	Entity& createRandomBunnyEntity();
	Entity& createRandomCubeEntity();
	Entity& createEmptyEntity();

	void osEventResizeWindow(int width, int height);
	void osEventResizeWindowPixels(int width, int height);

	void onMouseButtonPress(int set_button, double x, double y);

protected:

	GLFWwindow* m_window;

	double m_previousTime;
	double m_currentTime;
	
	ObjectFactory m_objectFactory;

	std::vector<System*> m_systems;

	RenderSystem* m_renderSystem;

	int m_meshID; // These should go someplace else...
	int m_modelID;
	int m_materialID;
	int m_buttonMaterialID;
};

}

#endif

