#include <iostream>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

bool is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(), 
		s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

void error()
{
	cout << "ERROR: Nesprávné zadání!\n" << endl;
}

struct ZakladniTexty
{
	const string easyText = "EASY obtížnost\n- Začínáte s 3 mld. penězi\n- Začínáte s 2000 vojáky\n- Dokud neinvestujete, získáváte 2 mld. peněz za kolo\n- Chcete-li vyhrát, musíte získat 25 území\n- Investovat můžete do 10 peněz za kolo\n- Invaze do vaší země se konají každých 10 kol\n- Invaze jsou vždy po 1000 vojácích";
	const string normalText = "NORMAL obtížnost\n- Začínáte s 3 mld. penězi\n- Nezačínáte s žádnými vojáky\n- Dokud neinvestujete, získáváte 2 mld. peněz za kolo\n- Chcete-li vyhrát, musíte získat 55 území\n- Investovat můžete do 5 peněz za kolo\n- Invaze do vaší země se konají každých 5 kol\n- Invaze jsou vždy po 1000 vojácích";
	const string hardText = "HARD obtížnost\n- Nezačínáte s žádnými penězi\n- Nezačínáte s žádnými vojáky\n- Dokud neinvestujete, získáváte 2 mld. peněz za kolo\n- Chcete-li vyhrát, musíte získat 70 území\n- Investovat můžete do 5 peněz za kolo\n- Invaze do vaší země se konají každých 5 kol\n- Invaze jsou vždy po 2000 vojácích";
};

struct Hra
{
	int penize;
	int vojaci;
	int kola = 1;
	int obsadit;
	int banka = 0;
	int penize_za_kolo = 2;
};

bool koupitVojaky(Hra& hra)
{
	string pocet_str;
	int pocet;

	cout << "Máš " << hra.vojaci << " vojáků, peněz " << hra.penize << ", cena za 1000 vojáků je 1 mld. Kolik jich chceš koupit? ";
	cin >> pocet_str;
	if (!is_number(pocet_str))
		return 1;
	
	pocet = stoi(pocet_str);
	if (pocet % 1000 != 0) {
		cout << "Nezadal jsi číslo dělitelné 1000!";
		return 0;
	}

	if (hra.penize < pocet / 1000) {
		cout << "NEMÁŠ DOSTATEK FINANCÍ!";
		return 0;
	}

	hra.penize -= pocet / 1000;
	hra.vojaci += pocet;
	cout << "Nakoupeno " << pocet << " vojáků." << endl << "Celkem máš " << hra.vojaci << " vojáků, zbývá ti " << hra.penize << " peněz.";
	return 0;
}

bool valka(Hra& hra)
{
	string obsadit_str;
	char& obsadit = obsadit_str[0];

	cout << "Musíš obsadit ještě " << hra.obsadit << " území. Na jedno území potřebuješ 2000 vojáků, chceš zaútočit? A = Ano, N = Ne: ";
	cin >> obsadit_str;
	if (obsadit_str.length() > 1)
		return 1;

	obsadit_str = toupper(obsadit);
	switch (obsadit)
	{
	case 'A':
		if (hra.vojaci < 2000) {
			cout << "NEMÁŠ DOSTATEK VOJÁKŮ!";
			return 0;
		}

		hra.vojaci -= 2000;
		hra.obsadit -= 1;
		cout << "Zaútočil jsi! Zbývá ti " << hra.vojaci << " vojáků.";
		return 0;
	case 'N':
		cout << "NE!";
		return 0;
	default:
		return 1;
	}
}

bool investovat(Hra& hra, bool isEasy)
{
	string investice_str;
	int investice;

	cout << "Kolik chceš investovat?\n6 (+1 peníz za kolo)\n10 (+2 peníze za kolo): ";
	cin >> investice_str;
	if (!is_number(investice_str))
		return 1;

	investice = stoi(investice_str);
	if (investice != 6 && investice != 10)
		return 1;

	if (hra.penize < investice) {
		cout << "NEMÁŠ DOSTATEK FINANCÍ!";
		return 0;
	}

	if (hra.penize_za_kolo > ((investice == 6) ? 4 : 3) && !isEasy || hra.penize_za_kolo > ((investice == 6) ? 9 : 8)) {
		cout << "Už jsi investoval až moc peněz!";
		return 0;
	}

	hra.penize -= investice;
	hra.penize_za_kolo += floor(investice / 5);
	cout << hra.penize_za_kolo;
	return 0;
}

bool obtiznost_switch(char obtiznost, ZakladniTexty zakladniTexty, int& penize, int& vojaci, int& obsadit, string& zakladniText)
{
	switch (obtiznost)
	{
	case 'E':
		penize = 3;
		vojaci = 2000;
		obsadit = 25;
		zakladniText = zakladniTexty.easyText;
		return 0;
	case 'N':
		penize = 3;
		vojaci = 0;
		obsadit = 55;
		zakladniText = zakladniTexty.normalText;
		return 0;
	case 'H':
		penize = 0;
		vojaci = 0;
		obsadit = 70;
		zakladniText = zakladniTexty.hardText;
		return 0;
	default:
		return 1;
	}
}

bool vyber_switch(char vyber, Hra& hra, char obtiznost)
{
	switch (vyber)
	{
		case 'K':
			return koupitVojaky(hra);
		case 'V':
			return valka(hra);
		case 'I':
			return investovat(hra, obtiznost == 'E');
		case 'B':
			return 0;
		case 'D':
			return 0;
		case 'E':
			cout << "Odešel jsi ze hry." << endl;
			exit(0);
		default:
			return 1;
	}
}

int main() {
	Hra hra;
	ZakladniTexty zakladniTexty;
	string zakladniText;

	char* obtiznost;

	bool quit = false;
	while (!quit) {
		string obtiznost_str;
		obtiznost = &obtiznost_str[0];

		cout << "Na jakou chceš hrát obtížnost\nE = Easy\nN = Normal\nH = Hard: ";
		cin >> obtiznost_str;
		if (obtiznost_str.length() > 1) {
			error();
			continue;
		}

		obtiznost_str = toupper(*obtiznost);
		obtiznost_switch(*obtiznost, zakladniTexty, hra.penize, hra.vojaci, hra.obsadit, zakladniText) ? [] {error(); main();}() : [zakladniText] {cout << zakladniText << endl << "Stiskem ENTER pokračujte: ";}();
		quit = true;
	}

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.get();

	cout << "Toto je vylepšená verze hry textova_hra.py. Jestli chcete mít zážitek ze hry textova_hra, jako takový, stáhněte si KV OS BETA 0.6.\n" << endl;
	while (true) {
		string vyber_str;
		char& vyber = vyber_str[0];

		cout << hra.kola << ". KOLO! \nK = Koupit vojáky, V = Válka, I = Investovat, B = Banka, D = Další kolo, E = Exit: ";
		cin >> vyber_str;
		if (vyber_str.length() > 1) {
			error();
			continue;
		}

		vyber_str = toupper(vyber);
		if (vyber_switch(vyber, hra, *obtiznost)) {
			error();
			continue;
		}

		cout << endl << endl;
	}
}
