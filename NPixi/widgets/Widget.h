#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui-sfml.h"

class Widget {
public:
	Widget();
	virtual ~Widget();

	virtual void render() = 0;
};