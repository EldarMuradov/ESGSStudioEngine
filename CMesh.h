#pragma once
#include "Component.h"
#include "Prerequisites.h"
#include <vector>

class CMesh : public Component
{
public:
	CMesh();
	virtual ~CMesh();

	void setMesh(const MeshPtr& mesh);
	const MeshPtr& getMesh();

	void addMaterial(const MaterialPtr& mat);
	void setSingleMaterial(const MaterialPtr& mat);
	void removeMaterial(unsigned int index);

	const std::vector<MaterialPtr>& getMaterials();

protected:
	virtual void onCreateInternal();

public:
	MeshPtr m_mesh;

	std::vector<MaterialPtr> m_materials;
};