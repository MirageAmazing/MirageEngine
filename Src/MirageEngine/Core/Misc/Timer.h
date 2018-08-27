#pragma once
#include <chrono>
#include "../Core.h"

using namespace std;
using namespace chrono;

namespace Mirage {
	namespace Misc {
		/// <summary>
		/// Get nowtime with microseconds.
		/// </summary>
		#define GetNowTimeForMicroSeconds() duration_cast<microseconds>(chrono::steady_clock::now().time_since_epoch())

		/// <summary>
		/// The interface of Timer.
		/// </summary>
		class ITimer {
		public:
			virtual float GetDeltaTime() const = 0;
			virtual uint64_t GetFrames() const = 0;
			virtual float GetAvergerFramerate() const = 0;
			virtual float GetLatestFramerate() const = 0;
			virtual float GetIdleTime() const = 0;
			virtual float GetBusynessTime() const = 0;
			virtual bool IsPause() const = 0;
		};

		/// <summary>
		/// Timer.
		/// </summary>
		class Timer : public ITimer {
		public:
			Timer();
			~Timer();

			void Tick();

			void Pause();

			void Start();

			MEINLINE virtual float GetDeltaTime() const override {
				return deltaTime.count() * 0.000001f;
			}

			MEINLINE virtual uint64_t GetFrames() const override {
				return frames;
			}

			MEINLINE virtual float GetAvergerFramerate() const override {
				return avergerframerate;
			}

			MEINLINE virtual float GetLatestFramerate() const override {
				return currentframerate;
			}

			MEINLINE virtual float GetIdleTime() const override {
				return idletime.count() * 0.000001f;
			}

			MEINLINE virtual float GetBusynessTime() const override {
				return busynesstime.count() * 0.000001f;
			}

			MEINLINE virtual bool IsPause() const override {
				return isPause;
			}

		private:

			microseconds timepoint = microseconds(0);
			uint64_t frames = 0;
			float avergerframerate = 0;
			float currentframerate = 0;
			microseconds deltaTime = microseconds(0);

			bool isPause = true;
			bool firstStart = true;

			microseconds pausetimepoint = microseconds(0);
			microseconds starttimepoint = microseconds(0);
			microseconds busynesstime = microseconds(0);
			microseconds idletime = microseconds(0);
		};
	}
}