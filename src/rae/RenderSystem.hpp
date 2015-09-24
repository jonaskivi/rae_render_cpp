#ifndef RAE_RENDERSYSTEM_HPP
#define RAE_RENDERSYSTEM_HPP

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "System.hpp"

struct NVGcontext;

namespace Rae
{

class ObjectFactory;
class Transform;
class Material;
class Mesh;
class Entity;

class RenderSystem : public System
{
public:
	RenderSystem(ObjectFactory* set_factory, GLFWwindow* set_window);
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

	void onMouseButtonPress(int set_button, int x, int y);

	int   windowPixelHeight() { return m_windowPixelHeight; }
	int   windowHeight()      { return m_windowHeight;      }
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

	int m_nroFrames;
	double m_fpsTimer;
	std::string m_fpsString;
	
	// TODO make a proper Camera Component
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::vec3 m_cameraPosition;
	float m_yawAngle;
	float m_pitchAngle;
	float m_fieldOfView;
	float m_cameraSpeed;
	float m_rotateSpeed;
};

}

#endif

