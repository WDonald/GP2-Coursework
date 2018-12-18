#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "GameCamera.h"
#include <iostream>

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;								// Set this -> pos to the value that was pased in through pos.
		this->rot = rot;								// Set this -> rot to the value that was pased in through rot.
		this->scale = scale;							// Set this -> scale to the value that was pased in through scale.

	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(pos);			// Crete a position matrix using translate(pos).
		glm::mat4 scaleMat = glm::scale(scale);			// Create a scaler matrix using scale(scale).
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));		// create a rotation matrix for the X-axis usin a vector (1, 0, 0).
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));		// create a rotation matrix for the Y-axis usin a vector (0, 1, 0).
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));		// create a rotation matrix for the Z-axis usin a vector (0, 0, 1).
		glm::mat4 rotMat = rotX * rotY * rotZ;			// Create a rotation matrix for the X, Y and Z axes by multiplying rotX, rotY and rotZ together.

		return posMat * rotMat * scaleMat;				// Return a movement matrix that will move, rotate and scale the object by multiplying posMat, rotMat and scaleMat together.
	}


	inline glm::vec3* GetPos() { return &pos; }			// Getter for position.
	inline glm::vec3* GetRot() { return &rot; }			// Getter for rotation.
	inline glm::vec3* GetScale() { return &scale; }		// Getter for scale.

	inline void SetPos(glm::vec3& pos) { this->pos = pos; }				// Setter for position.
	inline void SetRot(glm::vec3& rot) { this->rot = rot; }				// Setter for rotation.
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }		// Setter for scale.


	void transformObj(float inputPos, int direction);	// Move the object in the desierd direction when called.
	void resetObjRot(float inputPos);					// Reset the rotation of the object when called.
	void setTransform();								// Set the position of the ship when called.

protected:
private:
	glm::vec3 pos;										// Holds the value for position.
	glm::vec3 rot;										// Holds the value for rotation.
	glm::vec3 scale;									// Holds the value for scale.
	
	int currentDirection;								// Holds the value used to determine direction the is ship moving.
	
	float counter;										// Holds the value used to tilt the ship. 
	float decreaseCounter;								// Holds a value used to move the ship.

	bool canGoBack;										// Used to determine if the ship scould move in the opposite direction When at the boundary.
};


