#include "../include/shader_program.h"

ShaderProgram::ShaderProgram(const char* filepath)
{
	m_id = glCreateProgram();

	std::ifstream stream(filepath);

	if (stream)
	{
		std::string line;
		std::stringstream ss[SHADER_TYPES_COUNT];
		ShaderType sourceType = ShaderType::NONE;

		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					sourceType = ShaderType::VERTEX;
				else if (line.find("geometry") != std::string::npos)
					sourceType = ShaderType::GEOMETRY;
				else if (line.find("fragment") != std::string::npos)
					sourceType = ShaderType::FRAGMENT;
			}
			else if (sourceType != ShaderType::NONE)
				ss[sourceType] << line << std::endl;
		}

		Shader* shaders[SHADER_TYPES_COUNT];
		for (int s = 0; s < SHADER_TYPES_COUNT; s++)
		{
			shaders[s] = nullptr;

			const std::string source = ss[s].str();
			if (source != "")
			{
				shaders[s] = new Shader((ShaderType)s, source.c_str());
				attachShader(shaders[s]);
			}
		}

		link();

		for (int s = 0; s < SHADER_TYPES_COUNT; s++)
			if (shaders[s] != nullptr)
				delete shaders[s];
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_id);
}

void ShaderProgram::link() const
{
	glLinkProgram(m_id);

	if (!linked())
	{
		GLint maxLength = 0;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_id, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(m_id); 
	}
}

GLuint ShaderProgram::getID() const
{
	return m_id;
}

GLuint ShaderProgram::getUniformLoc(const char* uniformName) const
{
	GLint loc = glGetUniformLocation(m_id, uniformName);

	if (loc == -1)
		return loc;

	return loc;
}

void ShaderProgram::setUniform_1i(const char* uniformName, const GLint i) const
{
	glUniform1i(getUniformLoc(uniformName), i);
}

void ShaderProgram::setUniform_1f(const char* uniformName, const GLfloat f) const
{
	glUniform1f(getUniformLoc(uniformName), f);
}

void ShaderProgram::setUniform_2f(const char* uniformName, const GLfloat f[2]) const
{
	glUniform2f(getUniformLoc(uniformName), f[0], f[1]);
}

void ShaderProgram::setUniform_3f(const char* uniformName, const GLfloat f[3]) const
{
	glUniform3f(getUniformLoc(uniformName), f[0], f[1], f[2]);
}

void ShaderProgram::setUniform_4f(const char* uniformName, const GLfloat f[4]) const
{
	glUniform4f(getUniformLoc(uniformName), f[0], f[1], f[2], f[3]);
}

void ShaderProgram::setUniform_mat4(const char* uniformName, const GLfloat f[16]) const
{
	glUniformMatrix4fv(getUniformLoc(uniformName), 1, GL_FALSE, f);
}

void ShaderProgram::enable() const
{
	if (m_id)
		glUseProgram(m_id);
}

bool ShaderProgram::linked() const
{
	GLint isLinked = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);
	return isLinked != GL_FALSE;
}

void ShaderProgram::attachShader(const Shader* shader) const
{
	glAttachShader(m_id, shader->id());
}