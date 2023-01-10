#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>

class GraphicsEn;
class DeviceContext;

class PixelShader
{
public:
	PixelShader();
	void release();
	~PixelShader();
private:
	bool init(const void* shader_byte_code, size_t byte_code_size);
private:
	ID3D11PixelShader* m_ps;
private:
	friend class GraphicsEn;
	friend class DeviceContext;
};