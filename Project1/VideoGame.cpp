#include "VideoGame.h"
#include<sstream>

// KONSTRUKTORI

VideoGame::VideoGame()
{
}

VideoGame::VideoGame(string name, int year, string publisher, double Global_sales)
{
	set_name(name);
	set_year(year);
	set_publisher(publisher);
	set_Global_sales(Global_sales);
}

VideoGame::VideoGame(int rank, string name, string platform, int year, string genre, string publisher, double NA_sales, double EU_sales, double JP_sales, double Other_sales, double Global_sales)
{
	set_rank(rank);
	set_name(name);
	set_platform(platform);
	set_year(year);
	set_genre(genre);
	set_publisher(publisher);
	set_NA_sales(NA_sales);
	set_EU_sales(EU_sales);
	set_JP_sales(JP_sales);
	set_Other_sales(Other_sales);
	set_Global_sales(Global_sales);
}

// GETTERI

int VideoGame::get_rank()
{
	return rank;
}

string VideoGame::get_name()
{
	return name;
}

string VideoGame::get_platform()
{
	return platform;
}

int VideoGame::get_year()
{
	return year;
}

string VideoGame::get_genre()
{
	return genre;
}

string VideoGame::get_publisher()
{
	return publisher;
}

double VideoGame::get_NA_sales()
{
	return NA_sales;
}

double VideoGame::get_EU_sales()
{
	return EU_sales;
}

double VideoGame::get_JP_sales()
{
	return JP_sales;
}

double VideoGame::get_Other_sales()
{
	return Other_sales;
}

double VideoGame::get_Global_sales()
{
	return Global_sales;
}

// SETTERI

void VideoGame::set_rank(int rank)
{
	this->rank = rank;
}

void VideoGame::set_name(string name)
{
	this->name = name;
}

void VideoGame::set_platform(string platform)
{
	this->platform = platform;
}

void VideoGame::set_year(int year)
{
	this->year = year;
}

void VideoGame::set_genre(string genre)
{
	this->genre = genre;
}

void VideoGame::set_publisher(string publisher)
{
	this->publisher = publisher;
}

void VideoGame::set_NA_sales(double NA_sales)
{
	this->NA_sales = NA_sales;
}

void VideoGame::set_EU_sales(double EU_sales)
{
	this->EU_sales = EU_sales;
}

void VideoGame::set_JP_sales(double JP_sales)
{
	this->JP_sales = JP_sales;
}

void VideoGame::set_Other_sales(double Other_sales)
{
	this->Other_sales = Other_sales;
}

void VideoGame::set_Global_sales(double Global_sales)
{
	this->Global_sales = Global_sales;
}

// NAJVAŽNIJI PODACI ZA ISPIS U STRING

string VideoGame::to_string()
{
	stringstream ss;

	ss << "NAME: " << name << ", ";
	ss << "YEAR: " << year << ", ";
	ss << "PUBLISHER: " << publisher << ", ";
	ss << "GLOBAL SALES: " << Global_sales;

	return ss.str();
}
