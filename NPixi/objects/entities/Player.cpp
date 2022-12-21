#include "Player.h"
#include "../../Core.h"

#include "../../states/World.h"

Player::Player(const bool& controlled)
	: Entity(PLAYER), m_Controlled(controlled), m_World(*dynamic_cast<World*>(&Core::getInstance().getStateManager().getCurrentState()))
{
	setSize(sf::Vector2f(40, 40));
	setTexture(Core::getInstance().getAssetsManager().Textures["player"]);
	setSpeed(5.0f);
}

Player::~Player()
{
}
void Player::update()
{
	if (m_Controlled && Core::getInstance().isFocus()) {
		float x = 0, y = 0;
		bool c = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			x = -1;
			c = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			x = 1;
			c = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			y = -1;
			c = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			y = 1;
			c = true;
		}

		if (c)
		{
			entityMove(x, y);
		}

		//auto objects = m_World.getCollisisionWithGameObject(this);
		//auto collis = getCollision();

		//static sf::Sound Sound;
		/*for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects[i]->getGameObject().getPosition() != getPosition() && objects[i]->getCollision().intersects(collis)) {
				
			}
		}*/
	}
}
