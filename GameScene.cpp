#include "GameScene.h"
#include "Entity.h"
#include "AppWindow.h"
#include "Prerequisites.h"
#include "World.h"
#include "Quaternion.h"
#include "ESGSStudioEngine.h"
#include "PlayerController.h"
#include "InspectorTool.h"

GameScene::GameScene()
{
	
}

GameScene::~GameScene()
{
}

void GameScene::awake()
{

}

int i = 0;
Entity* entity_box = nullptr;

void GameScene::start()
{
	auto player = m_level->getWorld()->createEntity<PlayerController>();
	player->setTag("Player");
	player->setName("Player Controller");

	m_level->getWorld()->setSkyTexture(L"Assets\\Textures\\pinksky.png");

	//light
	auto light_entity = m_level->getWorld()->createEntity<Entity>();
	light_entity->setName("Directional Light");
	auto light = light_entity->createComponent<CLight>();
	light->setColor(Vector4D(0.50f, 0.50f, 0.50f, 1));
	light->setLightType(LightType::Directional);

	//building 1
	auto mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\bulld.obj");
	auto tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\beton.jpg");
	auto material = GraphicsEngine::get()->createMaterial();
	material->addTexture(tex);

	m_entity = m_level->getWorld()->createEntity<Entity>();
	m_entity->setName("Building");

	auto cmesh_home = m_entity->createComponent<CMesh>();
	cmesh_home->setMesh(mesh);
	cmesh_home->addMaterial(material);

	m_entity->getTransform()->setPosition(Vector3D(-30, -6, -15));

	m_entity->getTransform()->setScale(Vector3D(0.3f, 0.3f, 0.3f));

	//building 2
	auto entity_home2 = m_level->getWorld()->createEntity<Entity>();
	auto cmesh_home2 = entity_home2->createComponent<CMesh>();
	cmesh_home2->setMesh(mesh);
	cmesh_home2->addMaterial(material);

	entity_home2->getTransform()->setPosition(Vector3D(25, -6, 10));
	entity_home2->getTransform()->setRotation(Quaternion::euler(1, 1, 0));
	entity_home2->getTransform()->setScale(Vector3D(0.3f, 0.3f, 0.3f));
	entity_home2->setName("Building (2)");

	//box
	auto mesh_box = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\room.obj");
	auto tex_box = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\woodfloor.jpeg");
	auto material_box = GraphicsEngine::get()->createMaterial();
	material_box->addTexture(tex_box);

	entity_box = m_level->getWorld()->createEntity<Entity>();

	entity_box->setName("Box");
	auto cmesh_box = entity_box->createComponent<CMesh>();
	cmesh_box->setMesh(mesh_box);
	cmesh_box->addMaterial(material_box);

	entity_box->getTransform()->setPosition(Vector3D(0, 30, 50));
	entity_box->getTransform()->setScale(Vector3D(10.0f, 10.0f, 10.0f));

	//heap
	auto mesh_heap = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\heap.obj");
	auto tex_heap = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\woodfloor.jpeg");
	auto material_heap = GraphicsEngine::get()->createMaterial();
	material_heap->addTexture(tex_heap);

	auto entity_heap = m_level->getWorld()->createEntity<Entity>();
	entity_heap->setName("Heap");
	auto cmesh_heap = entity_heap->createComponent<CMesh>();
	cmesh_heap->setMesh(mesh_heap);
	cmesh_heap->addMaterial(material_heap);

	entity_heap->getTransform()->setPosition(Vector3D(25, -5, 10));
	entity_heap->getTransform()->setRotation(Quaternion::euler(0, 0, 0));
	entity_heap->getTransform()->setScale(Vector3D(0.3f, 0.3f, 0.3f));

	//terrain
	auto mesh_terr = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\terrain.obj");
	auto tex_terr = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\tile.jpg");
	auto material_terr = GraphicsEngine::get()->createMaterial();
	material_terr->addTexture(tex_terr);

	auto entity_terr = m_level->getWorld()->createEntity<Entity>();
	entity_terr->setName("Terrain");
	auto cmesh_terr = entity_terr->createComponent<CMesh>();
	cmesh_terr->setMesh(mesh_terr);
	cmesh_terr->addMaterial(material_terr);

	entity_terr->getTransform()->setPosition(Vector3D(0,-5, 0));
	entity_terr->getTransform()->setRotation(Quaternion::euler(0, 0, 0));
	entity_terr->getTransform()->setScale(Vector3D(1, 1, 1));

	//house x5

	auto mesh_h = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\house.obj");
	auto tex_barrel = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\barrel.jpg");
	auto tex_brick = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\house_brick.jpg");
	auto tex_wood = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\house_wood.jpg");
	auto tex_win = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\house_windows.jpg");
	
	auto material_h1 = GraphicsEngine::get()->createMaterial();
	material_h1->addTexture(tex_barrel);

	auto material_h2 = GraphicsEngine::get()->createMaterial();
	material_h2->addTexture(tex_brick);

	auto material_h3 = GraphicsEngine::get()->createMaterial();
	material_h3->addTexture(tex_win);

	auto material_h4 = GraphicsEngine::get()->createMaterial();
	material_h4->addTexture(tex_wood);

	for (unsigned int in = 0; in < 3; in++)
	{
		for (unsigned int kn = 0; kn < 3; kn++)
		{
			auto entity_h = m_level->getWorld()->createEntity<Entity>();
			auto cmesh_h = entity_h->createComponent<CMesh>();
			cmesh_h->setMesh(mesh_h);
			cmesh_h->addMaterial(material_h1);
			cmesh_h->addMaterial(material_h2);
			cmesh_h->addMaterial(material_h3);
			cmesh_h->addMaterial(material_h4);

			entity_h->getTransform()->setPosition(Vector3D(-14.0f + 14.0f * in, -5, -14.0f + 14.0f * kn));
			entity_h->getTransform()->setRotation(Quaternion::euler(0, 30 * 2 , 0));
			entity_h->getTransform()->setScale(Vector3D(1, 1, 1));
		}
	}

	InspectorTool::setCurrentEntity(player);
	InspectorTool::setCurrentCam(player->getComponent<CCamera>());
}

void GameScene::update()
{
	i++;
	m_entity->getTransform()->setRotation(Quaternion::euler(1, i, 0));
	entity_box->getTransform()->setRotation(Quaternion::euler(i, i, i));
}