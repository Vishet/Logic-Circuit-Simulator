#pragma once
#include "NormalGate.h"
#include "Graphics.h"
#include "SignalInput.h"

class ANDGate : public NormalGate
{
public:
	ANDGate(
		const Graphics* pGraphics, 
		const D2D1_RECT_F& rcItem, 
		const D2D1_COLOR_F bgColor, 
		const D2D1_COLOR_F textColor
	);
};

