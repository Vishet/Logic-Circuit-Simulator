#pragma once

#include "SignalIO.h"

class SignalInput : public SignalIO
{
public:
	SignalInput(
		const Graphics* pGraphics,
		const D2D1_POINT_2F& offsetPosition, 
		const float radius, 
		const D2D1_COLOR_F& bgColor
	);

	//void LinkItem();
};

