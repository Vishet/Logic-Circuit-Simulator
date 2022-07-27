#pragma once

#include "SignalIO.h"
#include "SignalInput.h"
#include "SignalLine.h"

class SignalOutput : public SignalIO
{
private:
	SignalInput* pLinkedInput{};
	SignalLine signalLine;

public:
	SignalOutput(
		const Graphics* pGraphics,
		const D2D1_POINT_2F& position,
		const float radius,
		const D2D1_COLOR_F& bgColor
	);

	void LinkInput(SignalInput* pInput);
	void SetStatus(bool status) override;
	void UpdateLine(const D2D1_POINT_2F& newPoint);
	void UpdateLine();
	void Draw() const override;
	void Move(const D2D1_POINT_2F& ptMoveTo) override;
	SignalLine* GetLinePtr() { return &signalLine; }
};

