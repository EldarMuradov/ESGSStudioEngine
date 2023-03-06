#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "Material.h"
#include <set>

class GraphicsEngine
{
private:
	GraphicsEngine();
	~GraphicsEngine();

public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();

	MaterialPtr createMaterial(const wchar_t* vs_path, const wchar_t* ps_path);
	MaterialPtr createMaterial(const MaterialPtr& material);
	MaterialPtr createMaterial();
	MaterialPtr createSkyMaterial(const wchar_t* vs_path, const wchar_t* ps_path);

	void setMaterial(const MaterialPtr& material);
	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

	void addComponent(Component* comp);
	void removeComponent(Component* comp);

public:
	static GraphicsEngine* get();
	static void create();
	static void release();
private:
	RenderSystem* m_render_system = nullptr;
	TextureManager* m_tex_manager = nullptr;
	MeshManager* m_mesh_manager = nullptr;

	static GraphicsEngine* m_engine;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;

	std::set<CMesh*> m_meshes;
	std::set<CCamera*> m_cameras;

	friend class AppWindow;
};