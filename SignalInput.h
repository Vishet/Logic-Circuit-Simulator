#pragma once

#include "SignalIO.h"
#include "SignalLine.h"

class SignalInput : public SignalIO
{
private:
	SignalLine* signalLine{};

public:
	SignalInput(
		const Graphics* pGraphics,
		const D2D1_POINT_2F& position,
		const float radius, 
		const D2D1_COLOR_F& bgColor,
		const D2D1_COLOR_F& activeColor
	);

	void Move(const D2D1_POINT_2F& ptMoveTo) override;
	void LinkLine(SignalLine* signalLine) { this->signalLine = signalLine; }
	bool isLinked() const { return signalLine; }
};

