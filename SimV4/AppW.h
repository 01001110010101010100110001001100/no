#pragma once
#pragma comment(lib,"d3d11.lib") 
#include "Window.h"
#include "GraphicsEn.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstBuffer.h"
#include "VertexShader.h"
#include  "PixelShader.h"

class AppW: public Window
{
public:
	AppW();
	void udateQuadPosition();
	~AppW();
	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstBuffer* m_cb;
private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;
	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
};

