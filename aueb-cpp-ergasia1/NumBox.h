#pragma once

#include "Widget.h"
#include "graphics.h"

#include <string>
#include <map>

#define TEXT_OFFSET 5
#define HINT_OFFSET 10

class NumBox : public Widget
{
private:
	static const int MAX_SIZE = 4;
	std::map<graphics::scancode_t, std::string> codes{
		{graphics::SCANCODE_1, "1"},
		{graphics::SCANCODE_2, "2"},
		{graphics::SCANCODE_3, "3"},
		{graphics::SCANCODE_4, "4"},
		{graphics::SCANCODE_5, "5"},
		{graphics::SCANCODE_6, "6"},
		{graphics::SCANCODE_7, "7"},
		{graphics::SCANCODE_8, "8"},
		{graphics::SCANCODE_9, "9"},
		{graphics::SCANCODE_0, "0"},
	};
protected:
	graphics::Brush br, br_txt;
	std::string hint, txt;
	graphics::scancode_t lastCode;
	float lastTime;
public:
	NumBox(float x, float y, float w, float h, std::string hint, std::string defaultValue);

	void init();
	void draw();
	void update();

	std::string getText();
};
