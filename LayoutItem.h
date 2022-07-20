#pragma once

class LayoutItem
{
public:
	enum class ItemType
	{
		None,
		Line,
		Holdable
	};
	ItemType itemType{ ItemType::None };
	virtual void Draw() const = 0;
};

