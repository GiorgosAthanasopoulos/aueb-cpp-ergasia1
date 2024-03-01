#pragma once

#include "Widget.h"
#include "Movie.h"
#include "graphics.h"
#include "App.h"
#include "SceneState.h"

#define SCROLLVIEW_TEXT_OFFSETX 150
#define SCROLLVIEW_TEXT_OFFSETY 66

#define GENRES_FONT_SIZE 20
#define DESCRIPTION_FONT_SIZE 25
#define TITLE_FONT_SIZE 30

#define IMAGE_WIDTH 1024
#define IMAGE_HEIGHT 512

class View : public Widget
{
protected:
	Movie movie;
	graphics::Brush br;

	App* app;
	SceneState scene;
public:
	View(float x, float y, float w, float h, Movie movie, graphics::Brush br, App* const app, SceneState scene);

	void init();
	void draw();
	void update();
};
