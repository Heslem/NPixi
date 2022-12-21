#pragma once

#include "../sfml.h"

namespace math {
	static float clamp01(const float& value) {
		if (value > 1.0f) {
			return 1.0f;
		}
		else if (value < 0.0f) {
			return 0.0f;
		}
		else {
			return value;
		}
		
	}

	inline float getDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
		return sqrtf(powf(b.x - a.x, 2.0f) + powf(b.y - a.y, 2.0f));
	}
}