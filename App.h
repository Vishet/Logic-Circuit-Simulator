#pragma once

#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
//#include "Graphics.h"

class App
{
private:
	Keyboard keyboard{};
	Mouse mouse{};
	Window window{&keyboard, &mouse};

public:
	App() = default;
	App(const App&) = delete;
	App operator=(const App&) = delete;
	
	int Run();

	void Update();
	//void Render();
};

