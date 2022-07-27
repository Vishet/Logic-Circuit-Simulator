#include "Graphics.h"

Graphics::Graphics() :
	pFactory{},
	pRenderTarget{},
	pWriteFactory{}
{

}

Graphics::~Graphics()
{

}

bool Graphics::InitializeCOM()
{
	HRESULT hr{};
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr))
		return false;

	return true;
}

void Graphics::UnitializeCOM()
{
	CoUninitialize();
}

bool Graphics::Initialize(HWND hWindow)
{
	HRESULT hr{};

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	if (FAILED(hr)) return false;

	RECT rc{};
	GetClientRect(hWindow, &rc);
	D2D1_SIZE_U windowSize = D2D1::SizeU(rc.right, rc.bottom);
	hr = pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWindow, windowSize),
		&pRenderTarget
	);
	if (FAILED(hr)) return false;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(pWriteFactory), reinterpret_cast<IUnknown**>(&pWriteFactory));
	if (FAILED(hr)) return false;

	hr = pWriteFactory->CreateTextFormat(
		fontName,
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"",
		&pTextFormat
	);
	if (FAILED(hr)) return false;

	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	return true;
}

void Graphics::Unitialize() const
{
	pRenderTarget->Release();
	pFactory->Release();
	pTextFormat->Release();
	pWriteFactory->Release();
}

void Graphics::BeginDraw() const
{
	pRenderTarget->BeginDraw();
}

void Graphics::BeginDraw(const D2D1::ColorF& clearColor) const
{
	this->BeginDraw();
	this->Fill(clearColor);
}

void Graphics::BeginDraw(const D2D1::ColorF& clearColor, const std::vector<LayoutItem*>& layoutItems) const
{
	this->BeginDraw(clearColor);
	this->DrawLayout(layoutItems);
}

void Graphics::BeginDraw(const D2D1::ColorF& clearColor, const std::vector<LayoutItem*>& layoutItems, const std::vector<CircuitItem*>& circuitItems, const std::vector<LayoutItem*>& signalLines) const
{
	this->BeginDraw(clearColor);
	this->DrawSignalLines(signalLines);
	this->DrawCircuit(circuitItems);
	this->DrawLayout(layoutItems);
}

void Graphics::Fill(const D2D1::ColorF& clearColor) const
{
	pRenderTarget->Clear(clearColor);
}

bool Graphics::EndDraw() const
{
	return SUCCEEDED(pRenderTarget->EndDraw());
}

void Graphics::DrawLayout(const std::vector<LayoutItem*>& layoutItems) const
{
	for (const auto& item : layoutItems)
		if(item)
			item->Draw();
}

void Graphics::DrawLine(const D2D1_POINT_2F& pointA, const D2D1_POINT_2F& pointB, const D2D1_COLOR_F& color, float strokeWidth) const
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};
	pRenderTarget->CreateSolidColorBrush(color, &pBrush);
	pRenderTarget->DrawLine(pointA, pointB, pBrush, strokeWidth);
}

void Graphics::FillRectangle(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color) const
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};
	pRenderTarget->CreateSolidColorBrush(color, &pBrush);
	pRenderTarget->FillRectangle(rect, pBrush);
}

void Graphics::DrawWString(const std::wstring& text, const D2D1_COLOR_F& textColor, const D2D1_RECT_F& layoutRect) const
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};
	pRenderTarget->CreateSolidColorBrush(textColor, &pBrush);

	pRenderTarget->DrawTextW(
		text.c_str(),
		static_cast<UINT32>(text.size()),
		pTextFormat,
		D2D1::RectF(
			layoutRect.left, 
			layoutRect.top + (layoutRect.bottom - layoutRect.top - realFontSize) / 2 - (fontSize - realFontSize), 
			layoutRect.right, layoutRect.bottom
		),
		pBrush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP
	);
}

void Graphics::FillCircle(const D2D1_POINT_2F& centerPoint, const float radius, const D2D1_COLOR_F& bgColor) const
{
	CComPtr<ID2D1SolidColorBrush> pBrush{};
	pRenderTarget->CreateSolidColorBrush(bgColor, &pBrush);
	pRenderTarget->FillEllipse(D2D1::Ellipse(centerPoint, radius, radius), pBrush);
}

void Graphics::DrawCircuit(const std::vector<CircuitItem*>& circuitItems) const
{
	for (const auto& item : circuitItems)
		if (item)
			item->Draw();
}

void Graphics::DrawSignalLines(const std::vector<LayoutItem*>& signalLines) const
{
	for (const auto& signalLine : signalLines)
		if (signalLine)
			signalLine->Draw();
}