#pragma once

#include <string>

class Movie
{
protected:
	int year;
	std::string producers, actors, genres, description, name, filenameBanner, filenameCard, longDescription, url;

public:
	Movie(std::string name, std::string description, int year, std::string producers, std::string actors, std::string genres, std::string filenameBanner, std::string filenameCard, std::string longDescription, std::string url);
	Movie();

	std::string getName();
	std::string getDescription();
	std::string getFilenameBanner();
	std::string getFilenameCard();
	int getYear();
	std::string getProducers();
	std::string getActors();
	std::string getGenres();
	std::string getLongDescription();
	std::string getUrl();
};
