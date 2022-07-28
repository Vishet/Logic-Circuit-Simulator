#include "App.h"

App::~App()
{
	for (auto& layoutItem : layoutVector)
		delete layoutItem;

	for (auto& circuitItem : circuitVector)
		delete circuitItem;

	graphics.Unitialize();
}

int App::Run()
{
	if (!window.Create(L"Logic Circuit Simulator", WindowClass::ClassName::VCLASS, 800, 600, 40, 60))
		return -1;

	if (!graphics.Initialize(window.GetHwnd()))
		return -1;

	CreateLayout();

	window.Show();

	std::optional<WPARAM> exitCode{};
	while (true)
	{
		if (exitCode = window.ProcessMessages())
			break;

		Update();
		Render();
	}

	return *exitCode;
}

void App::Update()
{
	if (mouse.GetLMBStatus() == Mouse::MouseStatus::PRESSED)
		OnLMBClicked();

	if (mouse.GetLMBStatus() == Mouse::MouseStatus::RELEASED)
		OnLMBReleased();

	if (mouse.GetRMBStatus() == Mouse::MouseStatus::PRESSED)
		OnRMBClicked();

	if (mouse.GetRMBStatus() == Mouse::MouseStatus::RELEASED)
		OnRMBReleased();

	if (mouse.GetLMBStatus() == Mouse::MouseStatus::DOWN)
		OnLMBDown();

	if (mouse.GetRMBStatus() == Mouse::MouseStatus::DOWN)
		OnRMBDown();

	mouse.Update();
	keyboard.Update();

	if (fpsDelayTimer.GetElapsedSeconds() > 1)
	{
		frameRate = fpsTimer.GetTickRate();
		fpsDelayTimer.Set();
	}
	fpsTimer.Set();
}

void App::Render()
{
	graphics.BeginDraw(D2D1::ColorF::Black);
	
	for (const auto& line : signalLinesVector)
		if (line)
			line->Draw();

	for (const auto& item : circuitVector)
		if (item)
			item->Draw();

	for (const auto& item : layoutVector)
		if (item)
			item->Draw();

	DrawFrameRate();

	graphics.EndDraw();
}

inline void App::DrawFrameRate()
{
	graphics.DrawWString(
		std::to_wstring(frameRate),
		D2D1::ColorF(D2D1::ColorF::White),
		0, 0
	);
}

void App::CreateLayout()
{
	float maxX{ window.GetWidth() - 1 };
	float maxY{ window.GetHeight() - 1 };

	float lineY{ 510.0f };

	layoutVector.push_back(new Line(
		&graphics,
		D2D1::Point2F(0, lineY),
		D2D1::Point2F(maxX, lineY),
		D2D1::ColorF(D2D1::ColorF::White),
		2.0f
	));

	layoutVector.push_back(new HoldableAND(
		&graphics,
		D2D1::RectF(15, lineY + 17.0f,
			115.0f, maxY - 15.0f
		),
		D2D1::ColorF(D2D1::ColorF::White),
		D2D1::ColorF(D2D1::ColorF::Black)
	));

	layoutVector.push_back(new HoldableOR(
		&graphics,
		D2D1::RectF(130, lineY + 17.0f,
			230.0f, maxY - 15.0f
		),
		D2D1::ColorF(D2D1::ColorF::White),
		D2D1::ColorF(D2D1::ColorF::Black)
	));

	const float inputRadius{ (maxY - lineY - 32.0f) / 2 };
	layoutVector.push_back(new HoldableInput(
		&graphics,
		D2D1::Point2F(245.0f + inputRadius, lineY + 17.0f + inputRadius),
		inputRadius,
		D2D1::ColorF(D2D1::ColorF::White),
		D2D1::ColorF(D2D1::ColorF::Blue)
	));
}

void App::OnLMBClicked()
{
	OutputDebugString(L"Clickou\n");
	for (auto& item : layoutVector)
	{
		if (item->itemType == LayoutItem::ItemType::Holdable)
		{
			pHoldingItem = dynamic_cast<HoldableItem*>(item)->OnClick(D2D1::Point2F(
				static_cast<float>(mouse.GetX()),
				static_cast<float>(mouse.GetY())
			));
			if (pHoldingItem)
			{
				layoutVector.push_back(pHoldingItem);
				break;
			}
		}
	}
	for (auto item{ circuitVector.rbegin() }; item != circuitVector.rend(); ++item)
	{
		if (true)
		{
			pHoldingCircuitItem = dynamic_cast<MoveableCircuitItem*>(*item)->OnClick(D2D1::Point2F(
				static_cast<float>(mouse.GetX()),
				static_cast<float>(mouse.GetY())
			));
			if (pHoldingCircuitItem)
				break;
		}
	}
}

void App::OnLMBReleased()
{
	for(auto item{ layoutVector.begin() }; item != layoutVector.end(); ++item)
	{
		if (*item == pHoldingItem)
		{
			layoutVector.erase(item);
			circuitVector.push_back(pHoldingItem->Drop());
			break;
		}
	}

	delete pHoldingItem;
	pHoldingItem = nullptr;

	pHoldingCircuitItem = nullptr;
}

void App::OnRMBClicked()
{
	for (auto item{ circuitVector.rbegin() }; item != circuitVector.rend(); ++item)
	{
		pSelectedSignalOutput = (*item)->OnRightClick(D2D1::Point2F(
			static_cast<float>(mouse.GetX()), static_cast<float>(mouse.GetY())
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
			if (!findedLine)
				signalLinesVector.push_back(pSelectedSignalOutput->GetLinePtr());

			break;
		}

	}
}

void App::OnRMBReleased()
{
	if (pSelectedSignalOutput)
	{
		for (auto item{ circuitVector.rbegin() }; item != circuitVector.rend(); ++item)
		{
			pSelectedSignalInput = (*item)->OnRightUp(D2D1::Point2F(
				static_cast<float>(mouse.GetX()),
				static_cast<float>(mouse.GetY())
			));
			if (pSelectedSignalInput)
			{
				pSelectedSignalOutput->LinkInput(pSelectedSignalInput);
				pSelectedSignalInput->LinkLine(pSelectedSignalOutput->GetLinePtr());
				pSelectedSignalOutput->UpdateLine(pSelectedSignalInput->GetPosition());

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
		}

		pSelectedSignalOutput = nullptr;
		pSelectedSignalInput = nullptr;
	}
}

void App::OnLMBDown()
{
	if (pHoldingItem)
		pHoldingItem->Move(D2D1::Point2F(
			static_cast<float>(mouse.GetX()),
			static_cast<float>(mouse.GetY()) )
		);
	else if (pHoldingCircuitItem)
		pHoldingCircuitItem->Move(D2D1::Point2F(
			static_cast<float>(mouse.GetX()),
			static_cast<float>(mouse.GetY()) )
		);
}

void App::OnRMBDown()
{
	if (pSelectedSignalOutput)
	{
		pSelectedSignalOutput->UpdateLine(D2D1::Point2F(
			static_cast<float>(mouse.GetX()),
			static_cast<float>(mouse.GetY())
		));
	}
}