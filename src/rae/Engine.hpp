#ifndef RAE_ENGINE_HPP
#define RAE_ENGINE_HPP

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ObjectFactory.hpp"
#include "core/ScreenSystem.hpp"
#include "ui/Input.hpp"

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

	void osMouseButtonPress(int set_button, float x, float y);
	void osMouseButtonRelease(int set_button, float x, float y);
	void osMouseMotion(float x, float y);
	void osScrollEvent(float scrollX, float scrollY);
	void osKeyEvent(int key, int scancode, int action, int mods);

	void onMouseEvent(const Input& input);

protected:

	GLFWwindow* m_window;

	double m_previousTime;
	double m_currentTime;

	ScreenSystem m_screenSystem;
	Input m_input;
	
	ObjectFactory m_objectFactory;

	std::vector<System*> m_systems;

	RenderSystem* m_renderSystem;

	int m_meshID; // These should go someplace else...
	int m_modelID;
	int m_materialID;
	int m_bunnyMaterialID;
	int m_buttonMaterialID;
};

}

#endif

