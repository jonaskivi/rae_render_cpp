#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#	define GLFW_INCLUDE_GLCOREARB
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include "nanovg.h"
#include "nanovg_gl.h"
#include "nanovg_gl_utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Random.hpp"
#include "Animator.hpp"
#include "Shader.hpp"
#include "ComponentType.hpp"
#include "Entity.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "ObjectFactory.hpp"
#include "System.hpp"
#include "RenderSystem.hpp"
#include "Engine.hpp"
using namespace Rae;

//----------------------------------------

Engine* g_engine = nullptr;

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
	if( g_engine == nullptr )
		return;
	g_engine->osEventResizeWindow(width, height);
}

void windowPixelSizeCallback(GLFWwindow* window, int width, int height)
{
	if( g_engine == nullptr )
		return;
	g_engine->osEventResizeWindowPixels(width, height);
}

void GLFWonMouseButton(GLFWwindow* set_window, int set_button, int set_action, int set_mods)
{
	if( g_engine == nullptr )
		return;

	double mx, my;
	glfwGetCursorPos(set_window, &mx, &my);

	//cout << "GLFWMouseButtonPress. x: " << mx << " y: " << my << "\n";
	if(set_action == GLFW_PRESS)
	{
		g_engine->onMouseButtonPress(set_button, mx, my);
	}
	else if(set_action == GLFW_RELEASE)
	{
		//TODO release for a proper click, and add a proper event system.
	}
}

int main()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	// Enable MSAA (multisample anti-aliasing)
	glfwWindowHint(GLFW_SAMPLES, 4);

	#ifndef _WIN32 // don't require this on win32, and works with more cards
	// Set OpenGL version to 2.1
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	#endif
	
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

	// Create window

	GLFWmonitor* screen     = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(screen);

	window = glfwCreateWindow( mode->width - 200, mode->height - 200, "Rae Render", nullptr, nullptr);
	
	if( window == nullptr )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	// GLEW generates GL error because it calls glGetString(GL_EXTENSIONS), we'll consume it here.
	glGetError();

	glfwSwapInterval(0);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	// Load it into a VBO

	Engine engine(window);
	
	// Set global access point just for GLFW callbacks.
	g_engine = &engine;
	glfwSetWindowSizeCallback     (window, windowSizeCallback);
	glfwSetFramebufferSizeCallback(window, windowPixelSizeCallback); // Support hi-dpi displays
	glfwSetMouseButtonCallback    (window, GLFWonMouseButton);
	
	engine.run();

	glfwTerminate();

	return 0;
}

