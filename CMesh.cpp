#include "CMesh.h"
#include <exception>
#include "Entity.h"
#include "World.h"
#include "GameScene.h"
#include "GraphicsEngine.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
    GraphicsEngine::get()->removeComponent(this);
}

const char* CMesh::toStr()
{
    return "MeshRenderer";
}

void CMesh::setMesh(const MeshPtr& mesh)
{
    m_mesh = mesh;
}

const MeshPtr& CMesh::getMesh()
{
    return m_mesh;
}

void CMesh::addMaterial(const MaterialPtr& mat)
{
    m_materials.push_back(mat);
}

void CMesh::setSingleMaterial(const MaterialPtr& mat)
{
    m_materials.clear();
    m_materials.push_back(mat);
}

void CMesh::removeMaterial(unsigned int index)
{
    if (index >= m_materials.size())
        throw std::exception("Failed to remove Material from CMesh component. Material index out of range!");
    m_materials.erase(m_materials.begin() + index);
}

const std::vector<MaterialPtr>& CMesh::getMaterials()
{
    return  m_materials;
}

void CMesh::onCreateInternal()
{
    GraphicsEngine::get()->addComponent(this);
}
