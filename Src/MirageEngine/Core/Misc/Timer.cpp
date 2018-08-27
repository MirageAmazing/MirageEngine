#include "Timer.h"

namespace Mirage {
	namespace Misc {
		Timer::Timer() {
			timepoint = GetNowTimeForMicroSeconds();
			pausetimepoint = timepoint;
			Start();
		}
		Timer::~Timer() { }

		void Timer::Tick() {
			if (isPause)
				return;
			frames++;
			microseconds time = GetNowTimeForMicroSeconds();
			if (!firstStart) {
				deltaTime = time - timepoint;
				currentframerate = 1000000.0f / ((float)deltaTime.count());
				avergerframerate = (avergerframerate + currentframerate) * 0.5f;
			}
			else {
				firstStart = false;
			}
			timepoint = time;
		}

		void Timer::Pause() {
			if (!isPause) {
				isPause = true;
				pausetimepoint = GetNowTimeForMicroSeconds();

				busynesstime += (pausetimepoint - starttimepoint);
			}
		}

		void Timer::Start() {
			if (isPause) {
				starttimepoint = GetNowTimeForMicroSeconds();
				isPause = false;
				firstStart = true;

				idletime += (starttimepoint - pausetimepoint);
			}
		}
	}
}