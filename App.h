#pragma once

#include "Window.h"
#include "Keyboard.h"
//#include "Graphics.h"

class App
{
private:
	Keyboard keyboard{};
	Window window{&keyboard};

public:
	App() = default;
	App(const App&) = delete;
	App operator=(const App&) = delete;
	
	int Run();

	//void Update();
	//void Render();
};

