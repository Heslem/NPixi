#include "Core.h"

#include "imgui/imgui.h"
#include "imgui/imgui-sfml.h"
#include <iostream>
#include "animation/SpriteSheet.h"


Core::~Core()
{
	
}

void Core::run()
{
	std::cout << "Initialize window." << std::endl;
	
	m_Window = new sf::RenderWindow(sf::VideoMode(1200, 720), "Pixi.", sf::Style::Default);
	m_Window->setFramerateLimit(60);
	m_Window->setActive(false);

	m_AssetsManager = new AssetsManager();
	std::cout << "Loading assets." << std::endl;
	m_AssetsManager->load();

	std::cout << "Loading states." << std::endl;
	m_StateManager = new StateManager();

	std::cout << "Create camera." << std::endl;
	m_Camera = new Camera(sf::Vector2f(0, 0), (sf::Vector2f)m_Window->getSize());

	std::cout << "Initialize Dear ImGui." << std::endl;
	ImGui::SFML::Init(*m_Window, false);
	ImGui::SFML::SetCurrentWindow(*m_Window);
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("content/fonts/font.ttf", 15, NULL, io.Fonts->GetGlyphRangesCyrillic())->Scale = 0.8f;
	ImGui::SFML::UpdateFontTexture();

	std::cout << "Load scripts." << std::endl;
	m_Lua = new LuaBinding();


	std::cout << "Launch render thread." << std::endl;
	m_RenderThread.launch();

	std::cout << "Launch update thread." << std::endl;
	update();
}

void Core::dispose()
{
	delete m_Window;
	delete m_StateManager;
	delete m_AssetsManager;
	delete m_Lua;
	ImGui::SFML::Shutdown();
}

void Core::close()
{
	m_Window->close();
}

StateManager& Core::getStateManager()
{
	return *m_StateManager;
}

AssetsManager& Core::getAssetsManager()
{
	return *m_AssetsManager;
}

Camera& Core::getCamera()
{
	return *m_Camera;
}

LuaBinding& Core::getLuaBinding()
{
	return *m_Lua;
}

sf::Vector2f Core::getWindowSize() const
{
	return (sf::Vector2f)m_Window->getSize();
}

bool Core::isFocus() const
{
	return m_Window->hasFocus();
}

void Core::drawFloatRect(sf::RenderTarget& target, const sf::RenderStates& states, const sf::FloatRect& rect)
{
	sf::RectangleShape s(sf::Vector2f(rect.width, rect.height));
	s.setPosition(sf::Vector2f(rect.left, rect.top));
	s.setOutlineColor(sf::Color::Red);
	s.setFillColor(sf::Color::Transparent);
	s.setOutlineThickness(16.0f);

	target.draw(s);
}

void Core::update()
{
	sf::Clock fixedClock;
	sf::Time elapsedTime;

	while (m_Window->isOpen()) {
		elapsedTime += fixedClock.restart();
		if (elapsedTime > oneFrame) {
			pollEvents();

			m_StateManager->update();
			m_Camera->update();

			elapsedTime -= oneFrame;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				close();
			}
		}
	}
	std::cout << "Update thread is finished." << std::endl;
}

void Core::render()
{
	m_Window->setActive();

	float fps;
	sf::Clock fpsClock;
	sf::Time previousTime = fpsClock.getElapsedTime();
	sf::Time currentTime;

	bool debug = true;

	sf::Clock imDelta; // TODO: delete it
	while (m_Window->isOpen()) {
		ImGui::SFML::Update(*m_Window, imDelta.restart());

		m_Window->clear();

		m_Window->setView(m_Camera->getView());

		m_Window->draw(*m_StateManager);

		m_StateManager->renderImGui();
		//ImGui::ShowDemoWindow();

		if (debug) {
			ImGui::Begin("State info", (bool*)1, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text(("State name: " + m_StateManager->getCurrentState().getNameString()).c_str());
			ImGui::End();

			ImGui::Begin("Lua editor", (bool*)1, ImGuiWindowFlags_AlwaysAutoResize);

			static char buf[512];

			ImGui::InputTextMultiline("Code", buf, 512);

			if (ImGui::Button("Run")) {
				m_Lua->doString(buf);
			}

			ImGui::End();
		}

		ImGui::SFML::Render(*m_Window);

		currentTime = fpsClock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
		previousTime = currentTime;

		m_Window->display();
	}
	std::cout << "Render thread is finished." << std::endl;
}

void Core::pollEvents()
{
	sf::Event event;
	while (m_Window->pollEvent(event)) {
		ImGui::SFML::ProcessEvent(*m_Window, event);
		if (event.type == sf::Event::EventType::Closed) {
			m_Window->close();
		}
		else if (event.type == sf::Event::EventType::Resized) {
			m_Window->setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f((float)event.size.width, (float)event.size.height)));
		}
		else if (event.type == sf::Event::EventType::MouseWheelScrolled) {
			m_Camera->zoom(event.mouseWheelScroll);
		}
	}
}

Core::Core() :
	m_RenderThread(&Core::render, this), oneFrame(sf::seconds(1.0f / 60.0f))
{
}
