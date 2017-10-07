#pragma once

#include "Buffer.h"

template <class T>
class StaticArrayBuffer : public Buffer<T>
{
public:
	StaticArrayBuffer() : Buffer<T>(GL_ARRAY_BUFFER) {}
	virtual ~StaticArrayBuffer() {}
};
