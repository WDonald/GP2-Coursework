#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "GameCamera.h"

class Shader
{
public:
	Shader();

	void Bind();										// Set gpu to use our shaders.
	void Update(const Transform& transform, const GameCamera& camera);
	void init(const std::string& filename);

	std::string Shader::LoadShader(const std::string& fileName);
	void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint Shader::CreateShader(const std::string& text, unsigned int type);

    ~Shader();


protected:
private:
	static const unsigned int NUM_SHADERS = 2;			// Number of shaders.

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program;										// Track the shader program.
	GLuint shaders[NUM_SHADERS];						// Array of shaders.
	GLuint uniforms[NUM_UNIFORMS];						// Number of uniform variables.
};
