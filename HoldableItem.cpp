#include "HoldableItem.h"

HoldableItem::HoldableItem(
	const Graphics* pGraphics, 
	const D2D1_RECT_F& rcItem, 
	const D2D1_COLOR_F& bgColor, const D2D1_COLOR_F& textColor, 
	const std::wstring& itemText
) :
	pGraphics{ pGraphics },
	rcItem{ rcItem },
	bgColor{ bgColor },
	textColor{ textColor },
	itemText{ itemText }
{
	itemType = ItemType::Holdable;
}

void HoldableItem::Move(const D2D1_POINT_2F& mousePoint)
{
	const float width{ rcItem.right - rcItem.left };
	const float height{ rcItem.bottom - rcItem.top };

	rcItem.right = mousePoint.x + width / 2.0f;
	rcItem.bottom = mousePoint.y + height / 2.0f;
	rcItem.left = mousePoint.x - width / 2.0f;
	rcItem.top = mousePoint.y - height / 2.0f;
}

void HoldableItem::Draw() const
{
	pGraphics->FillRectangle(rcItem, bgColor);
	pGraphics->DrawWString(itemText, textColor, rcItem);
}