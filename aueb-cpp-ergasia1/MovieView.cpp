#include "MovieView.h"
#include "graphics.h"
#include "Metrics.h"
#include "Image.h"
#include "Button.h"
#include "Utils.h"

MovieView::MovieView(float x, float y, float w, float h, Movie movie, std::string titleFgColor) : WidgetGroup(x, y, w, h, std::list<std::shared_ptr<Button>>())
{
	this->movie = movie;
	this->titleFgColor = titleFgColor;
	init();
}

void MovieView::init()
{
	// background
	banner.texture = movie.getFilenameBanner();
	banner.outline_opacity = 0;
	banner.gradient = true;
	banner.gradient_dir_u = 0;
	banner.gradient_dir_v = 1;
	banner.fill_secondary_opacity = 0;
	// card
	card.texture = movie.getFilenameCard();
	card.outline_opacity = 0;
	// title
	// genres
	// url
	button.outline_opacity = 0;
	button.fill_color[0] = 1;
	button.fill_color[1] = 0;
	button.fill_color[2] = .5f;
	hover.fill_color[0] = 1;
	hover.fill_color[1] = 0;
	hover.fill_color[2] = .5f;
	// description

	children.push_back(std::shared_ptr<Widget>(new Image(x, y, w, h, movie.getFilenameBanner(), banner)));
	children.push_back(std::shared_ptr<Widget>(new Image(x / 3 + CARD_OFFSETX, y - CARD_OFFSETY, CARD_WIDTH_MV / 2, CARD_HEIGHT_MV / 2, movie.getFilenameCard(), card)));
	children.push_back(std::shared_ptr<Widget>(new Button(x / 3 + BUTTON_OFFSETX, y - BUTTON_OFFSETY, BUTTON_WIDTH, BUTTON_HEIGHT, button, title, "Watch", WATCH_OFFSETX, WATCH_OFFSETY, hover, title,
		[&]()
		{
			open(movie.getUrl());
		},
	"", CLICK)));
}

void MovieView::draw()
{
	// with the parameter titleFgColor of MovieView::MovieView we can set the movie title foreground color so that the text is visible
	// even in white backgrounds
	if (titleFgColor == "black")
	{
		title.fill_color[0] = 0;
		title.fill_color[1] = 0;
		title.fill_color[2] = 0;
	}

	// draw title
	graphics::setFont(OPENSANSB);
	graphics::drawText(x / 3 + TITLE_OFFSETX, 66 + 50, 40, movie.getName(), title);

	// draw genres
	graphics::setFont(OPENSANSL);
	graphics::drawText(x / 3 + TITLE_OFFSETX, 66 + 80, 25, movie.getGenres(), title);

	title.fill_color[0] = 1;
	title.fill_color[1] = 1;
	title.fill_color[2] = 1;

	// draw actors text
	graphics::drawText(x / 3 + TITLE_OFFSETX, y - 132, 20, "Actors", title);
	graphics::setFont(OPENSANSB);
	std::list<std::string> _splitActors = splitActors(movie.getActors());
	// counter is for spacing purposes
	int counter = 0;
	for (std::list<std::string>::iterator it = _splitActors.begin(); it != _splitActors.end(); ++it)
	{
		// draw actors list
		graphics::drawText(x / 3 + TITLE_OFFSETX, y - 99 + 25 * counter, 20, (*it), title);
		counter++;
	}
	int offset = (counter - 1) * 25;
	graphics::setFont(OPENSANSL);
	// draw directors text
	graphics::drawText(x / 3 + TITLE_OFFSETX, y - 66 + offset, 20, "Directors", title);
	graphics::setFont(OPENSANSB);
	// draw directors
	graphics::drawText(x / 3 + TITLE_OFFSETX, y - 33 + offset, 20, movie.getProducers(), title);

	graphics::setFont(OPENSANS);
	// draw description list
	std::list<std::string> splitDescriptions = splitDescription(movie.getLongDescription());
	counter = 0;
	for (std::list<std::string>::iterator it = splitDescriptions.begin(); it != splitDescriptions.end(); ++it)
	{
		graphics::drawText(x / 3 + TITLE_OFFSETX, y + 25 * counter + offset, 18, (*it), title);
		counter++;
	}

	for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
		if ((*it)->isActive())
			(*it)->draw();
}

void MovieView::update()
{
	for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
		if ((*it)->isActive())
			(*it)->update();
}
