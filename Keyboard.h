#pragma once

#include <array>
#include <vector>
#include <algorithm>

class Keyboard
{
public:
	enum class KeyStatus
	{
		UP,
		PRESSED,
		DOWN,
		RELEASED
	};

private:
	static constexpr size_t VKCodesNumber{ 256 };
	std::array<KeyStatus, VKCodesNumber> keysStatus{};
	std::vector<size_t> pressedReleasedKeys{};
	std::vector<size_t> downKeys{};

	void OnKeyDown(int vkCode);
	void OnKeyUp(int vkCode);
	void Flush();

public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard operator=(const Keyboard&) = delete;

	void Update();

	KeyStatus GetKeyStatus(int vkCode) const;

	friend class Window;
};

