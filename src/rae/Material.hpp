#ifndef RAE_MATERIAL_HPP
#define RAE_MATERIAL_HPP

#include <GL/glew.h>

struct NVGcontext;
struct NVGLUframebuffer;

namespace Rae
{

class Material
{
public:
	int id() { return m_id; }
protected:
	void id(int set) { m_id = set; }
	int m_id;

public:
	Material(int set_id, int set_type); // TODO that type should be an enum... :)

	void generateFBO(NVGcontext* vg);
	void update(NVGcontext* vg, double time);

	GLuint textureID();

protected:
	NVGLUframebuffer* m_framebufferObject;
	int m_width;
	int m_height;

	int m_type; // TODO enum. Currently 0 and 1 supported!
};

}

#endif

