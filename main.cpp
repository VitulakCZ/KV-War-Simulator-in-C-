#include <iostream>

using namespace std;

void error()
{
	cout << "ERROR: Nesprávné zadání!";
}

bool obtiznost_switch(char obtiznost, int& penize, int& vojaci, int& obsadit)
{
	switch (obtiznost)
	{
	case 'E':
		penize = 3;
		vojaci = 2000;
		obsadit = 25;
		return 0;
	case 'N':
		penize = 3;
		vojaci = 0;
		obsadit = 55;
		return 0;
	case 'H':
		penize = 0;
		vojaci = 0;
		obsadit = 70;
		return 0;
	default:
		return 1;
	}
}

struct Hra
{
	int penize;
	int vojaci;
	int obsadit;
	int banka = 0;
	int penize_za_kolo = 2;
};


int main() {
	Hra hra;
	bool quit = false;
	while (!quit) {
		string obtiznost_str;
		char& obtiznost = obtiznost_str[0];

		cout << "Na jakou chceš hrát obtížnost\nE = Easy\nN = Normal\nH = Hard: ";
		cin >> obtiznost_str;
		if (obtiznost_str.length() > 1) {
			error();
			continue;
		}
		obtiznost_str = toupper((char)obtiznost_str[0]);
		obtiznost_switch(obtiznost, hra.penize, hra.vojaci, hra.obsadit) ? [] {error(); main();}() : [] {cout << "Dobře ty!" << endl;}();
		quit = true;
	}
}