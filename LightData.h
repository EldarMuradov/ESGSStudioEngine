#pragma once
#include "Vector4D.h"

__declspec(align(16))
struct LightData
{
	Vector4D color;
	Vector4D direction;
};