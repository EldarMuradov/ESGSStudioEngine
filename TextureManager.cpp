#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager(): ResourceManager()
{
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Texture>(createResourceFromFile(file_path));
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) 
	{
		throw std::exception("Failed to create {Texture}. Error in ctor.");
	}

	return tex;
}

TextureManager::~TextureManager()
{
}