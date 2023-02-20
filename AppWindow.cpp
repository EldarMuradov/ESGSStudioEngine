#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "Mesh.h"
#include "vertex.h"
#include "constant.h"
#include "PhysicsEngine.h"
#include <iostream>

AppWindow::AppWindow()
{
}

void AppWindow::render()
{
	//clear the render target
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//compute transform matrices
	update();

	m_mat_list.clear();
	m_mat_list.push_back(m_mat_0);

	updateModel(Vector3D(25, -5, 10), Vector3D(0.3f, 0.3f, 0.3f), Vector3D(22, 0, 0), m_mat_list);
	drawMesh(m_mesh, m_mat_list);

	//m_mat_list.clear();
	//m_mat_list.push_back(m_mat_1);

	//updateModel(Vector3D(0, -5, 50), Vector3D(10.0f, 10.0f, 10.0f), Vector3D(), m_mat_list);
	//drawMesh(m_mesh_1, m_mat_list);

	m_mat_list.clear();
	m_mat_list.push_back(m_mat_1);

	updateModel(Vector3D(25, -5, 10), Vector3D(0.3f, 0.3f, 0.3f), Vector3D(), m_mat_list);
	drawMesh(m_mesh_0, m_mat_list);

	m_mat_list.clear();
	m_mat_list.push_back(m_mat_barrel);
	m_mat_list.push_back(m_mat_brick);
	m_mat_list.push_back(m_mat_win);
	m_mat_list.push_back(m_mat_wood);
	//updateModel(Vector3D(0, 0, 0), Vector3D(1.0f, 1.0f, 1.0f), m_mat_list);
	//drawMesh(m_mesh_h, m_mat_list);

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int k = 0; k < 3; k++)
		{
			updateModel(Vector3D(-14.0f + 14.0f * i, -5, -14.0f + 14.0f * k), Vector3D(1.0f, 1.0f, 1.0f), Vector3D(0, 0 + 30 * 2 * k, 0), m_mat_list);
			drawMesh(m_mesh_h, m_mat_list);
		}
	}

	m_mat_list.clear();
	m_mat_list.push_back(m_mat_terr);
	updateModel(Vector3D(0, -5, 0), Vector3D(1, 1, 1), Vector3D(), m_mat_list);
	drawMesh(m_mesh_terr, m_mat_list);

	m_mat_list.clear();
	m_mat_list.push_back(m_sky_mat);
	drawMesh(m_sky_mesh, m_mat_list);

	m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;

	std::cout << "FPS: " << (unsigned int)(1.0f / m_delta_time) << std::endl;

	m_time += m_delta_time;
}

void AppWindow::update()
{
	updateCamera();
	updateSkyBox();
	updateLight();
	updatePhisycs();
}

void AppWindow::updateModel(Vector3D pos, Vector3D scale, Vector3D rot, const std::vector<MaterialPtr>& mat_list)
{
	constant cc;

	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.setIdentity();
	m_light_rot_matrix.setRotationY(m_light_rot_y);

	cc.m_world.setIdentity();
	cc.m_world.setTranslation(pos);
	cc.m_world.setRotation(rot);
	cc.m_view = m_view_cam;
	cc.m_proj = m_proj_cam;
	cc.m_camera_position = m_world_cam.getTranslation();
	cc.m_world.setScale(scale);

	cc.m_light_position = m_light_position;

	cc.m_light_radius = m_light_radius;
	cc.m_light_direction = m_light_rot_matrix.getZDirection();
	cc.m_time = m_time;

	for(size_t mat = 0; mat < mat_list.size(); mat++)
		mat_list[mat]->setData(&cc, sizeof(constant));
}

void AppWindow::updateCamera()
{
	Matrix4x4 world_cam, temp;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.05f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.05f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.inverse();

	m_view_cam = world_cam;

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_proj_cam.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
}

void AppWindow::updateSkyBox()
{
	constant cc;

	cc.m_world.setIdentity();
	cc.m_world.setScale(Vector3D(100.0f, 100.0f, 100.0f));
	cc.m_world.setTranslation(m_world_cam.getTranslation());
	cc.m_view = m_view_cam;
	cc.m_proj = m_proj_cam;

	m_sky_mat->setData(&cc, sizeof(constant));
}

void AppWindow::updateLight()
{
	//m_light_rot_y += 1.57f * m_delta_time;

	float dist_from_origin = 3.0f;

	m_light_position = Vector4D(0, 50, 0, 1.0f);
}

void AppWindow::updatePhisycs()
{
	PhysicsEngine::m_scene->simulate(1.0f/60.0f);
	PhysicsEngine::m_scene->fetchResults(true);
}

void AppWindow::drawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& mat_list)
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(mesh->getVertexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(mesh->getIndexBuffer());

	for (size_t mat = 0; mesh->getNumMatSlots(); mat++)
	{
		if (mat >= mat_list.size())
			break;

		MaterialSlot slot = mesh->getMaterialSlots(mat);
		GraphicsEngine::get()->setMaterial(mat_list[mat]);

		// draw the triangle
		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(slot.num_indices, 0, slot.start_index);
	}
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);

	m_play_state = true;
	InputSystem::get()->showCursor(false);

	m_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wall.jpg");
	m_tex_0 = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\beton.jpg");
	m_tex_1 = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\woodfloor.jpeg");

	m_tex_terr = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\sand.jpg");

	m_sky_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\pinksky.png");

	m_tex_barrel = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\barrel.jpg");
	m_tex_brick = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\house_brick.jpg");
	m_tex_wood = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\house_wood.jpg");
	m_tex_win = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\house_windows.jpg");
	
	m_mesh_h = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\house.obj");
	m_mesh_terr = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\terrain.obj");
	m_sky_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\sphere.obj");

	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\bulld.obj");
	m_mesh_0 = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\heap.obj");
	m_mesh_1 = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\room.obj");

	RECT rc = this->getClientWindowRect();
	m_swap_chain=GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0, 0, -1));

	m_mat = GraphicsEngine::get()->createMaterial(L"PointLightVertexShader.hlsl", L"PointLightPixelShader.hlsl");
	m_mat->addTexture(m_tex);
	m_mat->setCullMode(CULL_MODE_BACK);

	m_mat_0 = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_0->addTexture(m_tex_0);
	m_mat_0->setCullMode(CULL_MODE_BACK);

	m_mat_1 = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_1->addTexture(m_tex_1);
	m_mat_1->setCullMode(CULL_MODE_BACK);

	m_mat_terr = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_terr->addTexture(m_tex_terr);
	m_mat_terr->setCullMode(CULL_MODE_BACK);

	m_mat_barrel = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_barrel->addTexture(m_tex_barrel);
	m_mat_barrel->setCullMode(CULL_MODE_BACK);

	m_mat_brick = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_brick->addTexture(m_tex_brick);
	m_mat_brick->setCullMode(CULL_MODE_BACK);

	m_mat_win = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_win->addTexture(m_tex_win);
	m_mat_win->setCullMode(CULL_MODE_BACK);

	m_mat_wood = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_wood->addTexture(m_tex_wood);
	m_mat_wood->setCullMode(CULL_MODE_BACK);

	m_sky_mat = GraphicsEngine::get()->createMaterial(L"SkyBoxVertexShader.hlsl", L"SkyBoxShader.hlsl");
	m_sky_mat->addTexture(m_sky_tex);
	m_sky_mat->setCullMode(CULL_MODE_FRONT);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	m_mat_list.resize(128);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();
	this->render();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->setFullScreen(false, 1, 1);
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onSize()
{
	RECT rc = this->getClientWindowRect();
	m_swap_chain->resize(rc.right, rc.bottom);
	this->render();
}

void AppWindow::onKeyDown(int key)
{
	if (!m_play_state) return;

	if (key == 'W')
	{
		m_forward = 1.0f;
		std::cout << "Debug: Moving forward" << std::endl;
	}
	else if (key == 'S')
	{
		m_forward = -1.0f;
		std::cout << "Debug: Moving backward" << std::endl;
	}
	else if (key == 'A')
	{
		m_rightward = -1.0f;
		std::cout << "Debug: Moving leftward" << std::endl;
	}
	else if (key == 'D')
	{
		m_rightward = 1.0f;
		std::cout << "Debug: Moving rightward" << std::endl;
	}
	else if (key == 'O')
	{
		m_light_radius = (m_light_radius <= 0) ? 0.0f : m_light_radius - 1.0f * m_delta_time;
	}
	else if (key == 'P')
	{
		m_light_radius += 1.0f * m_delta_time;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;

	if (key == 'G')
	{
		m_play_state = !m_play_state;
		InputSystem::get()->showCursor(!m_play_state);
	}
	else if (key == 'F')
	{
		m_fullscreen_state = !m_fullscreen_state;
		RECT size_screen = this->getSizeScreen();
	
		m_swap_chain->setFullScreen(m_fullscreen_state, size_screen.right, size_screen.bottom);
	}
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	if (!m_play_state) 
		return;

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f;

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{

}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{

}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{

}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{

}

AppWindow::~AppWindow()
{
}