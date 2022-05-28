#include "Izdavac.h"
#include <iostream>
#include<string>
#include <string.h>
#include<stack>
#include<sstream>
using namespace std;

Izdavac::Izdavac()
{
}

Izdavac::Izdavac(string ime, double zarada)
{
    set_ime(ime);
    set_zarada(zarada);
}

string Izdavac::get_ime()
{
    return ime;
}

double Izdavac::get_zarada()
{
    return zarada;
}

void Izdavac::set_ime(string ime)
{
    this->ime = ime;
}

void Izdavac::set_zarada(double zarada)
{
    this->zarada = zarada;
}

string Izdavac::to_str()
{
    stringstream ss;
    ss << "NAZIV: " << ime << ", ZARADA: ";

    string s = to_string(zarada);
    string obrnuto(s.rbegin(), s.rend());

    stack<char> znamenke;
    bool flag = 0;
    int brojac = 0;

    for (int i = 4; i < obrnuto.length(); i++) {

        if (obrnuto[i] == '.') {
            flag = 1;
            znamenke.push(',');
        }
        else if (flag) {

            znamenke.push(obrnuto[i]);
            brojac++;
            if (brojac % 3 == 0 && i != obrnuto.length() - 1) {
                znamenke.push('.');
            }

        }
        else {
            znamenke.push(obrnuto[i]);
        }

    }

    while (!znamenke.empty()) {

        ss << znamenke.top();
        znamenke.pop();

    }

    ss << " USD";

    return ss.str();
}
