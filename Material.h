#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "CULL_MODE.h"
#include <vector>

class GraphicsEngine;

class Material
{
public:
	Material(const wchar_t* vs_path, const wchar_t* ps_path);
	Material(const MaterialPtr& material);

	void addTexture(const TexturePtr& texture);
	void removeTexture(unsigned int index);
	void clearTextures();
	void setData(void* data, unsigned int size);
	void setCullMode(CULL_MODE mode);

	CULL_MODE getCullMode();

	~Material();

private:
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	ConstantBufferPtr m_cb;
	std::vector<TexturePtr> m_textures;

	CULL_MODE m_cull_mode = CULL_MODE_BACK;

private:
	friend class GraphicsEngine;
};