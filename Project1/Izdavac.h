#pragma once
#include<iostream>
using namespace std;
class Izdavac
{
public:
	Izdavac();
	Izdavac(string ime, double zarada);
	string get_ime();
	double get_zarada();
	void set_ime(string ime);
	void set_zarada(double zarada);
	string to_str();
private:
	string ime;
	double zarada;
};



