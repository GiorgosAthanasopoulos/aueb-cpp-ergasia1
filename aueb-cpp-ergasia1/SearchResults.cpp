#include "SearchResults.h"

SearchResults::SearchResults(float x, float y, float w, float h, std::list<std::shared_ptr<Card>> children) : WidgetGroup(x, y, w, h, std::list<std::shared_ptr<Widget>>())
{
	for (std::list<std::shared_ptr<Card>>::iterator it = children.begin(); it != children.end(); ++it)
	{
		Card card = (**it);
		cards.push_back(std::shared_ptr<Card>(new Card(card.getX(), card.getY(), CARD_WIDTH, CARD_HEIGHT, card.getMovie(), card.getBrush(), card.getOnclick())));
	}

	init();
}

void SearchResults::init()
{
	title = "";
	producers = "";
	actors = "";
	genres = "";
	minYear = -5000;
	maxYear = 5000;
	maxResults = 8;
	results = 0;
	activeCards = {};

	textboxes.push_back(std::shared_ptr<TextBox>(new TextBox(180 + 350 * 0, 66 + 50, 300, 50, "Title")));
	textboxes.push_back(std::shared_ptr<TextBox>(new TextBox(180 + 350 * 1, 66 + 50, 300, 50, "Producers")));
	textboxes.push_back(std::shared_ptr<TextBox>(new TextBox(180 + 350 * 2, 66 + 50, 300, 50, "Actors")));
	textboxes.push_back(std::shared_ptr<TextBox>(new TextBox(180 + 350 * 3, 66 + 50, 300, 50, "Genres")));
	numboxes.push_back(std::shared_ptr<NumBox>(new NumBox(180 + 350 * 0, 66 + 50 + 75, 300, 50, "Min Year", "1900")));
	numboxes.push_back(std::shared_ptr<NumBox>(new NumBox(180 + 350 * 1, 66 + 50 + 75, 300, 50, "Max Year", "2025")));
}

void SearchResults::draw()
{
	if (active)
	{
		updateFilters();

		for (std::list<std::shared_ptr<Card>>::iterator it = activeCards.begin(); it != activeCards.end(); ++it)
			if ((*it)->isActive())
				(*it)->draw();

		for (std::list<std::shared_ptr<TextBox>>::iterator it = textboxes.begin(); it != textboxes.end(); ++it)
			if ((*it)->isActive())
				(*it)->draw();

		for (std::list<std::shared_ptr<NumBox>>::iterator it = numboxes.begin(); it != numboxes.end(); ++it)
			if ((*it)->isActive())
				(*it)->draw();
	}
}

void SearchResults::update()
{
	if (active)
	{
		updateFilters();

		for (std::list<std::shared_ptr<Card>>::iterator it = activeCards.begin(); it != activeCards.end(); ++it)
			if ((*it)->isActive())
				(*it)->update();

		for (std::list<std::shared_ptr<TextBox>>::iterator it = textboxes.begin(); it != textboxes.end(); ++it)
			if ((*it)->isActive())
				(*it)->update();
		
		for (std::list<std::shared_ptr<NumBox>>::iterator it = numboxes.begin(); it != numboxes.end(); ++it)
			if ((*it)->isActive())
				(*it)->update();
	}
}

bool SearchResults::checksFilters(Movie movie)
{
	std::string name = movie.getName();
	toLowerCase(&name);
	if (name.find(title) == std::string::npos || name == "" || name == " ")
		return false;

	std::string producers = movie.getProducers();
	toLowerCase(&producers);
	if (producers.find(this->producers) == std::string::npos || producers == "" || producers == " ")
		return false;

	std::string actors = movie.getActors();
	toLowerCase(&actors);
	if (actors.find(this->actors) == std::string::npos || actors == "" || actors == " ")
		return false;

	std::string genres = movie.getGenres();
	toLowerCase(&genres);
	if (genres.find(this->genres) == std::string::npos || genres == "" || genres == " ")
		return false;

	if (movie.getYear() < minYear || movie.getYear() > maxYear)
		return false;

	return true;
}

void SearchResults::resetResults()
{
	activeCards.clear();
	results = 0;

	float x = 300;
	float y = 66 + 300;

	for (std::list<std::shared_ptr<Card>>::iterator it = cards.begin(); it != cards.end(); ++it)
		if ((*it)->isActive() && results < maxResults && checksFilters((**it).getMovie()))
		{
			(**it).setX(x);
			(**it).setY(y);
			x += CARD_WIDTH + CARD_OFFSET_X;
			if (results == 3)
			{
				x = 300;
				y = 66 + 300 + CARD_HEIGHT + CARD_OFFSET_Y;
			}
			activeCards.push_back(*it);
			results++;
		}
}

void SearchResults::updateFilters()
{
	int counter = 0;

	for (std::list<std::shared_ptr<TextBox>>::iterator it = textboxes.begin(); it != textboxes.end(); ++it)
		if ((*it)->isActive())
		{
			if (counter == 0)
			{
				title = (**it).getText();
				toLowerCase(&title);
			}
			else if (counter == 1)
			{
				producers = (**it).getText();
				toLowerCase(&producers);
			}
			else if (counter == 2)
			{
				actors = (**it).getText();
				toLowerCase(&actors);
			}
			else if (counter == 3)
			{
				genres = (**it).getText();
				toLowerCase(&genres);
			}

			counter++;
		}

	counter = 0;

	for (std::list<std::shared_ptr<NumBox>>::iterator it = numboxes.begin(); it != numboxes.end(); ++it)
		if ((*it)->isActive())
		{
			if (counter == 0)
				minYear = std::stoi((**it).getText());
			else
				maxYear = std::stoi((**it).getText());

				counter++;
		}

	resetResults();
}
