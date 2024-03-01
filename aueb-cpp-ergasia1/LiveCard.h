#pragma once

#include "WidgetGroup.h"
#include "graphics.h"

#include <string>

#define TITLE_OFFSET_Y 20

#define ICON_OFFSET_X 70
#define ICON_W 128
#define ICON_H 64

#define PERCENTAGE_BAR_OFFSET_Y 30
#define PERCENTAGE_BAR_H 5

#define AGE_OFFSET_X 10
#define AGE_OFFSET_Y 15
#define AGE_SIZE 10

#define PLAY_TEXT_OFFSET_X 5

class LiveCard : public WidgetGroup 
{
private:
	graphics::Brush play, icon;
protected:
	std::string time, title, age_restriction, filename, url, iconUrl;
	int percentage;
public:
	LiveCard(float x, float y, float w, float h, std::string time, std::string title, std::string age_restriction, int percentage, std::string filename, std::string url, std::string iconUrl);

	void init();
	void draw();
	void update();
};
