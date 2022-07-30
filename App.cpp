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

	if (pHoldingItem)
		pHoldingItem->Draw();

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

	layoutVector.push_back(new VRectangle(
		&graphics,
		D2D1::RectF(0, lineY, maxY, maxX),
		D2D1::ColorF(D2D1::ColorF::Black)
	));

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
	for (auto& item : layoutVector)
	{
		if (item->GetItemType() == LayoutItem::ItemType::Holdable)
		{
			pHoldingItem = dynamic_cast<HoldableItem*>(item)->OnClick(D2D1::Point2F(
				static_cast<float>(mouse.GetX()),
				static_cast<float>(mouse.GetY())
			));
			if (pHoldingItem)
				break;
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
	if (pHoldingItem)
	{
		auto circuitItem{ pHoldingItem->Drop() };

		circuitVector.push_back(circuitItem);
		if (circuitItem->GetType() == CircuitItem::ItemType::INPUT)
			signalLinesVector.push_back(dynamic_cast<Input*>(circuitItem)->GetSignalOutputPtr()->GetLinePtr());
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
			break;
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
				pSelectedSignalOutput->GetLinePtr()->ChangePointB(pSelectedSignalInput->GetPosition());

				break;
			}
		}

		if (!pSelectedSignalInput)
		{
			SignalLine* resetedLine{ pSelectedSignalOutput->GetLinePtr() };

			for (size_t index{ 0 }; index < signalLinesVector.size(); index++)
				if (signalLinesVector.at(index) == resetedLine)
				{
					dynamic_cast<SignalLine*>(signalLinesVector.at(index))->Reset();
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
		for (auto item{ circuitVector.rbegin() }; item != circuitVector.rend(); ++item)
		{
			D2D1_POINT_2F inputPoint{};
			if((*item)->isMouseOverInput(D2D1::Point2F(
				static_cast<float>(mouse.GetX()),
				static_cast<float>(mouse.GetY())
				), 
				inputPoint
			))
			{
				pSelectedSignalOutput->SetLockLine(false);
				pSelectedSignalOutput->GetLinePtr()->ChangePointB(
					D2D1::Point2F(
						static_cast<float>(inputPoint.x),
						static_cast<float>(inputPoint.y)
					)
				);
				return;
			}

		}

		if (keyboard.GetKeyStatus(VK_SHIFT) == Keyboard::KeyStatus::DOWN)
			pSelectedSignalOutput->SetLockLine(true);
		else
			pSelectedSignalOutput->SetLockLine(false);

		int changeX{mouse.GetX()};
		int changeY{mouse.GetY()};

		if (pSelectedSignalOutput->GetLinePtr()->GetLastLine()->IsDirectionLocked())
		{
			int alignedX{};
			int alignedY{};

			D2D1_POINT_2F selectedPoint{ pSelectedSignalOutput->GetLinePtr()->GetLastLine()->GetPointB() };

			for (const auto leaderLine : signalLinesVector)
			{
				auto line{ dynamic_cast<SignalLine*>(leaderLine) };

				while (line)
				{
					if (line != pSelectedSignalOutput->GetLinePtr()->GetLastLine())
					{
						D2D1_POINT_2F iteratingPoint{ dynamic_cast<SignalLine*>(line)->GetPointB() };

						if (pSelectedSignalOutput->GetLinePtr()->GetLastLine()->IsHorizontalDirection())
						{
							if (abs(selectedPoint.x - iteratingPoint.x) < abs(alignedX - selectedPoint.x))
							{
								alignedX = iteratingPoint.x;
							}
						}
						else
						{
							if (abs(selectedPoint.y - iteratingPoint.y) < abs(alignedY - selectedPoint.y))
							{
								alignedY = iteratingPoint.y;
							}
						}
					}

					line = line->GetLinkedLine();
				}	
			}

			if (pSelectedSignalOutput->GetLinePtr()->GetLastLine()->IsHorizontalDirection())
			{
				if (abs(alignedX - changeX) <= signalLineAlignmentLimit)
					changeX = alignedX;			
			}
			else if (abs(alignedY - changeY) <= signalLineAlignmentLimit)
			{
				changeY = alignedY;
				OutputDebugString(L"ALINHOU");
			}
				
				
		}

		pSelectedSignalOutput->GetLinePtr()->ChangePointB(
			D2D1::Point2F(
				static_cast<float>(changeX),
				static_cast<float>(changeY)
			)
		);

		if (keyboard.GetKeyStatus(Keyboard::Code::VK_D) == Keyboard::KeyStatus::PRESSED)
		{
			pSelectedSignalOutput->GetLinePtr()->CreateLinkLine();
		}
	}
}