#pragma once

#include <array>
#include <vector>
#include <algorithm>

class Keyboard
{
private:
	enum class KeyStatus
	{
		UP,
		PRESSED,
		DOWN,
		RELEASED
	};

	static constexpr size_t VKCodesNumber{ 256 };
	std::array<KeyStatus, VKCodesNumber> keysStatus{};
	std::vector<size_t> pressedReleasedKeys{};
	std::vector<size_t> downKeys{};

public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard operator=(const Keyboard&) = delete;

	void OnKeyDown(int vkCode);
	void OnKeyUp(int vkCode);
	void UpdateKeys();
	void FlushKeys();

	KeyStatus GetKeyStatus(int vkCode) const;
};

