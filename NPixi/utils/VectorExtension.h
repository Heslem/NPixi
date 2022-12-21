#pragma once

#include "../sfml.h"
#include "MathUtils.h"

namespace sf {
	static sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, const float& t) {
		float clampedT = math::clamp01(t);
		return sf::Vector2f(
			a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t
		);
	}
}