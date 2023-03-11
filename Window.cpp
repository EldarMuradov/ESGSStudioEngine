#include "Window.h"
#include <exception>
#include "imgui_impl_dx11.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "GraphicsEngine.h"
#include <tchar.h>
#include "SwapChain.h"

bool Window::m_play = false;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg)
	{
		case WM_CREATE:
			break;
		case WM_SIZE:
		{
			// Event fired when the window is resized
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window) 
				window->onSize();
			break;
		}
		case WM_SETFOCUS:
		{
			// Event fired when the window get focus
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window)
				window->onFocus();
			break;
		}
		case WM_KILLFOCUS:
		{
			// Event fired when the window lost focus
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onKillFocus();
			break;
		}
		case WM_DESTROY:
		{
			// Event fired when the window is destroyed
			Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			::PostQuitMessage(0);
			break;
		}
		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return NULL;
}

Window::Window()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "ESGSStudioEngine";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		throw std::exception("Failed to create {Window}. Error in ctor / {::RegisterClassEx == false}.");

	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "ESGSStudioEngine", "ESGS Studio Engine",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		throw std::exception("Failed to create {Window}. Error in ctor / Failed to create {m_hwnd = ::CreateWindowEx(...)}.");

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable some options

	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->getDevice(), GraphicsEngine::get()->getRenderSystem()->getDeviceContext());
	ImGui::StyleColorsDark();

	m_is_run = true;
}

bool Window::broadcast()
{
	MSG msg;

	if (!this->m_is_init)
	{
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		this->onCreate();
		this->m_is_init = true;
	}

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	GraphicsEngine::get()->getRenderSystem()->getDeviceContext()->OMSetRenderTargets(1,
		GraphicsEngine::get()->getRenderSystem()->getSwapChain().get()->getRenderTargetViewC(),
		GraphicsEngine::get()->getRenderSystem()->getSwapChain().get()->getDepthStencilView());
	GraphicsEngine::get()->getRenderSystem()->getDeviceContext()->ClearRenderTargetView(
		GraphicsEngine::get()->getRenderSystem()->getSwapChain().get()->getRenderTargetView(), clear_color_with_alpha);

	this->onUpdate();

	m_gui.update();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	GraphicsEngine::get()->getRenderSystem()->getSwapChain().get()->present(true);

	//Sleep(1);

	return true;
}

bool Window::isRun()
{
	if (m_is_run)
		broadcast();
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

RECT Window::getSizeScreen()
{
	RECT rc;

	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = ::GetSystemMetrics(SM_CYSCREEN);

	return rc;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	m_is_run = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

void Window::onSize()
{
}

Window::~Window()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}