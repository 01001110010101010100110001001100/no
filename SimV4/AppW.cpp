#include "AppW.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"

struct vertex {
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant {
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time; 
};


AppW::AppW() {
}

void AppW::udateQuadPosition() {
	constant cc;
	cc.m_time = ::GetTickCount();
	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;
	Matrix4x4 temp;
	m_delta_scale += m_delta_time / 0.15f;
	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));
	cc.m_world *= temp;
	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/400.0f,
		-4.0f,
		4.0f);
	m_cb->update(GraphicsEn::get()->getImmediateDeviceContext(), &cc);
}

AppW::~AppW() {
}

void AppW::onCreate() {
	Window::onCreate();
	GraphicsEn::get()->init();
	GraphicsEn::get()->createSwapChain();
	m_swap_chain = GraphicsEn::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	vertex list[] = {
		//x y z RGB
		{Vector3D(-0.5f,-0.5f,0.0f),Vector3D(-0.32f,-0.11f,0.0f),Vector3D(0,0,0),Vector3D(0,1,0)}, // POS1
		{Vector3D(-0.5f,0.5f,0.0f),Vector3D(-0.11f,0.78f,0.0f),Vector3D(1,1,0),Vector3D(0,1,1) }, // POS2
		{Vector3D(0.5f,-0.5f,0.0f),Vector3D(0.75f,-0.73f,0.0f),Vector3D(0,0,1),Vector3D(1,0,0) },// POS2
		{Vector3D(0.5f,0.5f,0.0f),Vector3D(0.88f,0.77f,0.0f),Vector3D(1,1,1),Vector3D(0,0,1) }
		//{Vector3D(-0.5f,-0.5f,0.0f),Vector3D(0,1,0)}, // POS1
		//{Vector3D(-0.5f,0.5f,0.0f),Vector3D(0,1,1) }, // POS2
		//{Vector3D(0.5f,-0.5f,0.0f),Vector3D(1,0,0) },// POS2
		//{Vector3D(0.5f,0.5f,0.0f),Vector3D(0,0,1) }
	};
	m_vb = GraphicsEn::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEn::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEn::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEn::get()->releaseCompiledShader();
	GraphicsEn::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEn::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEn::get()->releaseCompiledShader();
	constant cc;
	cc.m_time = 0;
	m_cb = GraphicsEn::get()->createConstBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void AppW::onUpdate() {
	Window::onUpdate();
	GraphicsEn::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 1, 0, 1, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEn::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	udateQuadPosition();
	GraphicsEn::get()->getImmediateDeviceContext()->setConstBuffer(m_vs, m_cb);
	GraphicsEn::get()->getImmediateDeviceContext()->setConstBuffer(m_ps, m_cb);
	GraphicsEn::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEn::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEn::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEn::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	m_swap_chain->present(true);
	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppW::onDestroy() {
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEn::get()->release();
}
