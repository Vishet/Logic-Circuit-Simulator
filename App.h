#pragma once

#include "Window.h"
//#include "Graphics.h"

class App
{
private:
	Window window{};

public:
	App() = default;
	App(const App&) = delete;
	App operator=(const App&) = delete;
	
	int Run();

	//void Update();
	//void Render();
};

