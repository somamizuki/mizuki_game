#pragma once
#include "GPUBuffer.h"
class ConstantBuffer:public GPUBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	bool Create(const void* pInitData, int bufferSize);
};

