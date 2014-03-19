#include "Shader.hpp"

#include <vector>
#include <iostream>
#include <fstream>

std::unique_ptr<Shader> Shader::m_Instance;

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
	: m_VertexFile(vertexFile)
	, m_FragmentFile(fragmentFile)
{
	
}

Shader::~Shader()
{
	glDeleteProgram(m_Program);
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

Shader& Shader::getInstance()
{
	if (m_Instance == nullptr)
		m_Instance = std::unique_ptr<Shader>(new Shader("", ""));

	return *m_Instance;
}