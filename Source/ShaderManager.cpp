#include "ShaderManager.hpp"

std::unique_ptr<ShaderManager> ShaderManager::m_Instance;


// TODO
// =================================
// Make this constructor "= default"
// =================================
ShaderManager::ShaderManager()
{

}

void ShaderManager::enableScreenShake(float amount)
{
	for (auto shader : m_Shaders)
	{
		shader.second->bind();
		shader.second->setUniform("in_CameraShakeEnabled", 1);
		shader.second->setUniform("in_CameraShakeAmount", amount);
	}
}

void ShaderManager::disableScrenShake()
{
	for (auto shader : m_Shaders)
	{
		shader.second->bind();
		shader.second->setUniform("in_CameraShakeEnabled", 0);
	}
}

void ShaderManager::addShader(const std::string& id, const std::string& vertexFile, const std::string& fragmentFile)
{
	m_Shaders[id] = std::make_shared<Shader>(vertexFile, fragmentFile);
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& id)
{
	assert(m_Shaders.find(id) != m_Shaders.end());

	return m_Shaders[id];
}

ShaderManager& ShaderManager::getInstance()
{
	if (m_Instance == nullptr)
		m_Instance = std::unique_ptr<ShaderManager>(new ShaderManager);

	return *m_Instance;
}