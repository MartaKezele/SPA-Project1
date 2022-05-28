#pragma once
#include<vector>
#include<string>
using namespace std;
class Igra
{
public:
	Igra();
	Igra(string naziv, string platfroma);
	void add_platforma(string platforma);
	string get_naziv();
	int get_size();
	string to_string();
private:
	string naziv;
	vector<string> platforme;
	void abecedni_sort_platforme();
	bool dobar_redoslijed(string a, string b);

};


