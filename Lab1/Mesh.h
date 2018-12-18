#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "transform.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)		// Constructor passing in vec3 pos and vec2 texCoords. 
	{
		this->pos = pos;								// Set this -> pos to the value that was pased in through pos. 
		this->texCoord = texCoord;						// Set this -> texCoord to the value that was pased in through texCoord. 
		this->normal = normal;							// Set this -> normal to the value of normal. 
	}

	glm::vec3* GetPos() { return &pos; }				// Getter for pos.
	glm::vec2* GetTexCoord() { return &texCoord; }		// Getter for texCoord.
	glm::vec3* GetNormal() { return &normal; }			// Getter for normal.

private:
	glm::vec3 pos;										// Variable to hold the position.
	glm::vec2 texCoord;									// Variable to hold the texture coordinates.
	glm::vec3 normal;									// Variable to hold the normals.
};

struct Sphere
{
	Sphere();											// Constructor.
public:
	Sphere(glm::vec3& pos, float& radius)				// Constructor passing in vec3 pos and float radius.
	{
		this->pos = pos;								// Set this -> pos to the value that was pased in through pos. 
		this->radius = radius;							// Set this -> radius to the value that was pased in through radius. 
	}


	inline glm::vec3* GetPos() { return &pos; }			// Getter for pos.
	inline float* GetRadius() { return &radius; }		// Getter for radius.

	inline void SetPos(glm::vec3& pos) { this->pos = pos; }				// Setter for pos.
	inline void SetRadius(float& radius) { this->radius = radius; }		// Setter for radius.

private:

	glm::vec3 pos;										// Variable to hold the position.
	float radius;										// Variable to hold the radius.

};

class Mesh
{
public:
	Mesh();												// Constructor.
	~Mesh();											// Destructor.

	void draw();										// Draw mesh when called.
	
	void loadModel(const std::string& filename);		// Load the model from file when called.
	void initModel(const IndexedModel& model);			// Initialise the model when called.


	glm::vec3* SpherePos(){return this -> meshSphere.GetPos();}				// Get the value of the position of the sphere.
	float* sphereRadius() { return  this -> meshSphere.GetRadius(); }		// Get the value of the radius of the sphere.

	void UpdateSphere(glm::vec3& pos, float radius);	// Updaes the position and the radius of the sphere when called.

private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;							// Store the object we want to draw.
	GLuint vertexArrayBuffers[NUM_BUFFERS];				// Create our array of buffers.
	unsigned int drawCount;								// How much of the vertexArrayObject do we want to draw.
	
	Sphere meshSphere;									// The sphere used to calculate collisions.
	Transform transform;								// The transform for the ship.
};

