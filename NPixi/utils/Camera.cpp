#include "Camera.h"

#include "VectorExtension.h"

Camera::Camera(const sf::Vector2f& center, const sf::Vector2f& size)
	: m_View(center, size)
{
}

Camera::~Camera()
{
}

void Camera::bind(sf::Transformable& target)
{
	m_Target = &target;
	m_IsTarget = true;
}

void Camera::unbind()
{
	m_IsTarget = false;
}

void Camera::update()
{
	if (m_IsTarget) {
		const sf::Vector2f& posEnd = m_Target->getPosition();

		m_View.setCenter(sf::lerp(m_View.getCenter(), posEnd, damping));
	}
}

void Camera::zoom(const sf::Event::MouseWheelScrollEvent& event)
{
	if (event.delta < -0.01f) {
		m_View.zoom(1.05f);
	}
	else if (event.delta > 0.01f) {
		m_View.zoom(0.95f);
	}
}

sf::View& Camera::getView()
{
	return m_View;
}
