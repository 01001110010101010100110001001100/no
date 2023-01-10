#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class ConstBuffer;
class VertexShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);
	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);
	void setConstBuffer(VertexShader* vertex_shader, ConstBuffer* buffer);
	void setConstBuffer(PixelShader* pixel_shader, ConstBuffer* buffer);
	bool release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
private:
	friend class ConstBuffer;
};

