#include "Movie.h"

Movie::Movie(std::string name, std::string description, int year, std::string producers, std::string actors, std::string genres, std::string filenameBanner, std::string filenameCard, std::string longDescription, std::string url)
{
	this->name = name;
	this->year = year;
	this->producers = producers;
	this->actors = actors;
	this->genres = genres;
	this->filenameBanner = filenameBanner;
	this->filenameCard = filenameCard;
	this->description = description;
	this->longDescription = longDescription;
	this->url = url;
}

Movie::Movie()
{
	this->name = "";
	this->year = 0;
	this->producers = "";
	this->actors = "";
	this->genres = "";
	this->filenameBanner = "";
	this->filenameCard = "";
	this->description = "";
}

std::string Movie::getName()
{
	return name;
}

std::string Movie::getDescription()
{
	return description;
}

std::string Movie::getFilenameBanner()
{
	return filenameBanner;
}

std::string Movie::getFilenameCard()
{
	return filenameCard;
}

int Movie::getYear()
{
	return year;
}

std::string Movie::getProducers()
{
	return producers;
}

std::string Movie::getActors()
{
	return actors;
}

std::string Movie::getGenres()
{
	return genres;
}

std::string Movie::getLongDescription()
{
	return longDescription;
}

std::string Movie::getUrl()
{
	return url;
}
