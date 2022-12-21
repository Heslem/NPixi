#include "MultiplayerState.h"


#include "../imgui/imgui.h"
#include "../imgui/imgui-sfml.h"

#include "../Core.h"
#include <iostream>
#include "World.h"
#include "ServerState.h"

MultiplayerState::MultiplayerState()
	: IState("multiplayer"), open(true)
{
	const auto address = sf::IpAddress::getLocalAddress().toString();
	m_IpTextBuffer = new char[16];
	for (size_t i = 0; i < 16; ++i)
	{
		if (i < address.size()) {
			m_IpTextBuffer[i] = address[i];
		}
		else {
			m_IpTextBuffer[i] = '\0';
		}
	}
}

MultiplayerState::~MultiplayerState()
{
}

void MultiplayerState::update()
{
}

void MultiplayerState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void MultiplayerState::renderImGui()
{
	const sf::Vector2f windowSize = Core::getInstance().getWindowSize();
	ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2, windowSize.y / 2));
	ImGui::Begin("Multiplayer", &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

	if (ImGui::Button("Connect")) {
		World* serverWorld = new World(true);

		Core::getInstance().getStateManager().addState(serverWorld);
		Core::getInstance().getStateManager().setCurrentState("world");
		\


	}
	if (ImGui::Button("Host game")) {
		World* world = new World();

		Core::getInstance().getStateManager().addState(world);
		Core::getInstance().getStateManager().setCurrentState("world");
		
	}

	ImGui::InputText("IP", m_IpTextBuffer, 16);
	ImGui::End();
}
