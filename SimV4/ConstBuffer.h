#pragma once
#pragma comment(lib,"d3d11.lib") 
#include <d3d11.h>

class DeviceContext;

class ConstBuffer
{
public:
	ConstBuffer();
	bool load(void* buffer, UINT size_buffer); 
	void update(DeviceContext* context, void* buffer);
	bool release();
	~ConstBuffer();
private:
	ID3D11Buffer* m_buffer;
private:
	friend class DeviceContext;
};