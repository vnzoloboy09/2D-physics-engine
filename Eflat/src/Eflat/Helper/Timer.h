#pragma once

#include <chrono>

namespace Eflat {

	class Timer
	{
	public:
		Timer();
		~Timer();

		float GetDurationNow();

	public:
		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::duration<float> duration;
	};

}


