#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include <memory>
#include <string>
#include <map>

#include "Shader.hpp"

class ShaderManager
{
public:
	static ShaderManager& getInstance();

	void addShader(const std::string& id, const std::string& vertexFile, const std::string& fragmentFile);
	std::shared_ptr<Shader> getShader(const std::string& id);

	void enableScreenShake(float amount = 3.f);
	void disableScrenShake();

private:
	ShaderManager();

	static std::unique_ptr<ShaderManager> m_Instance;

	std::map<std::string, std::shared_ptr<Shader>> m_Shaders;
};

#endif