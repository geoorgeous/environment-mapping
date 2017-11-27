#include "../include/shader.h"

Shader::Shader(ShaderType type, const char* source)
{
	m_type = type;

	switch (m_type)
	{
	case ShaderType::NONE:
	case ShaderType::VERTEX:
		m_id = glCreateShader(GL_VERTEX_SHADER);  
		break;

	case ShaderType::GEOMETRY:
		m_id = glCreateShader(GL_GEOMETRY_SHADER);
		break;

	case ShaderType::FRAGMENT:
		m_id = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	m_source = source;

	glShaderSource(m_id, 1, &source, NULL);
	glCompileShader(m_id);

	if (!compiled())
	{
		GLint maxLength = 0;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(m_id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(m_id);
	}
}

Shader::~Shader()
{
	glDeleteShader(m_id);
}

ShaderType Shader::type() const
{
	return m_type;
}

const std::string& Shader::source() const
{
	return m_source;
}

GLuint Shader::id() const
{
	return m_id;
}

bool Shader::compiled() const
{
	GLint isCompiled = 0;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);
	return isCompiled != GL_FALSE;
}