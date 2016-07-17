#pragma once

//#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "core/Utils.hpp"

namespace Rae
{

class Camera
{
public:

	Camera(float fieldOfViewRadians, float setAspectRatio, float aperture, float focusDistance)
	: m_fieldOfView(fieldOfViewRadians),
	m_aspectRatio(setAspectRatio),
	m_aperture(aperture),
	m_focusDistance(focusDistance),
	m_yawAngle(0.0f),
	m_pitchAngle(0.0f),
	m_cameraSpeed(2.0f),
	m_rotateSpeed(1.0f)
	{
		calculateFrustum();
	}

	void calculateFrustum()
	{
		m_lensRadius = m_aperture / 2.0f;

		// Direction : Spherical coordinates to Cartesian coordinates conversion
		direction = vec3(
			cos(m_pitchAngle) * sin(m_yawAngle), 
			sin(m_pitchAngle),
			cos(m_pitchAngle) * cos(m_yawAngle)
		);
		
		// Right vector
		right = glm::vec3(
			sin(m_yawAngle - 3.14f/2.0f),
			0,
			cos(m_yawAngle - 3.14f/2.0f)
		);

		// Up vector
		up = glm::cross( right, direction );

		m_projectionMatrix = glm::perspective(Math::toDegrees(m_fieldOfView), m_aspectRatio, 0.1f, 500.0f);
		m_viewMatrix = glm::lookAt( m_position, m_position + direction, up );

		//

		vec3 w;
		float halfHeight = tan(m_fieldOfView / 2.0f);

		float halfWidth = m_aspectRatio * halfHeight;
		w = normalize(m_position - (m_position + direction));
		
		// Normal way: m_topLeftCorner = m_position - (halfWidth * right) + (halfHeight * up) - w;
		m_topLeftCorner =
			m_position
			- (halfWidth * m_focusDistance * right)
			+ (halfHeight * m_focusDistance * up)
			- (m_focusDistance * w);
		/*
		m_lowerLeftCorner =
			m_position
			- (halfWidth * m_focusDistance * right)
			- (halfHeight * m_focusDistance * up)
			- (m_focusDistance * w);
		*/
		
		horizontal = 2.0f * halfWidth * m_focusDistance * right;
		vertical = 2.0f * halfHeight * m_focusDistance * up;

		m_needsUpdate = false;
	}

	// return true if frustum was updated
	bool update()
	{
		bool ret = m_needsUpdate;
		if (m_needsUpdate)
		{
			calculateFrustum();
		}
		return ret;
	}

	void needsUpdate() { m_needsUpdate = true; }

	const vec3& position() { return m_position; }
	void setPosition(vec3 pos)
	{
		if (pos != m_position)
		{
			m_needsUpdate = true;
			m_position = pos;
		}
	}

	void moveForward(float delta)
	{
		if (delta > 0.0f)
		{
			m_needsUpdate = true;
			m_position += delta * direction * cameraSpeed();
		}	
	}

	void moveBackward(float delta)
	{
		if (delta > 0.0f)
		{
			m_needsUpdate = true;
			m_position -= delta * direction * cameraSpeed();
		}	
	}

	void moveRight(float delta)
	{
		if (delta > 0.0f)
		{
			m_needsUpdate = true;
			m_position += delta * right * cameraSpeed();
		}	
	}

	void moveLeft(float delta)
	{
		if (delta > 0.0f)
		{
			m_needsUpdate = true;
			m_position -= delta * right * cameraSpeed();
		}	
	}

	void moveUp(float delta)
	{
		if (delta > 0.0f)
		{
			m_needsUpdate = true;
			m_position += delta * up * cameraSpeed();
		}	
	}

	void moveDown(float delta)
	{
		if (delta > 0.0f)
		{
			m_needsUpdate = true;
			m_position -= delta * up * cameraSpeed();
		}	
	}

	void rotateYaw(double delta_time, float dir)
	{
		m_needsUpdate = true;
		m_yawAngle += float(delta_time) * m_rotateSpeed * dir;
	}

	void rotatePitch(float delta_time, float dir)
	{
		m_needsUpdate = true;
		m_pitchAngle += float(delta_time) * m_rotateSpeed * dir;
	}

	void rotateYaw(float delta)
	{
		m_needsUpdate = true;
		m_yawAngle += delta;
	}

	void rotatePitch(float delta)
	{
		m_needsUpdate = true;
		m_pitchAngle += delta;
	}

	float yaw() { return m_yawAngle; }
	void setYaw(float set) { m_yawAngle = set; m_needsUpdate = true; }
	float pitch() { return m_pitchAngle; }
	void setPitch(float set) { m_pitchAngle = set; m_needsUpdate = true; }

	void setCameraSpeedUp(bool set) { m_cameraSpeedUp = set; }
	void setCameraSpeedDown(bool set) { m_cameraSpeedDown = set; }

	float cameraSpeed()
	{
		if (m_cameraSpeedUp)
			return m_cameraSpeed * 10.0f;
		else if (m_cameraSpeedDown)
			return m_cameraSpeed * 0.1f;
		return m_cameraSpeed;
	}

	void setAspectRatio(float aspect)
	{
		m_aspectRatio = aspect;
	}

	float fieldOfView() { return m_fieldOfView; } // in radians

	// also handles negative input unlike other similar funcs
	void plusFieldOfView(float delta = 0.1f)
	{
		if ((m_fieldOfView + delta) >= Math::toRadians(1.0f))
		{
			if ((m_fieldOfView + delta) <= Math::toRadians(180.0f))
			{
				m_fieldOfView += delta;
			}
			else m_fieldOfView = Math::toRadians(180.0f);
		}
		else m_fieldOfView = Math::toRadians(1.0f);
		m_needsUpdate = true;
	}

	void minusFieldOfView(float delta = 0.1f)
	{
		if ((m_fieldOfView - delta) >= Math::toRadians(1.0f))
		{
			if ((m_fieldOfView - delta) <= Math::toRadians(180.0f))
			{
				m_fieldOfView -= delta;
			}
			else m_fieldOfView = Math::toRadians(180.0f);
		}
		else m_fieldOfView = Math::toRadians(1.0f);
		m_needsUpdate = true;
	}

	float aperture() { return m_aperture; }
	void setAperture(float set) { m_aperture = set; m_needsUpdate = true; }

	void plusAperture(float delta = 0.01f)
	{
		m_aperture += delta;
		m_needsUpdate = true;
	}

	void minusAperture(float delta = 0.01f)
	{
		if ((m_aperture - delta) >= 0.0f)
			m_aperture -= delta;
		else m_aperture = 0.0f;
		m_needsUpdate = true;
	}

	void plusFocusDistance(float delta = 0.01f)
	{
		m_focusDistance += delta;
		m_needsUpdate = true;
	}

	const float MinFocusDistance = 0.01f;
	void minusFocusDistance(float delta = 0.01f)
	{
		if ((m_focusDistance - delta) >= MinFocusDistance)
			m_focusDistance -= delta;
		else m_focusDistance = MinFocusDistance;
		m_needsUpdate = true;
	}

	void setFocusDistance(float distance)
	{
		m_focusDistance = distance;
		m_needsUpdate = true;
	}	

	void setFocusPosition(vec3 pos)
	{
		m_focusDistance = length(m_position - pos);
		m_needsUpdate = true;
	}
	
	vec3 getFocusPosition()
	{
		return m_position + (direction * m_focusDistance);
	}

	float focusDistance() { return m_focusDistance; }

// TODO protected:

	vec3 direction = vec3(0.0f, 0.0f, -1.0f);
	vec3 right = vec3(1,0,0); // u
	vec3 up = vec3(0,1,0); // v

	// This is a bit more constant. The world up, not the camera up.
	vec3 upAxis = vec3(0.0f, 1.0f, 0.0f);

	//vec3 m_lowerLeftCorner = vec3(-2.0f, -1.0f, -1.0f);
	vec3 m_topLeftCorner = vec3(-2.0f, 1.0f, -1.0f);
	vec3 horizontal = vec3(4.0f, 0.0f, 0.0f);
	vec3 vertical = vec3(0.0f, 2.0f, 0.0f);

	float m_fieldOfView; // in radians
	float m_aspectRatio;
	float m_aperture = 2.0f;
	float m_focusDistance = 2.0f;
	float m_lensRadius;

	// From legacy camera:
	float m_yawAngle;
	float m_pitchAngle;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	bool m_cameraSpeedUp = false;
	bool m_cameraSpeedDown = false;
	float m_cameraSpeed;
	float m_rotateSpeed;

protected:

	vec3 m_position = vec3(13.0f, 2.0f, 3.0f);

	bool m_needsUpdate = true;
};

}
