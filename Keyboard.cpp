#include "Keyboard.h"

void Keyboard::OnKeyDown(int vkCode)
{
	if (keysStatus.at(vkCode) == KeyStatus::UP)
	{
		keysStatus.at(vkCode) = KeyStatus::PRESSED;
		pressedReleasedKeys.push_back(vkCode);
	}
	else
		keysStatus.at(vkCode) = KeyStatus::DOWN;
}

void Keyboard::OnKeyUp(int vkCode)
{
	if (keysStatus.at(vkCode) == KeyStatus::DOWN)
	{
		keysStatus.at(vkCode) = KeyStatus::RELEASED;
		pressedReleasedKeys.push_back(vkCode);
	}
	else
		keysStatus.at(vkCode) = KeyStatus::UP;
}

void Keyboard::UpdateKeys()
{
	for (const auto& keyCode : pressedReleasedKeys)
	{
		if (keysStatus.at(keyCode) == KeyStatus::RELEASED)
			keysStatus.at(keyCode) = KeyStatus::UP;
		else if (keysStatus.at(keyCode) == KeyStatus::PRESSED)
			keysStatus.at(keyCode) = KeyStatus::DOWN;
	}

	pressedReleasedKeys.clear();
}

void Keyboard::FlushKeys()
{
	keysStatus.fill(KeyStatus::UP);
	pressedReleasedKeys.clear();
}
