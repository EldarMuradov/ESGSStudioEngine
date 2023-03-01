#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include <exception>
#include "CMesh.h"

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) 
	{ 
		throw std::exception("Failed to create {RenderSystem}. Error in {GraphicsEngine::ctor}.");
	}

	try
	{
		m_tex_manager = new TextureManager();
	}
	catch (...)
	{ 
		throw std::exception("Failed to create {TextureManager}. Error in {GraphicsEngine::ctor}.");
	}
	
	try
	{
		m_mesh_manager = new MeshManager();
	}
	catch (...) 
	{ 
		throw std::exception("Failed to create {MeshManager}. Error in {GraphicsEngine::ctor}.");
	}


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	m_render_system->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	m_render_system->releaseCompiledShader();
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

MaterialPtr GraphicsEngine::createMaterial(const wchar_t* vs_path, const wchar_t* ps_path)
{
	MaterialPtr mat = nullptr;
	try
	{
		mat = std::make_shared<Material>(vs_path, ps_path);
		mat->setCullMode(CULL_MODE_BACK);
	}
	catch (...)
	{
		throw std::exception("Failed to create {Material}. Error in {GraphicsEngine::createMaterial(...)}.");
	}
	return mat;
}

MaterialPtr GraphicsEngine::createMaterial(const MaterialPtr& material)
{

	MaterialPtr mat = nullptr;
	try
	{
		mat = std::make_shared<Material>(material);
		mat->setCullMode(CULL_MODE_BACK);
	}
	catch (...)
	{
		throw std::exception("Failed to create {Material}. Error in {GraphicsEngine::createMaterial(...)}.");
	}
	return mat;
}

MaterialPtr GraphicsEngine::createMaterial()
{
	MaterialPtr mat = nullptr;
	try
	{
		MaterialPtr base = createMaterial(L"PointLightVertexShader.hlsl", L"PointLightPixelShader.hlsl");

		mat = std::make_shared<Material>(base);
		mat->setCullMode(CULL_MODE_BACK);
	}
	catch (...)
	{
		throw std::exception("Failed to create {Material}. Error in {GraphicsEngine::createMaterial(...)}.");
	}
	return mat;
}

MaterialPtr GraphicsEngine::createSkyMaterial(const wchar_t* vs_path, const wchar_t* ps_path)
{
	MaterialPtr mat = nullptr;
	try
	{
		mat = std::make_shared<Material>(vs_path, ps_path);
		mat->setCullMode(CULL_MODE_FRONT);
	}
	catch (...)
	{
		throw std::exception("Failed to create {Material}. Error in {GraphicsEngine::createMaterial(...)}.");
	}
	return mat;
}

void GraphicsEngine::setMaterial(const MaterialPtr& material)
{
	GraphicsEngine::get()->getRenderSystem()->setRasterizerState(material->m_cull_mode == CULL_MODE_FRONT);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(material->m_vs, material->m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(material->m_ps, material->m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(material->m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(material->m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(material->m_ps, &material->m_textures[0], material->m_textures.size());
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

void GraphicsEngine::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;
}

void GraphicsEngine::addComponent(Component* comp)
{
	if (auto c = dynamic_cast<CMesh*>(comp))
		m_meshes.emplace(c);
}

void GraphicsEngine::removeComponent(Component* comp)
{
	if (auto c = dynamic_cast<CMesh*>(comp))
		m_meshes.emplace(c);
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine) 
		throw std::exception("Failed to create {GraphicsEngine}. Error in {GraphicsEngine::create()}. {GraphicsEngine} is already created.");
	GraphicsEngine::m_engine = new GraphicsEngine();
}

void GraphicsEngine::release() 
{
	if (!GraphicsEngine::m_engine) 
		return;
	delete GraphicsEngine::m_engine;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_mesh_manager;
	delete m_tex_manager;
	delete m_render_system;
}