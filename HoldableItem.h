#pragma once

#include "LayoutItem.h"
#include "Graphics.h"
#include "CircuitItem.h"
#include "Helper.h"
#include <d2d1.h>
#include <string>

class HoldableItem : public LayoutItem
{
protected:
	const Graphics* pGraphics{};
	D2D1_RECT_F rcItem{};
	D2D1_COLOR_F bgColor{};
	std::wstring itemText{};
	D2D1_COLOR_F textColor{};

public:
	HoldableItem(
		const Graphics* pGraphics, 
		const D2D1_RECT_F& rcItem,
		const D2D1_COLOR_F& bgColor, const D2D1_COLOR_F& textColor,
		const std::wstring& itemText
	);

	virtual CircuitItem* Drop() const = 0;
	virtual HoldableItem* OnClick(const D2D1_POINT_2F& mousePoint) const = 0;

	virtual void Move(const D2D1_POINT_2F& mousePoint);
	virtual void Draw() const override;
};

