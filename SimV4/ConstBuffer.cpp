#include "ConstBuffer.h"
#include "GraphicsEn.h"
#include "DeviceContext.h"

ConstBuffer::ConstBuffer() {
}

bool ConstBuffer::load(void* buffer, UINT size_buffer) {
	if (m_buffer)m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags + D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;
	if (FAILED(GraphicsEn::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer))) {
		return false;
	}
	return true;
}

void ConstBuffer::update(DeviceContext* context, void* buffer) {
	context->m_device_context->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstBuffer::release() {
	if (m_buffer)m_buffer->Release();
	delete this;
	return true;
}

ConstBuffer::~ConstBuffer() {
}
