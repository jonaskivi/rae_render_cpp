#ifndef RAE_TRANSFORM_HPP
#define RAE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include "Animator.hpp"

namespace Rae
{

class Transform
{
public:
	int id() { return m_id; }
protected:
	void id(int set) { m_id = set; }
	int m_id;

public:
	Transform(int set_id, float set_x = 0.0f, float set_y = 0.0f, float set_z = 0.0f);

	void setPosition(glm::vec3 set);
	void setTarget(glm::vec3 set_target, float duration);
	void update(double time, double delta_time);

	void updateMatrix();

	const glm::vec3& position() { return m_position; }
	glm::mat4& modelMatrix() { return m_modelMatrix; } //TODO const

protected:
	glm::vec3 m_position;
	Animator<glm::vec3> m_positionAnimator;

	glm::mat4 m_modelMatrix;
};

}

#endif

