#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"
#include "World.h"
#include <chrono>

class AppWindow: public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	//Inherited by Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;	
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	virtual void onSize() override;

	//Inherited by InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
public:
	void render();
	void update();
	void updateModel(Vector3D pos, Vector3D scale, Vector3D rot, const std::vector<MaterialPtr>& mat_list);
	void updateModel(Vector3D pos, Vector3D scale, Quaternion rot, const std::vector<MaterialPtr>& mat_list);
	void updateCamera();
	void updateSkyBox();
	void updateLight();
	void updatePhisycs();

	World* getWorld();

	void drawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& mat_list);

private:
	SwapChainPtr m_swap_chain;

	VertexShaderPtr m_vs;

	PixelShaderPtr m_ps;
	PixelShaderPtr m_sky_ps;

	ConstantBufferPtr m_cb;
	ConstantBufferPtr m_sky_cb;

	TexturePtr m_tex_terr;
	TexturePtr m_tex_barrel;
	TexturePtr m_tex_brick;
	TexturePtr m_tex_win;
	TexturePtr m_tex_wood;
	TexturePtr m_tex;
	TexturePtr m_tex_0;
	TexturePtr m_tex_1;
	TexturePtr m_sky_tex;

	MaterialPtr m_mat_barrel;
	MaterialPtr m_mat_brick;
	MaterialPtr m_mat_win;
	MaterialPtr m_mat_wood;
	MaterialPtr m_mat_0;
	MaterialPtr m_mat_1;
	MaterialPtr m_mat;
	MaterialPtr m_mat_terr;
	MaterialPtr m_sky_mat;

	MeshPtr m_mesh_h;
	MeshPtr m_mesh;
	MeshPtr m_mesh_0;
	MeshPtr m_mesh_1;
	MeshPtr m_sky_mesh;
	MeshPtr m_mesh_terr;

private:
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_light_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Entity* m_entity = nullptr;

	bool cull = true;

	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;

	Vector3D m_cam_rot;

	Vector4D m_light_position;

	float m_time = 0.0f;
	float m_light_radius = 4.0f;
	float m_attenuation = 2.0f;

	std::chrono::system_clock::time_point m_prev_time;

	bool m_play_state = false;
	bool m_fullscreen_state = false;

	std::vector<MaterialPtr> m_mat_list;

	std::unique_ptr<World> m_world;
};