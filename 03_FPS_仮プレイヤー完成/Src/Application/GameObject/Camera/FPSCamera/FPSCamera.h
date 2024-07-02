#pragma once
#include "../CameraBase.h"

class FPSCamera : public CameraBase
{
public:
	FPSCamera() { Init(); }
	~FPSCamera()override {}

	void Update()override;

private:
	void Init()override;
};