#include "stdafx.h"
#include "StartCamera.h"


StartCamera::StartCamera(int No, const char* obj_name) :GameObject(No, obj_name)
{
}


StartCamera::~StartCamera()
{
}

bool StartCamera::Start()
{

	return true;
}

void StartCamera::Update()
{
}
