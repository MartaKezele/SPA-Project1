#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<chrono>
#include<sstream>
#include<list>
#include<algorithm>
#include<queue>
#include<stack>
#include"VideoGame.h"
#include"Izdavac.h"
#include"Igra.h"
using namespace std;
using namespace::chrono;


void naslov_programa() {

	cout << " .-.. .-.  .--.--. .-. .--." << endl;
	cout << "(   |(   ) |  |  |(.-' `--." << endl;
	cout << " `-`| `-'`-'  '  `-`--'`--'" << endl;
	cout << " ._.'" << endl << endl;

}

void izbornik(int& izbor) {

	system("CLS");
	naslov_programa();
	cout << "Izbornik:" << endl;
	cout << "(opcije 1 i 2 su uvjet za ostale opcije)" << endl;
	cout << "1. Unos putanje" << endl;
	cout << "2. Unos podataka iz datoteke" << endl;
	cout << "3. Ispis top 5 izdavaca prema zaradi u Europi" << endl;
	cout << "4. Ispis svih igara koje se pojavljuju na vise od jedne platforme" << endl;
	cout << "5. Kopiranje datoteke" << endl;
	cout << "6. Obrada po platformama" << endl;
	cout << "7. Funkcionalnost 23" << endl;
	cout << "8. Statistika igara prema globalnoj zaradi" << endl;
	cout << "9. Transakcije" << endl;
	cout << "10. Zavrsetak programa" << endl << endl;

	cout << "Odaberite jednu opciju iz izbornika. (Upisite broj opcije): ";
	cin >> izbor;
	cin.ignore();

}

void poluizbornik(bool& povratak) {

	cout << endl << "Upisite 1 za povratak na izbornik ili 0 za zavrsetak programa: ";
	cin >> povratak;
	cin.ignore();
}

template<typename datoteka>

bool uspjesno_otvorena_datoteka(datoteka& dat, string naziv) {

	if (!dat) {

		system("CLS");
		cout << endl << "Greska kod otvaranja datoteke " << naziv << endl << endl;
		return false;

	}

	return true;
}

// IZBOR 1

void unos_putanje_foldera(ofstream& out) {

	system("CLS");
	cout << "1. UNOS PUTANJE" << endl << endl;

	string putanja;
	cout << "Upisite putanju foldera u kojemu se nalazi datoteka: ";
	getline(cin, putanja);

	// SPREMANJE PUTANJE U BINARNU DATOTEKU
	// Duljina stringa u znakovima (dakle, i u bajtovima).
	int duljina = putanja.length();
	// Upisivanje broja znakova stringa u binarnu datoteku
	out.write((char*)(&duljina), sizeof(duljina));
	// Upisivanje stringa u binarnu datoteku
	out.write(putanja.c_str(), duljina);

}

// IZBOR 2

string procitaj_putanju_foldera(ifstream& in, bool& navodnici) {

	// Èitanje duljine stringa.
	int duljina;
	in.read((char*)(&duljina), sizeof(duljina));
	// Alociranje memorije na hrpi.
	char* pchar = new char[duljina];
	// Èitanje znakova iz datoteke u tu memoriju.
	in.read(pchar, duljina);
	// Konstruiranje stringa na stogu.
	string putanja = string(pchar, duljina);
	// Oslobaðanje memorije
	delete[] pchar;

	if (putanja[0] == '"') navodnici = true;

	return putanja;

}

void makni_navodnike(string& putanja) {

	stringstream ss;
	for (int i = 0; i < putanja.length(); i++) {

		if (i != 0 && i != putanja.length() - 1) ss << putanja[i];

	}
	ss << '\\';
	putanja = ss.str();

}

void dodaj_na_kraj(string& putanja) {

	stringstream ss;
	for (int i = 0; i < putanja.length(); i++) {

		ss << putanja[i];

	}
	ss << '\\';
	putanja = ss.str();

}

void sredi_putanju(string& putanja) {

	stringstream ss;

	for (int i = 0; i < putanja.length(); i++) {
		
		if (putanja[i] == '\\') {
			ss << '\\';
		}
		ss << putanja[i];
	}

	putanja = ss.str();

}

void isparsiraj_datoteku(ifstream& in, vector<VideoGame>& igre) {

	system("CLS");
	cout << "2. UNOS PODATAKA IZ DATOTEKE" << endl;

	auto begin = high_resolution_clock::now();

	// PARSIRANJE DATOTEKE
	string line;
	getline(in, line);

	while (getline(in, line)) {

		stringstream ss(line);

		int rank;
		ss >> rank;

		char zarez;
		ss >> zarez;

		string name;
		getline(ss, name, ',');

		string platform;
		getline(ss, platform, ',');

		int year;
		ss >> year;

		ss >> zarez;

		string genre;
		getline(ss, genre, ',');

		string publisher;
		getline(ss, publisher, ',');

		double NA_sales;
		ss >> NA_sales;

		ss >> zarez;

		double EU_sales;
		ss >> EU_sales;

		ss >> zarez;

		double JP_sales;
		ss >> JP_sales;

		ss >> zarez;

		double Other_sales;
		ss >> Other_sales;

		ss >> zarez;

		double Global_sales;
		ss >> Global_sales;

		igre.emplace_back(rank, name, platform, year, genre, publisher, NA_sales, EU_sales, JP_sales, Other_sales, Global_sales);

	}

	auto end = high_resolution_clock::now();

	cout << endl << "vrijeme ucitavanja datoteke u vektor: " << duration_cast<milliseconds>(end - begin).count() << "ms" << endl;

}

// IZBOR 3

Izdavac pronadji_i_izbrisi_najveceg(list<Izdavac>& izdavaci) {

	double max = -1;
	Izdavac najveci;

	for (auto it = izdavaci.begin(); it != izdavaci.end(); ++it) {

		if (it->get_zarada() > max) {
			max = it->get_zarada();
			najveci = *it;
		}

	}

	for (auto it = izdavaci.begin(); it != izdavaci.end();) {

		if (it->get_zarada() == najveci.get_zarada()) {
			it = izdavaci.erase(it);
			break;
		}
		else it++;

	}
	return najveci;
}

bool ima_li_5_vecih(double zarada, list<Izdavac>& izdavaci) {

	int brojac = 0;

	for (auto it = izdavaci.begin(); it != izdavaci.end(); ++it) {

		if (it->get_zarada() > zarada) brojac++;
		if (brojac >= 5) return 1;
	}
	return 0;
}

void ispis_top_5_izdavaca_EU(vector<VideoGame>& igre) {

	system("CLS");
	cout << "3. ISPIS TOP 5 IZDAVACA PREMA ZARADI U EUROPI" << endl << endl;

	// STVARANJE POPISA SVIH IZDAVACA I NJIHOVIH UKUPNIH ZARADA
	list<Izdavac> izdavaci;
	for (int i = 0; i < igre.size(); i++) {

		bool nadjen = 0;

		for (auto it = izdavaci.begin(); it != izdavaci.end(); ++it) {

			if (igre[i].get_publisher() == it->get_ime()) {

				nadjen = 1;
				double zarada = it->get_zarada();
				zarada += igre[i].get_EU_sales();
				it->set_zarada(zarada);

			}

			if (nadjen) break;
		}

		if (nadjen == 0) {

			izdavaci.emplace_back(igre[i].get_publisher(), igre[i].get_EU_sales());

		}

	}

	// STVARANJE LISTE TOP 5
	for (auto it = izdavaci.begin(); it != izdavaci.end();) {

		if (ima_li_5_vecih(it->get_zarada(), izdavaci)) {
			it = izdavaci.erase(it);
		}
		else it++;

	}

	// SORTIRRANJE TOP 5 POMOÆU REDA
	queue<Izdavac> top5;
	for (int i = 0; i < 5; i++) {

		Izdavac najveci = pronadji_i_izbrisi_najveceg(izdavaci);
		top5.push(najveci);
	}

	// ISPIS TOP 5
	int i = 1;
	while (!top5.empty()) {
		cout << i << ". " << top5.front().to_str() << endl;
		i++;
		top5.pop();
	}

}

// IZBOR 4

void ucitaj_ispisi_igre_i_platforme(vector<VideoGame>& igre) {

	system("CLS");
	cout << "4. ISPIS SVIH IGARA KOJE SE POJAVLJUJU NA VISE OD JEDNE PLATFORME" << endl << endl;

	vector<Igra> igre_i_platforme;
	list<VideoGame> kopija(igre.begin(), igre.end());

	// stvaranje popisa

	int indeks = 0;

	while (!kopija.empty()) {

		auto it = kopija.begin();
		string ime = it->get_name();
		igre_i_platforme.emplace_back(it->get_name(), it->get_platform());

		for (auto it1 = kopija.erase(it); it1 != kopija.end();) {

			if (it1->get_name() == ime) {
				igre_i_platforme[indeks].add_platforma(it1->get_platform());
				it1 = kopija.erase(it1);
			}
			else it1++;
		}

		if(igre_i_platforme[indeks].get_size() > 1)
			cout << igre_i_platforme[indeks].to_string() << endl;
		indeks+=1;

	}

}

// IZBOR 5

void sredi_putanju_za_out(string& putanja) {

	stringstream ss;

	ss << '"';

	for (int i = 0; i < putanja.length(); i++) {

		if (putanja[i] == '\\') {
			ss << '\\';
		}
		ss << putanja[i];
	}

	ss << '"';

	putanja = ss.str();

}

void ucitaj_redoslijed_datoteku_folder(int& redoslijed, string& naziv_odredisne_datoteke, string& putanja_foldera) {

	system("CLS");
	cout << "5. KOPIRANJE DATOTEKE" << endl << endl;

	cout << "Zelite li prepisati retke iz datoteke u istom (1) ili obrnutom redoslijedu (2)?" << endl;
	cout << "upisite broj (1-isti redoslijed, 2-obrnuti): ";
	cin >> redoslijed;
	cin.ignore();


	cout << "Unesite naziv odredisne datoteke: ";
	getline(cin, naziv_odredisne_datoteke);


	cout << "Unesite putanju do foldera cu kojem se nalazi odredisna datoteka: ";
	getline(cin, putanja_foldera);

}

void prepisi_dobar_redoslijed(ifstream& in, ofstream& out) {

	queue<string> red;

	string line;
	while (getline(in, line)) {

		red.push(line);

	}

	while (!red.empty()) {

		out << red.front() << endl;
		red.pop();

	}

}

void prepisi_obrnuti_redoslijed(ifstream& in, ofstream& out) {

	stack<string> stog;

	string line;
	while (getline(in, line)) {

		stog.push(line);

	}

	while (!stog.empty()) {

		out << stog.top() << endl;
		stog.pop();

	}

}


// IZBOR 6

template<typename T>

void kopiraj(vector<VideoGame>& igre, list<T>& igre_platfrome, string& platforma) {

	for (int i = 0; i < igre.size(); i++) {

		if (igre[i].get_platform() == platforma) {

			igre_platfrome.push_back(igre[i]);

		}

	}

}

void izbrisi(list<VideoGame>& igre_platforme) {

	for (auto it = igre_platforme.begin(); it != igre_platforme.end();) {

		if (it->get_Global_sales() < 250000.00) {

			it = igre_platforme.erase(it);

		}

		else {
			++it;
		}
	}

}

void preslozi(list<VideoGame>& igre_platforme) {

	stack<VideoGame> stog;

	for (auto it = igre_platforme.begin(); it != igre_platforme.end(); ++it) {

		stog.push(*it);

	}

	igre_platforme.clear();

	while (!stog.empty()) {

		igre_platforme.push_back(stog.top());
		stog.pop();

	}

}

void ispis(list<VideoGame>& igre_platforme) {

	cout.precision(15);

	for (auto it = igre_platforme.begin(); it != igre_platforme.end(); ++it) {

		cout << it->get_name() << endl;

	}

}

// IZBOR 7

bool ima_dvotocku(string naziv) {

	for (int i = 0; i < naziv.length(); i++) {

		if (naziv[i] == ':') return true;

	}

	return false;
}

string tekst_iza_dvotocke(string naziv) {

	bool dvotocka = false;
	stringstream ss;

	for (int i = 0; i < naziv.length(); i++) {

		if (dvotocka) {

			ss << naziv[i];

		}

		if (naziv[i] == ':') {
			dvotocka = true;
		}

	}

	return ss.str();
}

void funkcionalnost23(vector<VideoGame>& igre) {

	system("CLS");
	cout << "7. FUNKCIONALNOST 23" << endl << endl;

	stack<string> stog;

	for (auto it = igre.rbegin(); it != igre.rend(); ++it) {

		if (ima_dvotocku(it->get_name())) {

			stog.push(tekst_iza_dvotocke(it->get_name()));

		}
		else {

			if (!stog.empty()) {

				cout << stog.top() << endl;
				stog.pop();

			}
			else cout << "Stog je prazan." << endl;

		}

	}

	cout << endl << "sto je ostalo na stogu: " << endl << endl;

	if (!stog.empty()) {

		while (!stog.empty()) {

			cout << stog.top() << endl;
			stog.pop();

		}

	}
	else cout << "Stog je prazan." << endl;

}

// IZBOR 8

template<typename t>
void iscrtaj(int& raspon, int p, t k) {

	if (p == 50) {
		cout << p << k << '\t';
	}
	else {
		cout << p << " - " << k << '\t';
	}

	int istina = 0;

	for (int i = 10; 1; i += 10) {

		if (raspon <= i) {

			int broj = i;
			broj /= 10;

			for (int j = 0; j < broj; j++) {

				cout << "#";

			}

			istina = 1;
		}
		if (istina) break;
	}

	cout << "(" << raspon << ")" << endl;

}

void statistika_igara(vector<VideoGame>& igre) {

	system("CLS");
	cout << "8. STATISTIKA IGARA PREMA GLOBALNOJ ZARADI" << endl << endl;

	int raspon1 = 0;
	int raspon2 = 0;
	int raspon3 = 0;
	int raspon4 = 0;
	int raspon5 = 0;

	for (int i = 0; i < igre.size(); i++) {

		if (igre[i].get_Global_sales() >= 0 && igre[i].get_Global_sales() <= 9) {
			raspon1++;
		}
		else if (igre[i].get_Global_sales() >= 10 && igre[i].get_Global_sales() <= 19) {
			raspon2++;
		}
		else if (igre[i].get_Global_sales() >= 20 && igre[i].get_Global_sales() <= 29) {
			raspon3++;
		}
		else if (igre[i].get_Global_sales() >= 30 && igre[i].get_Global_sales() <= 49) {
			raspon4++;
		}
		else raspon5++;

	}

	iscrtaj<int>(raspon1, 0, 9);
	iscrtaj<int>(raspon2, 10, 19);
	iscrtaj<int>(raspon3, 20, 29);
	iscrtaj<int>(raspon4, 30, 49);
	iscrtaj<char>(raspon5, 50, '+');

}

// IZBOR 9

double get_update(string naredba) {

	stringstream ss;
	for (int i = 32; i < naredba.length(); i++) {
		ss << naredba[i];
	}
	double broj;
	ss >> broj;
	return broj;
}

void transakcije(vector<VideoGame>& igre) {

	system("CLS");
	cout << "9. TRANSAKCIJE" << endl << endl;

	string naredba;
	stack<string> stog;

	do {
		cout << "Upisite naredbu: ";
		getline(cin, naredba);
		stog.push(naredba);

	} while (naredba != "ROLLBACK" && naredba != "COMMIT");


	string zadnja_naredba = stog.top();
	if (zadnja_naredba == "ROLLBACK") {

	}
	else if (zadnja_naredba == "COMMIT") {

		stog.pop();
		while (!stog.empty()) {

			if (stog.top() == "BEGIN TRAN") stog.pop();
			else {

				double n = get_update(stog.top());
				stog.pop();

				for (int i = 0; i < igre.size(); i++) {

					double global_sales = igre[i].get_Global_sales() + n;
					igre[i].set_Global_sales(global_sales);

				}
			}

		}

	}

	for (int i = 0; i < igre.size(); i++) {

		cout << igre[i].get_rank() << ", " << igre[i].get_name() << ", " << igre[i].get_Global_sales() << endl;

	}

}

// MAIN

int main() {

	int izbor;
	bool povratak;
	string putanja;
	vector<VideoGame> igre;

	do {

		izbornik(izbor);

		if (izbor == 1) {

			ofstream out("putanja.bin", ios_base::binary);
			if (!uspjesno_otvorena_datoteka<ofstream>(out, "putanja.bin")) return -1;
			unos_putanje_foldera(out);
			out.close();

			poluizbornik(povratak);
			if (!povratak) return 0;

		}
		else if (izbor == 2) {

			ifstream in("putanja.bin", ios_base::binary);
			if (!uspjesno_otvorena_datoteka<ifstream>(in, "putanja.bin")) return -1;
			bool navodnici = 0;
			putanja = procitaj_putanju_foldera(in, navodnici);
			in.close();

			if (navodnici) {
				makni_navodnike(putanja);
			}
			else {
				dodaj_na_kraj(putanja);
			}

			putanja = putanja + "SPA_PROJ_006_GAME_SALES_data.csv";

			sredi_putanju(putanja);

			ifstream dat(putanja);
			if (!uspjesno_otvorena_datoteka<ifstream>(dat, putanja)) return -1;
			isparsiraj_datoteku(dat, igre);
			dat.close();

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 3) {

			ispis_top_5_izdavaca_EU(igre);

			poluizbornik(povratak);
			if (povratak == 0) return 0;

		}
		else if (izbor == 4) {

			ucitaj_ispisi_igre_i_platforme(igre);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 5) {

			int redoslijed;
			string naziv_odredisne_datoteke;
			string putanja_foldera;

			ucitaj_redoslijed_datoteku_folder(redoslijed, naziv_odredisne_datoteke, putanja_foldera);

			if (putanja_foldera[0] == '"') {
				makni_navodnike(putanja_foldera);
			}
			else dodaj_na_kraj(putanja_foldera);

			string odredisna_putanja = putanja_foldera + naziv_odredisne_datoteke;
			sredi_putanju(odredisna_putanja);

			ifstream in(putanja);
			if (!uspjesno_otvorena_datoteka<ifstream>(in, putanja)) return -1;

			ofstream out(odredisna_putanja);
			if (!uspjesno_otvorena_datoteka<ofstream>(out, naziv_odredisne_datoteke)) return -1;

			if (redoslijed == 1) {

				prepisi_dobar_redoslijed(in, out);

			}
			else {

				prepisi_obrnuti_redoslijed(in, out);

			}

			in.close();
			out.close();

			poluizbornik(povratak);
			if (povratak == 0) return 0;

		}
		else if (izbor == 6) {

			system("CLS");
			cout << "Upisite naziv platforme: ";
			string platforma;
			getline(cin, platforma);

			list<VideoGame> igre_platforme;

			kopiraj<VideoGame>(igre, igre_platforme, platforma);
			izbrisi(igre_platforme);

			if (!igre_platforme.empty()) {
				preslozi(igre_platforme);
				ispis(igre_platforme);
			}
			else cout << "Globalna zarada svih igara te platforme manja je od 250.000,00 USD" << endl;

			poluizbornik(povratak);
			if (povratak == 0) return 0;

		}
		else if (izbor == 7) {

			funkcionalnost23(igre);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 8) {

			statistika_igara(igre);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 9) {

			transakcije(igre);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else return 0;

	} while (izbor != 10);

	return 0;
}