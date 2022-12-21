#pragma once

#include "../sfml.h"

class Camera {
public:

	Camera(const sf::Vector2f& center, const sf::Vector2f& size);
	~Camera();
	Camera(const Camera&) = delete;

	void bind(sf::Transformable& target);
	void unbind();

	void update();
	void zoom(const sf::Event::MouseWheelScrollEvent& event);

	sf::View& getView();

private:
	sf::View m_View;
	sf::Transformable* m_Target;
	bool m_IsTarget;
	const float damping = 0.05f;
};