#pragma once

#include "Buffer.h"

template <class T>
class StaticArrayBuffer : public Buffer<T>
{
public:
	StaticArrayBuffer() : Buffer<T>(GL_ARRAY_BUFFER) {}
	virtual ~StaticArrayBuffer() {}

	void storeData(const std::vector<T>& data) override {
		this->bind();
		glBufferData(this->m_Target, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
	}
};
