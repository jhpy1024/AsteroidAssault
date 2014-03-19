#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <GL/GL.h>

#include <memory>
#include <string>

class Shader
{
public:
	~Shader();

	static Shader& getInstance();

	void bind();
	
protected:
	Shader(const std::string& vertexFile, const std::string& fragmentFile);

	void init();

private:
	std::string getShaderSource(const std::string& fileName) const;
	
	GLuint createShader(GLenum shaderType, const std::string& source);
	void createProgram(GLuint vertexShader, GLuint fragmentShader);

	void checkCompileStatus(GLuint shader);
	void checkLinkStatus();

private:
	static std::unique_ptr<Shader> m_Instance;

	std::string m_VertexFile;
	std::string m_FragmentFile;

	GLuint m_Program;
};

#endif