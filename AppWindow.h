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
#include "GameScene.h"
#include <chrono>
#include "Quaternion.h"
#include "Vector2D.h"

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
	void updateEntityModel(CTransform* transform, const std::vector<MaterialPtr>& mat_list);
	void updateModel(Vector3D pos, Vector3D scale, Quaternion rot, const std::vector<MaterialPtr>& mat_list);
	void updateCamera(CCamera* cam, const RECT& rc);
	void updateSkyBox();
	void updateLight(CLight* light);
	void updatePhisycs();
	void renderObj(Entity* entity);
	void renderObj(const MeshPtr& mesh, Vector3D pos, Vector3D scale, Quaternion rot, const std::vector<MaterialPtr>& mat_list);

	World* getWorld();

	void drawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& mat_list);

	static Vector2D getRect();
	static float getDeltaTime();

	static bool getPlayState();

	static void setPlayState(bool state);

public:
	const MaterialPtr& getSkyMaterial();

private:
	SwapChainPtr m_swap_chain;

	PixelShaderPtr m_sky_ps;

	ConstantBufferPtr m_sky_cb;

	MeshPtr m_sky_mesh;

	MaterialPtr m_sky_mat;

private:
	static float m_delta_time;

	float m_light_rot_y = 0.0f;

	bool cull = true;

	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;

	GameScene* m_scene = nullptr;

	Vector3D m_cam_rot;

	static Vector2D m_rect;

	Vector4D m_light_position;

	float m_time = 0.0f;
	float m_light_radius = 4.0f;
	float m_attenuation = 2.0f;

	std::chrono::system_clock::time_point m_prev_time;

	std::vector<MaterialPtr> m_mat_list;

	std::unique_ptr<World> m_world;

	friend class GameScene;
};