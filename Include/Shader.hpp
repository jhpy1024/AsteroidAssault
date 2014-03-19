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
	~Shader();

	static Shader& getInstance();

	void bind();

	void setUniform(const std::string& uniformName, float value);
	void setUniform(const std::string& uniformName, const glm::mat4& matrix);
	void setUniform(const std::string& uniformName, const glm::vec2& vector);
	void setUniform(const std::string& uniformName, const glm::vec3& vector);
	void setUniform(const std::string& uniformName, const glm::vec4& vector);
	
protected:
	Shader(const std::string& vertexFile, const std::string& fragmentFile);

	void init();

private:
	std::string getShaderSource(const std::string& fileName) const;
	
	GLuint createShader(GLenum shaderType, const std::string& source);
	void createProgram(GLuint vertexShader, GLuint fragmentShader);

	void checkCompileStatus(GLuint shader);
	void checkLinkStatus();

	GLint getUniformLocation(const std::string& uniformName);

private:
	static std::unique_ptr<Shader> m_Instance;

	std::string m_VertexFile;
	std::string m_FragmentFile;

	GLuint m_Program;

	std::map<std::string, GLint> m_UniformLocations;
};

#endif