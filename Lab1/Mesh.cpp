#include "Mesh.h"
#include <vector>


void Mesh::initModel(const IndexedModel& model)
{
	
	drawCount = model.indices.size();

	glGenVertexArrays(1, &vertexArrayObject);						// Generate a vertex array and store it in the VAO.
	glBindVertexArray(vertexArrayObject);							// Bind the VAO (any operation that works on a VAO will work on our bound VAO - binding).

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);					// Generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS].
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]);	// Tell opengl what type of data the buffer is, and pass the data.
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);	// Move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type).
	glEnableVertexAttribArray(0);									// Fill Attribute using vertex attribute array 0.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);			// Define an array of atribute data ( GLuint index,  GLint size,  GLenum type,  GLboolean normalized,  GLsizei stride,  const GLvoid * pointer). 

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);	// Tell opengl what type of data the buffer is, and pass the data.
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);	//Move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU.
	glEnableVertexAttribArray(1);									// Fill Attribute using vertex attribute array 1.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);			// Define an array of atribute data ( GLuint index,  GLint size,  GLenum type,  GLboolean normalized,  GLsizei stride,  const GLvoid * pointer).

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);	// Tell opengl what type of data the buffer is, and pass the data.
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);			//Move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU.
	glEnableVertexAttribArray(2);									// Fill Attribute using vertex attribute array 2.
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);			// Define an array of atribute data ( GLuint index,  GLint size,  GLenum type,  GLboolean normalized,  GLsizei stride,  const GLvoid * pointer).

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]); // Tell opengl what type of data the buffer is, and pass the data.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);	// Move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU.

	glBindVertexArray(0);											// Unbind our VAO.

	SpherePos();													// Get the position of the sphere.
	sphereRadius();													// Get the radius of the sphere.
}

void Mesh::UpdateSphere(glm::vec3 & pos, float radius)
{
	meshSphere.SetPos(pos);											// Update the position of the sphere.
	meshSphere.SetRadius(radius);									// Update the radius of the sphere.
}

Mesh::Mesh()
{
	drawCount = NULL;												// Set drawCount to null.
}

void Mesh::loadModel(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();		// Create an IndexModel model and set it to a stored model using filename.
	initModel(model);												// Call initModel passing in model.
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);					// Delete arrays.
}

void Mesh::draw()
{
	glBindVertexArray(vertexArrayObject);							// Bind the VAO.
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);	// Render primitives from the array data.
	glBindVertexArray(0);											// Unbind our VAO.
}

//Constructor//
Sphere::Sphere()
{
}
