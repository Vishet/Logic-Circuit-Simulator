#pragma once

class LayoutItem
{
public:
	enum class ItemType
	{
		None,
		Holdable,
		Line,
		Rectangle
	};
	virtual void Draw() const = 0;
	ItemType GetItemType() const { return itemType; }

protected:
	ItemType itemType{ ItemType::None };
};

