#include "Menu.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui-sfml.h"

#include "../Core.h"
#include "World.h"
#include "MultiplayerState.h"

constexpr float BUTTON_SIZE_X = 90;
constexpr float BUTTON_SIZE_Y = 25;
constexpr ImVec2 BUTTON_SIZE = ImVec2(BUTTON_SIZE_X, BUTTON_SIZE_Y);


Menu::Menu()
	: IState("menu"), open(true)
{
	m_Background.setSize((sf::Vector2f)Core::getInstance().getAssetsManager().Textures["menu_background"]->getSize());
	m_Background.setTexture(Core::getInstance().getAssetsManager().Textures["menu_background"]);

	m_Background.setOrigin(1920.0f / 2.0f, 1080.0f / 2.0f);
	m_Background.setPosition(sf::Vector2f(0, 0));
}

Menu::~Menu()
{
}

void Menu::update()
{
	//m_Background.setSize(Core::getInstance().getWindowSize());
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Background, states);
}

void Menu::renderImGui()
{
	const sf::Vector2f windowSize = Core::getInstance().getWindowSize();
	ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2, windowSize.y / 2));
	ImGui::Begin("Menu", &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

	if (ImGui::Button("Play", BUTTON_SIZE)) {
		auto& stateManager = Core::getInstance().getStateManager();
		stateManager.addState(new World());
		stateManager.setCurrentState("world");
	}
	if (ImGui::Button("Multiplayer")) {
		auto& stateManager = Core::getInstance().getStateManager();
		stateManager.addState(new MultiplayerState());
		stateManager.setCurrentState("multiplayer");
	}

	
	if (ImGui::Button("Close", BUTTON_SIZE)) {
		Core::getInstance().close();
	}

	ImGui::Text("Created by Hesles and Chelilleit.");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::Text("Hello player!\n We are developers of that game. We glad see you here.");
		ImGui::Text(u8"Русский язык!");
		ImGui::EndTooltip();
	}
	ImGui::SameLine();
	ImGui::Image(*Core::getInstance().getAssetsManager().Textures["player"]);

	ImGui::End();
}
