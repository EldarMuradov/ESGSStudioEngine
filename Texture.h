#pragma once
#include "Resource.h"
#include <d3d11.h>

class Texture: public Resource
{
public:
	Texture(const wchar_t* full_path);
	~Texture();

	const wchar_t* getFilePath();

private:
	ID3D11Resource* m_texture = nullptr;

	const  wchar_t* m_path;

	ID3D11ShaderResourceView* m_shader_res_view = nullptr;

	ID3D11SamplerState* m_sampler_state = nullptr;

private:
	friend class DeviceContext;
};