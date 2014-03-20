#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
	: m_VertexFile(vertexFile)
	, m_FragmentFile(fragmentFile)
{
	init();
}

Shader::~Shader()
{
	glDeleteProgram(m_Program);
}

void Shader::setupVertexAttribPointer(const std::string& name, int size, GLenum type, int stride, const GLvoid* pointer)
{
	auto attribLocation = getAttribLocation(name);

	glVertexAttribPointer(attribLocation, size, type, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(attribLocation);
}

GLint Shader::getAttribLocation(const std::string& name)
{
	if (m_AttribLocations.find(name) == m_AttribLocations.end())
	{
		auto location = glGetAttribLocation(m_Program, name.c_str());
		m_AttribLocations[name] = location;
	}

	return m_AttribLocations[name];
}

void Shader::setUniform(const std::string& uniformName, int value)
{
	std::cout << "Setting uniform " << uniformName << " to " << value << std::endl;
	auto location = getUniformLocation(uniformName);
	glUniform1i(location, value);
}

void Shader::setUniform(const std::string& uniformName, float value)
{
	auto location = getUniformLocation(uniformName);
	glUniform1f(location, value);
}

void Shader::setUniform(const std::string& uniformName, const glm::mat4& matrix)
{
	auto location = getUniformLocation(uniformName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform(const std::string& uniformName, const glm::vec2& vector)
{
	auto location = getUniformLocation(uniformName);
	glUniform2fv(location, 1, glm::value_ptr(vector));
}

void Shader::setUniform(const std::string& uniformName, const glm::vec3& vector)
{
	auto location = getUniformLocation(uniformName);
	glUniform3fv(location, 1, glm::value_ptr(vector));
}

void Shader::setUniform(const std::string& uniformName, const glm::vec4& vector)
{
	auto location = getUniformLocation(uniformName);
	glUniform4fv(location, 1, glm::value_ptr(vector));
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
	if (m_UniformLocations.find(uniformName) == m_UniformLocations.end())
	{
		auto uniformLocation = glGetUniformLocation(m_Program, uniformName.c_str());
		m_UniformLocations[uniformName] = uniformLocation;
	}

	return m_UniformLocations[uniformName];
}

void Shader::init()
{
	auto vertexShaderSource = getShaderSource(m_VertexFile);
	auto fragmentShaderSource = getShaderSource(m_FragmentFile);

	auto vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	auto fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	createProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::createProgram(GLuint vertexShader, GLuint fragmentShader)
{
	m_Program = glCreateProgram();

	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fragmentShader);

	glLinkProgram(m_Program);
	checkLinkStatus();
}

void Shader::checkLinkStatus()
{
	GLint isLinked = 0;
	glGetProgramiv(m_Program, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_Program, maxLength, &maxLength, &errorLog[0]);

		std::cerr << "Error linking program\n"
					 "------------------------" << std::endl;
		for (auto& c : errorLog)
			std::cerr << c;
		std::cerr << "------------------------" << std::endl;

		glDeleteProgram(m_Program);
	}
}

GLuint Shader::createShader(GLenum shaderType, const std::string& source)
{
	GLuint shader = glCreateShader(shaderType);

	auto sourceAsCString = source.c_str();

	glShaderSource(shader, 1, &sourceAsCString, NULL);
	glCompileShader(shader);

	checkCompileStatus(shader);

	return shader;
}

void Shader::checkCompileStatus(GLuint shader)
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		std::cerr << "Error compiling shader\n"
					 "------------------------" << std::endl;
		for (auto& c : errorLog)
			std::cerr << c;
		std::cerr << "------------------------" << std::endl;

		glDeleteShader(shader);
	}
}

std::string Shader::getShaderSource(const std::string& fileName) const
{
	std::ifstream fileStream(fileName);

	std::string currentLine;
	std::string fileContents;

	if (fileStream.is_open())
	{
		while (std::getline(fileStream, currentLine))
		{
			fileContents += currentLine += "\n";
		}
	}
	else
	{
		std::cerr << "Unable to open shader source file: " << fileName << std::endl;
	}

	return fileContents;
}

void Shader::bind()
{
	glUseProgram(m_Program);
}