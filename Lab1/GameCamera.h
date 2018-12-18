#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct GameCamera
{
public:
	GameCamera()				// Constructor.
	{
	}

	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip) // Initilisation of the camera.
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

protected:
private:
	glm::mat4 projection;		// Projection matrice for the camera.
	glm::vec3 pos;				// Position of the camera.
	glm::vec3 forward;			// Forword direction (where is the camera looking). 
	glm::vec3 up;				// Up direction (where is up in relation to the camera). 
};


