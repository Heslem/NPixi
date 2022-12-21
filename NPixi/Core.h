#pragma once

#include "sfml.h"
#include "states/StateManager.h"
#include "utils/AssetsManager.h"
#include "utils/Camera.h"
#include "scripting/LuaBinding.h"

class Core sealed
{
public:
	Core(const Core&) = delete;
	~Core();

	void run();
	void dispose();
	void close();

	static Core& getInstance() {
		static Core core;
		return core;
	}

	StateManager& getStateManager();
	AssetsManager& getAssetsManager();
	Camera& getCamera();
	LuaBinding& getLuaBinding();

	sf::Vector2f getWindowSize() const;
	bool isFocus() const;

	void drawFloatRect(sf::RenderTarget& target, const sf::RenderStates& states, const sf::FloatRect& rect);
private:

	void update();
	void render();

	void pollEvents();

	Core();

	sf::RenderWindow* m_Window;
	StateManager* m_StateManager;
	AssetsManager* m_AssetsManager;
	Camera* m_Camera;
	LuaBinding* m_Lua;

	sf::Thread m_RenderThread;

	const float fps = 60.0f;
	const sf::Time oneFrame;
};

