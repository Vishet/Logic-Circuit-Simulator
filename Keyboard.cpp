#include "Keyboard.h"

void Keyboard::OnKeyDown(int vkCode)
{
	if (keysStatus.at(vkCode) == KeyStatus::UP)
	{
		keysStatus.at(vkCode) = KeyStatus::PRESSED;
		pressedReleasedKeys.push_back(vkCode);
	}
}

void Keyboard::OnKeyUp(int vkCode)
{
	if (keysStatus.at(vkCode) == KeyStatus::DOWN)
	{
		keysStatus.at(vkCode) = KeyStatus::RELEASED;
		pressedReleasedKeys.push_back(vkCode);
		
		const auto downKey{ std::find(downKeys.begin(), downKeys.end(), vkCode) };
		if (downKey != downKeys.end())
			downKeys.erase(downKey);
	}
}

void Keyboard::Update()
{
	for (const auto& keyCode : pressedReleasedKeys)
	{
		if (keysStatus.at(keyCode) == KeyStatus::RELEASED)
			keysStatus.at(keyCode) = KeyStatus::UP;
		else if (keysStatus.at(keyCode) == KeyStatus::PRESSED)
		{
			keysStatus.at(keyCode) = KeyStatus::DOWN;
			downKeys.push_back(keyCode);
		}
	}

	pressedReleasedKeys.clear();
}

void Keyboard::Flush()
{
	keysStatus.fill(KeyStatus::UP);

	for (auto keyCode : downKeys)
	{
		keysStatus.at(keyCode) = KeyStatus::RELEASED;
	}

	downKeys.clear();
	pressedReleasedKeys.clear();
}

Keyboard::KeyStatus Keyboard::GetKeyStatus(int vkCode) const
{
	return keysStatus.at(vkCode);
}
