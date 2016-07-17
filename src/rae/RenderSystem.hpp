#ifndef RAE_RENDERSYSTEM_HPP
#define RAE_RENDERSYSTEM_HPP

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "System.hpp"
#include "Camera.hpp"

struct NVGcontext;

namespace Rae
{

class ObjectFactory;
class Transform;
class Material;
class Mesh;
class Entity;
class Input;

class RenderSystem : public System
{
public:
	RenderSystem(ObjectFactory* set_factory, GLFWwindow* set_window, Input& input);
	~RenderSystem();

	void initNanoVG();
	void init();

	void checkErrors(const char *file, int line);

	Mesh& createBox();
	Material& createAnimatingMaterial(int type);

	void update(double time, double delta_time, std::vector<Entity>& entities) override;

	void render(double time, double delta_time, std::vector<Entity>& entities);
	void renderPicking(std::vector<Entity>& entities);
	void render2d(double time, double delta_time);
	void updateCamera(double time, double delta_time);

	void renderMesh(Transform* transform, Material* material, Mesh* mesh);
	void renderMeshPicking(Transform* transform, Mesh* mesh, int entity_id);

	void osEventResizeWindow(int width, int height);
	void osEventResizeWindowPixels(int width, int height);

	void onMouseEvent(const Input& input);
	void onKeyEvent(const Input& input);

	int   windowPixelHeight() { return m_windowPixelHeight; }
	int   windowPixelWidth()  { return m_windowPixelWidth;  }
	int   windowHeight()      { return m_windowHeight;      }
	int   windowWidth()       { return m_windowWidth;       }
	float screenPixelRatio()  { return m_screenPixelRatio;  }
	
protected:

	// basic shader

	GLuint shaderID;

	GLuint modelViewMatrixUni;
	GLuint viewMatrixUni;
	GLuint modelMatrixUni;
	GLuint lightPositionUni;
	GLuint textureUni;

	// picking shader

	GLuint pickingShaderID;
	GLuint pickingModelViewMatrixUni;
	GLuint entityUni;
//public:	std::string m_pickedString;

protected:
	GLFWwindow* m_window;

	// nanovg context
	NVGcontext* vg;
	
	int m_windowWidth;
	int m_windowHeight;
	int m_windowPixelWidth;
	int m_windowPixelHeight;
	float m_screenPixelRatio;

	ObjectFactory* m_objectFactory;
	Input& m_input;

	int m_nroFrames;
	double m_fpsTimer;
	std::string m_fpsString;
	
	Camera camera;
};

}

#endif

