#pragma once
#include <random>

namespace nc {
	inline float random() {
		return rand() / static_cast<float>(RAND_MAX); //0 - rand max
	}

	inline float random(float min, float max) {
		if (min > max) {
			std::swap(min, max);
		}
		return min + ((max - min) * random());
	}
}