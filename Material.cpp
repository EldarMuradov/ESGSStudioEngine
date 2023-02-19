#include "Material.h"
#include "GraphicsEngine.h"
#include <exception>

Material::Material(const wchar_t* vs_path, const wchar_t* ps_path)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(vs_path, "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	if (!m_vs)
		throw std::exception("Failed to create Material vertex shader. Error in ctor.");

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(ps_path, "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	if (!m_ps)
		throw std::exception("Failed to create Material pixel shader. Error in ctor.");
}

Material::Material(const MaterialPtr& material)
{
	m_vs = material->m_vs;
	m_ps = material->m_ps;
}

void Material::addTexture(const TexturePtr& texture)
{
	m_textures.push_back(texture);
}

void Material::removeTexture(unsigned int index)
{
	if (index >= this->m_textures.size())
		return;
	m_textures.erase(m_textures.begin() + index);
}

void Material::clearTextures()
{
	m_textures.clear();
}

void Material::setData(void* data, unsigned int size)
{
	if (!m_cb)
		m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(data, size);
	else
		m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), data);
}

void Material::setCullMode(CULL_MODE mode)
{
	m_cull_mode = mode;
}

CULL_MODE Material::getCullMode()
{
	return m_cull_mode;
}

Material::~Material()
{
}
