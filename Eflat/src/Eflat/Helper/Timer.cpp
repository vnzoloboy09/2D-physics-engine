#include "efpch.h"
#include "Timer.h"

namespace Eflat {

	Timer::Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
#ifdef DEBUG
		std::cout << "Timer took: " << ms << " ms\n";
#endif
	}

	float Timer::GetDurationNow()
	{
		std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::high_resolution_clock::now();
		duration = now - start;

		float ms = duration.count() * 1000.0f;
		return ms;
	}

}

