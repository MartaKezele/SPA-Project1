#pragma once
#include<iostream>
using namespace std;
class VideoGame
{
public:

	// KONSTRUKTORI

	VideoGame();
	VideoGame(string name, int year, string publisher, double Global_sales);
	VideoGame(int rank, string name, string platform, int year, string genre, string publisher,
		double NA_sales, double EU_sales, double JP_sales, double Other_sales, double Global_sales);

	// GETTERI

	int get_rank();
	string get_name();
	string get_platform();
	int get_year();
	string get_genre();
	string get_publisher();
	double get_NA_sales();
	double get_EU_sales();
	double get_JP_sales();
	double get_Other_sales();
	double get_Global_sales();

	// SETTERI

	void set_rank(int rank);
	void set_name(string name);
	void set_platform(string platform);
	void set_year(int year);
	void set_genre(string genre);
	void set_publisher(string publisher);
	void set_NA_sales(double NA_sales);
	void set_EU_sales(double EU_sales);
	void set_JP_sales(double JP_sales);
	void set_Other_sales(double Other_sales);
	void set_Global_sales(double Global_sales);

	// NAJVAŽNIJI PODACI ZA ISPIS U STRING

	string to_string();

private:
	int rank;
	string name;
	string platform;
	int year;
	string genre;
	string publisher;
	double NA_sales;
	double EU_sales;
	double JP_sales;
	double Other_sales;
	double Global_sales;

};


