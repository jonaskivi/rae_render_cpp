#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Rae
{

Transform::Transform(int set_id, float set_x, float set_y, float set_z)
: m_id(set_id),
//m_position(set_x, set_y, set_z),
m_position(0.0f, 0.0f, 5.0f),
m_modelMatrix(1.0f)
{
	setTarget(glm::vec3(set_x, set_y, set_z), 5.0f);
	updateMatrix();
}

void Transform::setPosition(glm::vec3 set)
{
	m_position = set;
}

void Transform::setTarget(glm::vec3 set_target, float duration)
{
	m_positionAnimator.init(m_position, set_target, duration);
}

void Transform::update(double time, double delta_time)
{
	if( m_positionAnimator.update((float)time) )
	{
		m_position = m_positionAnimator.value();
	}

	updateMatrix();
}

void Transform::updateMatrix()
{
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position);
}

}

