#include "Window.h"

Window::Window(Keyboard* keyboard, Mouse* mouse) :
	keyboard{ keyboard },
	mouse{ mouse }
{
}

Window::~Window()
{
	for (auto& layoutItem : layoutVector)
		delete layoutItem;

	for (auto& circuitItem : circuitVector)
		delete circuitItem;

	pGraphics->Unitialize();
}

bool Window::Update() const
{
	pGraphics->BeginDraw(D2D1::ColorF::Black, layoutVector, circuitVector, signalLinesVector);
	return pGraphics->EndDraw();
}

bool Window::Create(const wchar_t* szWindowName, WindowClass::ClassName className, int nWidth, int nHeight, int x, int y)
{
	WindowClass::RegisterMyClass(className, WndProcSetup);

	std::wstring classNameString{};
	WindowClass::GetEnumString(className, classNameString);
	const wchar_t* szClassName{ classNameString.c_str() };

	this->nWidth = static_cast<float>(nWidth);
	this->nHeight = static_cast<float>(nHeight);

	RECT rcWnd{};
	rcWnd.right = nWidth;
	rcWnd.bottom = nHeight;
	AdjustWindowRect(&rcWnd, WS_OVERLAPPEDWINDOW, false);

	hWindow = CreateWindowExW(
		NULL,
		szClassName, szWindowName,
		WS_OVERLAPPEDWINDOW,
		x, y, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top,
		NULL, NULL, GetModuleHandle(0), this 
	);

	if (!pGraphics->Initialize(hWindow))
	{
		MessageBox(hWindow, L"pGraphics->Initialize() failed!", L"ERROR", MB_ICONERROR | MB_OK);
		this->Destroy();
		return false;
	}

	float maxX{ this->nWidth - 1 };
	float maxY{ this->nHeight - 1 };

	float lineY{ 510.0f };

	layoutVector.push_back(new Line(
		pGraphics,
		D2D1::Point2F(0, lineY),
		D2D1::Point2F(maxX, lineY),
		D2D1::ColorF(D2D1::ColorF::White),
		2.0f
	));

	layoutVector.push_back(new HoldableAND(
		pGraphics,
		D2D1::RectF(15, lineY + 17.0f, 
			115.0f, maxY - 15.0f
		),
		D2D1::ColorF(D2D1::ColorF::White),
		D2D1::ColorF(D2D1::ColorF::Black)
	));

	layoutVector.push_back(new HoldableOR(
		pGraphics,
		D2D1::RectF(130, lineY + 17.0f,
			230.0f, maxY - 15.0f
		),
		D2D1::ColorF(D2D1::ColorF::White),
		D2D1::ColorF(D2D1::ColorF::Black)
	));

	const float inputRadius{ (maxY - lineY - 32.0f) / 2 };
	layoutVector.push_back(new HoldableInput(
		pGraphics,
		D2D1::Point2F(245.0f + inputRadius, lineY + 17.0f + inputRadius),
		inputRadius,
		D2D1::ColorF(D2D1::ColorF::White),
		D2D1::ColorF(D2D1::ColorF::Blue)
	));

	pGraphics->BeginDraw(D2D1::ColorF::White, layoutVector);
	if(!pGraphics->EndDraw())
		MessageBox(hWindow, L"pGraphics->EndDraw() failed!\nOn Window::Create()", L"ERROR", MB_ICONERROR | MB_OK);

	return true;
}

void Window::Destroy()
{
	DestroyWindow(hWindow);
}

void Window::Show() const
{
	ShowWindow(hWindow, SW_SHOW);
}

void Window::Hide() const
{
	ShowWindow(hWindow, SW_HIDE);
}

LRESULT Window::WndProcSetup(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate{ reinterpret_cast<CREATESTRUCT*>(lParam) };
		Window* creatorWindow{ static_cast<Window*>(pCreate->lpCreateParams) };
		SetWindowLongPtr(hWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(creatorWindow));
		creatorWindow->hWindow = hWindow;

		return creatorWindow->WndProc(hWindow, uMsg, wParam, lParam);
	}
	else
	{
		Window* creatorWindow{ reinterpret_cast<Window*>(GetWindowLongPtr(hWindow, GWLP_USERDATA)) };
		if(creatorWindow)
			return creatorWindow->WndProc(hWindow, uMsg, wParam, lParam);
		else
			return DefWindowProc(hWindow, uMsg, wParam, lParam);
	}
}

LRESULT Window::WndProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps{};
		BeginPaint(hWindow, &ps);

		if (!this->Update())
			MessageBox(hWindow, L"this->Update() failed!", L"ERROR", MB_ICONERROR | MB_OK);
		return 0;

		EndPaint(hWindow, &ps);
	}

	case WM_LBUTTONDOWN:
		{
		mouse->OnLeftDown();
		}
		if (!lmbPrevious)
		{
			for (auto& item : layoutVector)
			{
				if (item && item->itemType == LayoutItem::ItemType::Holdable)
				{
					pHoldingItem = dynamic_cast<HoldableItem*>(item)->OnClick(D2D1::Point2F(
						static_cast<float>(GET_X_LPARAM(lParam)),
						static_cast<float>(GET_Y_LPARAM(lParam))
					));
					if (pHoldingItem)
					{
						layoutVector.push_back(pHoldingItem);
						if(!this->Update())
							MessageBox(hWindow, L"this->Update() failed!", L"ERROR", MB_ICONERROR | MB_OK);
						break;
					}
				}
			}
			for (auto& item : circuitVector)
			{
				if (item)
				{
					pHoldingCircuitItem = dynamic_cast<MoveableCircuitItem*>(item)->OnClick(D2D1::Point2F(
						static_cast<float>(GET_X_LPARAM(lParam)),
						static_cast<float>(GET_Y_LPARAM(lParam))
					));
					if (pHoldingCircuitItem)
						break;
				}		
			}

			lmbPrevious = true;
		}
		return 0;

	case WM_LBUTTONUP:
	{
		mouse->OnLeftUp();
	}
		for (size_t i{0}; i < layoutVector.size(); i++)
		{
			if (layoutVector.at(i) == pHoldingItem)
			{
				layoutVector.erase(layoutVector.begin() + i);
				circuitVector.push_back(pHoldingItem->Drop());
				break;
			}
		}
		delete pHoldingItem;
		pHoldingItem = nullptr;

		pHoldingCircuitItem = nullptr;

		if (!this->Update())
			MessageBox(hWindow, L"this->Update() failed!", L"ERROR", MB_ICONERROR | MB_OK);

		lmbPrevious = false;
		return 0;

	case WM_RBUTTONDOWN:
	{
		mouse->OnRightDown();
	}
		if (!rmbPrevious)
		{
			for (auto& item : circuitVector)
			{
				pSelectedSignalOutput = item->OnRightClick(D2D1::Point2F(
					static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam))
				));

				if (pSelectedSignalOutput)
				{
					bool findedLine{ false };
					for (size_t index{ 0 }; index < signalLinesVector.size(); index++)
						if (signalLinesVector.at(index) == pSelectedSignalOutput->GetLinePtr())
						{
							findedLine = true;
							break;
						}
					if(!findedLine)
						signalLinesVector.push_back(pSelectedSignalOutput->GetLinePtr());
					if (!this->Update())
						MessageBox(hWindow, L"this->Update() failed!", L"ERROR", MB_ICONERROR | MB_OK);
					break;
				}

			}

			rmbPrevious = true;
		}
		return 0;

	case WM_RBUTTONUP:
	{
		mouse->OnRightUp();
	}
		if (pSelectedSignalOutput)
		{
			for (auto& item : circuitVector)
			{
				pSelectedSignalInput = item->OnRightUp(D2D1::Point2F(
					static_cast<float>(GET_X_LPARAM(lParam)),
					static_cast<float>(GET_Y_LPARAM(lParam))
				));
				if (pSelectedSignalInput)
				{
					pSelectedSignalOutput->LinkInput(pSelectedSignalInput);
					pSelectedSignalInput->LinkLine(pSelectedSignalOutput->GetLinePtr());
					pSelectedSignalOutput->UpdateLine(pSelectedSignalInput->GetPosition());
					if (!this->Update())
						MessageBox(hWindow, L"this->Update() failed!", L"ERROR", MB_ICONERROR | MB_OK);
					break;
				}
			}

			
			if (!pSelectedSignalInput)
			{
				SignalLine* resetedLine{ pSelectedSignalOutput->GetLinePtr() };

				for (size_t index{ 0 }; index < signalLinesVector.size(); index++)
					if (signalLinesVector.at(index) == resetedLine)
					{
						signalLinesVector.erase(signalLinesVector.begin() + index);
						break;
					}

				if (!this->Update())
					MessageBox(hWindow, L"this->Update() failed!", L"ERROR", MB_ICONERROR | MB_OK);				
			}

			pSelectedSignalOutput = nullptr;
			pSelectedSignalInput = nullptr;
		}
		rmbPrevious = false;
		return 0;

	case WM_MOUSEMOVE:
	{
		mouse->OnMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	}
		if ((wParam & MOUSEMOVE_LMB) == MOUSEMOVE_LMB)
		{
			if (pHoldingItem)
				pHoldingItem->Move(D2D1::Point2F(
					static_cast<float>(GET_X_LPARAM(lParam)),
					static_cast<float>(GET_Y_LPARAM(lParam)))
				);
			else if (pHoldingCircuitItem)
				pHoldingCircuitItem->Move(D2D1::Point2F(
					static_cast<float>(GET_X_LPARAM(lParam)),
					static_cast<float>(GET_Y_LPARAM(lParam)))
				);
			
			if (!this->Update())
				MessageBox(hWindow, L"this->Update() failed!", L"ERROR", MB_ICONERROR | MB_OK);
		}
		if ((wParam & MOUSEMOVE_RMB) == MOUSEMOVE_RMB)
		{
			if (pSelectedSignalOutput)
			{
				pSelectedSignalOutput->UpdateLine(D2D1::Point2F(
					static_cast<float>(GET_X_LPARAM(lParam)),
					static_cast<float>(GET_Y_LPARAM(lParam))
				));

				if (!this->Update())
					MessageBox(hWindow, L"this->Update() failed!", L"ERROR", MB_ICONERROR | MB_OK);
			}
		}
		{
			POINT pt{ mouse->GetMousePosition() };
			OutputDebugString( (std::to_wstring(pt.x) + L' ' + std::to_wstring(pt.y) + L'\n').c_str());
		}
		return 0;

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		if (!(HIWORD(lParam) & 0x4000))
		{
			keyboard->OnKeyDown(static_cast<int>(wParam));
		}
		return 0;
	}

	case WM_KEYUP:
		if (HIWORD(lParam) & 0x4000)
		{
			keyboard->OnKeyUp(static_cast<int>(wParam));
		}
		return 0;

	case WM_KILLFOCUS:
		keyboard->Flush();
		return 0;

	default:
		return DefWindowProc(hWindow, uMsg, wParam, lParam);
	}

	return 0;
}