#pragma once

#include "Card.h"
#include "WidgetGroup.h"
#include "App.h"
#include "TextBox.h"
#include "Utils.h"
#include "NumBox.h"

#define CARD_OFFSET_X 100
#define CARD_OFFSET_Y 100

class SearchResults : public WidgetGroup
{
private:
	bool checksFilters(Movie movie);
protected:
	std::string title, producers, actors, genres;
	int minYear, maxYear, maxResults, results;
	std::list<std::shared_ptr<Card>> cards, activeCards;
	std::list<std::shared_ptr<TextBox>> textboxes;
	std::list<std::shared_ptr<NumBox>> numboxes;
public:
	SearchResults(float x, float y, float w, float h, std::list<std::shared_ptr<Card>> children);

	void init();
	void draw();
	void update();

	void resetResults();
	void updateFilters();
};
