#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <GL/GL.h>

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <map>

class Shader
{
public:
	Shader(const std::string& vertexFile, const std::string& fragmentFile);
	~Shader();

	void bind();

	void setUniform(const std::string& uniformName, int value);
	void setUniform(const std::string& uniformName, float value);
	void setUniform(const std::string& uniformName, const glm::mat4& matrix, GLboolean transpose = GL_FALSE);
	void setUniform(const std::string& uniformName, const glm::vec2& vector);
	void setUniform(const std::string& uniformName, const glm::vec3& vector);
	void setUniform(const std::string& uniformName, const glm::vec4& vector);

	void setupVertexAttribPointer(const std::string& name, int size = 2, GLenum type = GL_FLOAT, int stride = 0, const GLvoid* pointer = 0);
	
private:
	void init();

	std::string getShaderSource(const std::string& fileName) const;
	
	GLuint createShader(GLenum shaderType, const std::string& source);
	void createProgram(GLuint vertexShader, GLuint fragmentShader);

	void checkCompileStatus(GLuint shader);
	void checkLinkStatus();

	GLint getUniformLocation(const std::string& uniformName);
	GLint getAttribLocation(const std::string& name);

private:
	std::string m_VertexFile;
	std::string m_FragmentFile;

	GLuint m_Program;

	std::map<std::string, GLint> m_UniformLocations;
	std::map<std::string, GLint> m_AttribLocations;
};

#endif