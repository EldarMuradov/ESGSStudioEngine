#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "MaterialSlot.h"
#include <vector>

class Mesh: public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();

	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();

	const MaterialSlot& getMaterialSlots(unsigned int slot);
	size_t getNumMatSlots();

private:
	VertexBufferPtr m_vertex_buffer;
	IndexBufferPtr m_index_buffer;
	std::vector<MaterialSlot> m_mat_slots;

private:
	friend class DeviceContext;
};