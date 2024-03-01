#include "Utils.h"

#include <algorithm>
#include <cctype>
#include <string>

/*
splitDescription and splitActors take a movie's description and actors list accordingly and return a multiline string in the form of a 
string list so that big movie descriptions can fit in the window
*/

std::list<std::string> splitDescription(std::string description)
{
	std::list<std::string> res;
	res.push_back("");
	int charCount = 0;

	for (int i = 0; i < description.length(); ++i)
	{
		if (description[i] == ' ' && charCount > 90)
		{
			res.push_back("");
			charCount = 0;
		}
		res.back() += description[i];
		charCount++;
	}

	return res;
}

std::list<std::string> splitActors(std::string actors)
{
	std::list<std::string> res;
	res.push_back("");
	int charCount = 0;
	bool flag = false;

	for (int i = 0; i < actors.length(); ++i)
	{
		if (flag)
		{
			res.push_back("");
			charCount = 0;
			flag = false;
		}
		if (actors[i] == ',' && charCount > 90)
			flag = true;
		res.back() += actors[i];
		charCount++;
	}

	return res;
}

void open(std::string cmd)
{
	system(("start " + cmd).c_str());
}

std::shared_ptr<Button> getButtonFromList(std::list<std::shared_ptr<Button>> list, int index)
{
	std::list<std::shared_ptr<Button>>::iterator it = list.begin();

	for (int i = 0; i < index; i++)
		it++;

	return *it;
}

void toLowerCase(std::string* input)
{
	std::transform(input->begin(), input->end(), input->begin(), [](unsigned char c) { return std::tolower(c); });
}