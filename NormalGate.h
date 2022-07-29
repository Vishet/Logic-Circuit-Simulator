#pragma once

#include "MoveableCircuitItem.h"
#include "Graphics.h"
#include "SignalInput.h"

#include <string>

class NormalGate : public MoveableCircuitItem
{
private:
	D2D1_RECT_F rcItem;
	const D2D1_COLOR_F textColor;
	const std::wstring itemText;

	SignalInput inputA;
	SignalInput inputB;
	static constexpr float ioRadius{ 5.0f };

public:
	NormalGate(
		const Graphics* pGraphics,
		const D2D1_RECT_F& rcItem,
		const D2D1_COLOR_F& bgColor,
		const D2D1_COLOR_F& textColor,
		const std::wstring& itemText
	);

	void Draw() const override;
	SignalInput* OnRightUp(const D2D1_POINT_2F& mousePoint) override;
	MoveableCircuitItem* OnClick(const D2D1_POINT_2F& mousePoint) override;
	void Move(const D2D1_POINT_2F& mousePoint);

	bool isMouseOverInput(const D2D1_POINT_2F& mousePoint, D2D1_POINT_2F& inputPoint) const override;
};

