#pragma once

#include "LayoutItem.h"
#include "CircuitItem.h"
#include <Windows.h>
#include <vector>
#include <atlbase.h>
#include <string>

#include <dwrite.h>
#pragma comment(lib, "dwrite")

#include <d2d1.h>
#pragma comment(lib, "d2d1")

class Graphics
{
private:
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	IDWriteFactory* pWriteFactory;
	static constexpr auto fontName{ L"Verdana" };
	static constexpr float fontSize{ 30.0f };
	static constexpr float realFontSize{ 22.0f };
	IDWriteTextFormat* pTextFormat;

public:
	Graphics();
	~Graphics();	

	static bool InitializeCOM();
	static void UnitializeCOM();

	bool Initialize(HWND hWindow);
	void Unitialize() const;

	void BeginDraw() const;
	void BeginDraw(const D2D1::ColorF& clearColor) const;
	bool EndDraw() const;

	void Fill(const D2D1::ColorF& clearColor) const;

	void DrawLine(const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, float strokeWidth) const;
	void FillRectangle(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color) const;
	void DrawWString(const std::wstring& text, const D2D1_COLOR_F& textColor, const D2D1_RECT_F& layoutRect) const;
	void DrawWString(const std::wstring& text, const D2D1_COLOR_F& textColor, int x, int y);
	void FillCircle(const D2D1_POINT_2F& centerPoint, const float radius, const D2D1_COLOR_F& bgColor) const;
};

