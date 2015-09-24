#include <iostream>
using namespace std;
#include <math.h>
#include <assert.h>

#include "Material.hpp" // includes glew.h which is needed by nanovg headers.

#include "nanovg.h"
#include "nanovg_gl.h"
#include "nanovg_gl_utils.h"



namespace Rae
{

Material::Material(int set_id, int set_type) // TODO that type should be an enum... :)
: m_id(set_id),
m_framebufferObject(nullptr),
m_width(512),
m_height(512),
m_type(set_type)
{
	
}

void Material::generateFBO(NVGcontext* vg)
{
	m_framebufferObject = nvgluCreateFramebuffer(vg, m_width, m_height, NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
	if( m_framebufferObject == nullptr )
	{
		cout << "Could not create FBO.\n";
		assert(0);
	}
}

void Material::update(NVGcontext* vg, double time)
{
	if( m_framebufferObject == nullptr )
		return;

	float circle_size = float((cos(time) + 1.0) * 128.0);

	nvgluBindFramebuffer(m_framebufferObject);
	glViewport(0, 0, m_width, m_height);

	if(m_type == 1)
		glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	else glClearColor(0.7f, 0.3f, 0.1f, 0.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	nvgBeginFrame(vg, m_width, m_height, /*pixelRatio*/1.0f);

		nvgBeginPath(vg);
		nvgCircle(vg, float(m_width) * 0.5f, float(m_height) * 0.5f, circle_size);
		
		if(m_type == 1)
			nvgFillColor(vg, nvgRGBA(220, 45, 0, 200));
		else nvgFillColor(vg, nvgRGBA(0, 220, 45, 200));


		nvgFill(vg);

		if(m_type == 1)
		{
			nvgFontFace(vg, "sans");

			nvgFontSize(vg, 80.0f);
			nvgTextAlign(vg, NVG_ALIGN_CENTER);
			nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
			nvgText(vg, float(m_width) * 0.5f, (float(m_height) * 0.5f) + 20.0f, "Add Object", nullptr);
		}

	nvgEndFrame(vg);
	nvgluBindFramebuffer(NULL);
}

GLuint Material::textureID()
{
	if( m_framebufferObject == nullptr )
		return 0;
	return m_framebufferObject->texture;
}

}

