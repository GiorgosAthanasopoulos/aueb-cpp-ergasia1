#pragma once

#include "Widget.h"
#include "graphics.h"
#include "scancodes.h"

#include <map>

#define TEXT_OFFSET 5
#define HINT_OFFSET 10

class TextBox : public Widget {
private:
	static const int MAX_LINE_SIZE = 22;
	const std::map<graphics::scancode_t, std::string> codes{
		 {graphics::SCANCODE_A, "a"},
		 {graphics::SCANCODE_B, "b"},
		 {graphics::SCANCODE_C, "c"},
		 {graphics::SCANCODE_D, "d"},
		 {graphics::SCANCODE_E, "e"},
		 {graphics::SCANCODE_F, "f"},
		 {graphics::SCANCODE_G, "g"},
		 {graphics::SCANCODE_H, "h"},
		 {graphics::SCANCODE_I, "i"},
		 {graphics::SCANCODE_J, "j"},
		 {graphics::SCANCODE_K, "k"},
		 {graphics::SCANCODE_L, "l"},
		 {graphics::SCANCODE_M, "m"},
		 {graphics::SCANCODE_N, "n"},
		 {graphics::SCANCODE_O, "o"},
		 {graphics::SCANCODE_P, "p"},
		 {graphics::SCANCODE_Q, "q"},
		 {graphics::SCANCODE_R, "r"},
		 {graphics::SCANCODE_S, "s"},
		 {graphics::SCANCODE_T, "t"},
		 {graphics::SCANCODE_U, "u"},
		 {graphics::SCANCODE_V, "v"},
		 {graphics::SCANCODE_W, "w"},
		 {graphics::SCANCODE_X, "x"},
		 {graphics::SCANCODE_Y, "y"},
		 {graphics::SCANCODE_Z, "z"},
	};
protected:
	graphics::Brush br, text_br;
	std::string text, hint;
	graphics::scancode_t lastCode;
	float lastTime;
public:
	TextBox(float  x, float  y, float  w, float  h, std::string hint);

	void init();
	void draw();
	void update();

	std::string getText();
};
