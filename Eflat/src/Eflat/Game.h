#pragma once

#include "World.h"
#include <chrono>

namespace Eflat {

	class Game
	{
	public:
		Game();
		~Game();

		void Run();
		void Update(float dt);
		void Render();

		void HandleMouseInput();

		void UpdateCamera();

	private:
		Camera2D m_Camera = { 0 };
		Vector2 m_minCam, m_maxCam;

		World m_World;

		std::string m_EntityNumString;
		std::string m_StepTimeString;

		size_t m_TotalEntityNum = 0;
		size_t m_TotalSampleCount = 0;
		float m_TotalWorldStepTime = 0.0f;
		std::chrono::time_point<std::chrono::steady_clock> m_SampleTimer;
	};

}