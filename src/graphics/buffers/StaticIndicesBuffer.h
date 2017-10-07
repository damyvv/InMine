#pragma once

#include "Buffer.h"

template <class T>
class StaticIndicesBuffer : public Buffer<T>
{
public:
	StaticIndicesBuffer() : Buffer<T>(GL_ELEMENT_ARRAY_BUFFER) {}
	virtual ~StaticIndicesBuffer() {}
};
