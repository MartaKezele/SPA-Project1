#include "Igra.h"
#include<sstream>

Igra::Igra()
{
}

Igra::Igra(string naziv, string platforma)
{
	this->naziv = naziv;
	platforme.push_back(platforma);
}

void Igra::add_platforma(string platforma)
{
	platforme.push_back(platforma);
}

string Igra::get_naziv()
{
	return naziv;
}

int Igra::get_size()
{
	return platforme.size();
}

string Igra::to_string()
{
	abecedni_sort_platforme();
	stringstream ss;
	ss << "NAZIV: " << naziv << ", PLATFORME: (";

	for (int i = 0; i < platforme.size(); i++) {

		if (i == platforme.size() - 1) ss << platforme[i] << ")";
		else ss << platforme[i] << ", ";

	}

	return ss.str();
}

void Igra::abecedni_sort_platforme()
{
	for (int i = 0; i < platforme.size(); i++) {
		for (int j = i + 1; j < platforme.size(); j++) {

			if (!dobar_redoslijed(platforme[i], platforme[j])) {

				string temp = platforme[i];
				platforme[i] = platforme[j];
				platforme[j] = temp;

			}

		}
	}
}

bool Igra::dobar_redoslijed(string a, string b)
{
	int min = a.length();
	int flag = 0;
	if (b.length() < a.length()) {
		min = b.length();
		flag = 1;
	}

	for (int i = 0; i < min; i++) {

		if (a[i] < b[i]) {
			return true;
		}
		else if (a[i] > b[i]) {
			return false;
		}
	}

	if (flag == 0) return true;
	else return false;
}
