#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "GL/glew.h"
#include "maths/vec/vec2.h"
#include "maths/vec/vec3.h"
#include "maths/vec/vec4.h"
#include "maths/mat/mat4.h"

class Shader
{
private:
	unsigned int p_shaderID;
	std::string p_vsCode, p_fsCode;
	std::string p_vsCodePath, p_fsCodePath;

public:
	Shader(const std::string& vsPath, const std::string& fsPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	std::string loadShader(const std::string& shaderPath);
	unsigned int compileShader(unsigned int shaderType, const std::string& shaderCode);

	// Set the uniform values
	void setUniformVec2f(const char* uniName, const vec2& vec);
	void setUniformVec3f(const char* uniName, const vec3& vec);
	void setUniformVec4f(const char* uniName, const vec4& vec);
	void setUniformMat4f(const char* uniName, const mat4& mat);

	void setUniform1i(const char* uniname, const int& data);
	void setUniform1iv(const char* uniname, const int* const data);
	void setUniform1f(const char* uniname, const float& data);
	void setUniform1fv(const char* uniname, const float* const data);

};