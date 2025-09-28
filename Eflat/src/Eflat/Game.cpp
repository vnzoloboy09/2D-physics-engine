#include "efpch.h"
#include "Game.h"

#include "Math/Vector2D.h"
#include "Math/Converter.h"

#include "Eflat/Helper/Timer.h"
#include "Eflat/Helper/Random.h"

#include "Entity/RigidBody.h"

#include "Renderer.h"

#include "raymath.h"

namespace Eflat
{

	Eflat::Game::Game()
	{
		srand((uint32_t)time(nullptr));
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
		SetConfigFlags(FLAG_VSYNC_HINT);
		const int screenWidth = 1280;
		const int screenHeight = 720;
		InitWindow(screenWidth, screenHeight, "2D Physics Engine - Eflat");

		SetTargetFPS(60);

		m_Camera.target = { 2,  2 };
		m_Camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
		m_Camera.rotation = 0.0f;
		m_Camera.zoom = 20.0f;

		m_minCam = GetScreenToWorld2D({ 0, 0 }, m_Camera);
		m_maxCam = GetScreenToWorld2D({ screenWidth, screenHeight }, m_Camera);

		float paddingX = (m_maxCam.y - m_minCam.y) * 0.1f;

		if (!m_World.AddBox({2.0f, 14.0f}, m_maxCam.x - m_minCam.x - paddingX * 2, 3.0f, 0.8f, true, 0.5f))
		{
			TraceLog(LOG_ERROR, "Invalid Entity");
		}
		m_World.GetEntityList()[0].SetColor(GRAY);

		if (!m_World.AddCircle({ 20.0f, 50.0f }, 6.0f, 0.8f, true, 0.5f))
		{
			TraceLog(LOG_ERROR, "Invalid Entity");
		}

		m_SampleTimer = std::chrono::high_resolution_clock::now();
	}

	Eflat::Game::~Game()
	{

	}

	void Eflat::Game::Run()
	{
		while (!WindowShouldClose())
		{
			Update(GetFrameTime());
			Render();
		}
	}

	void Eflat::Game::Update(float dt)
	{
		UpdateCamera();
		HandleMouseInput();
	
		auto st = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> elapsed = st - m_SampleTimer;

		if (elapsed.count() > 1)
		{
			m_EntityNumString = "Body count: " + std::to_string(m_TotalEntityNum / m_TotalSampleCount);
			m_StepTimeString = "Step time: " + std::to_string(std::round(m_TotalWorldStepTime / m_TotalSampleCount * 10000.0) / 10000.0);

			m_TotalWorldStepTime = 0;
			m_TotalEntityNum = 0;
			m_TotalSampleCount = 0;
			m_SampleTimer = std::chrono::high_resolution_clock::now();
		}

		m_World.Step(dt);

		auto ed = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> duration = ed - st;

		m_TotalWorldStepTime += duration.count();
		m_TotalEntityNum += m_World.GetNumEntities();
		m_TotalSampleCount++;
	}

	void Eflat::Game::Render()
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText(m_EntityNumString.c_str(), 20, 10, 20, BLACK);
		DrawText(m_StepTimeString.c_str(), 20, 30, 20, BLACK);
		BeginMode2D(m_Camera);

		std::vector<Entity>& entities = m_World.GetEntityList();
		for (auto& e : entities)
		{
			Renderer::Render(e);
		}

		EndMode2D();
		EndDrawing();
	}

	void Game::HandleMouseInput()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 pos = GetScreenToWorld2D(GetMousePosition(), m_Camera);
			float width = Random::Float(2.0f, 3.5f);
			float height = Random::Float(2.0f, 3.5f);

			if (!m_World.AddBox(Converter::ToVector2D(pos), width, height, 0.8f, false, 0.5f))
			{
				TraceLog(LOG_ERROR, "Invalid Entity");
			}
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 pos = GetScreenToWorld2D(GetMousePosition(), m_Camera);
			float radius = Random::Float(0.5f, 2.0f);

			if(!m_World.AddCircle(Converter::ToVector2D(pos), radius, 0.8f, false, 0.5f))
			{
				TraceLog(LOG_ERROR, "Invalid Entity");
			}
		}

		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), m_Camera);

			m_Camera.offset = GetMousePosition();
			m_Camera.target = mouseWorldPos;

			float scale = 0.2f * wheel;
			m_Camera.zoom = Clamp(expf(logf(m_Camera.zoom) + scale), 0.125f, 64.0f);
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / m_Camera.zoom);
			m_Camera.target = Vector2Add(m_Camera.target, delta);
		}
	}

	void Game::UpdateCamera()
	{
		m_minCam = GetScreenToWorld2D({ 0, 0 }, m_Camera);
		m_maxCam = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight()}, m_Camera);
	}

}

