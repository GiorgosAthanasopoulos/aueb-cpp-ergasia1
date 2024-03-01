#include "View.h"
#include "graphics.h"
#include "Metrics.h"

View::View(float x, float y, float w, float h, Movie movie, graphics::Brush br, App* const app, SceneState scene) : Widget(x, y, w, h)
{
	this->movie = movie;
	this->br = br;
	this->app = app;
	this->scene = scene;
	init();
}

void View::init()
{
	br.outline_opacity = 0;
}

void View::draw()
{
	if (active)
	{
		br.texture = movie.getFilenameBanner();

		// draw movie card
		graphics::drawRect(x, y, w, h, br);
		graphics::setFont(OPENSANSL);
		// draw year, genres
		graphics::drawText(SCROLLVIEW_TEXT_OFFSETX, y + IMAGE_HEIGHT / 2 - SCROLLVIEW_TEXT_OFFSETY * 3, GENRES_FONT_SIZE, "* " + std::to_string(movie.getYear()) + " * " + movie.getGenres(), br);
		graphics::setFont(OPENSANSB);
		// draw title
		graphics::drawText(SCROLLVIEW_TEXT_OFFSETX, y + IMAGE_HEIGHT / 2 - SCROLLVIEW_TEXT_OFFSETY * 2, TITLE_FONT_SIZE, movie.getName(), br);
		graphics::setFont(OPENSANS);
		// draw description
		graphics::drawText(SCROLLVIEW_TEXT_OFFSETX, y + IMAGE_HEIGHT / 2 - SCROLLVIEW_TEXT_OFFSETY * 1, DESCRIPTION_FONT_SIZE, movie.getDescription(), br);
	}
}

void View::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float cur_x = graphics::windowToCanvasX((float) ms.cur_pos_x);
	float cur_y = graphics::windowToCanvasY((float) ms.cur_pos_y);

	if (cur_x <= x + w / 2 && cur_x >= x - w / 2 && cur_y <= y + h / 2 && cur_y >= y - h / 2)
		if (ms.button_left_pressed)
			app->setScene(scene);
}
