// Chmielecki_Damian.cpp Visual Studio 2019

#include <iostream>
#include <iomanip>
#include<cstdlib>

using namespace std;

const int MAX_W = 8;
const int MAX_K = 8;

void menu();

void gen_planszy(int PLANSZA[][MAX_K], int k);

void plansza_startowa(int PLANSZA[][MAX_K], int i, int j);

void plansza_dalsza(int PLANSZA[][MAX_K], int i, int j, int k);

void ruch(int gracz, int PLANSZA[MAX_W][MAX_K]);

bool spr_puste(int w, int k, int PLANSZA[MAX_W][MAX_K]);

bool istnienie_pionka(int wp, int kp, int gracz, int PLANSZA[MAX_W][MAX_K]);

void interpretacja(char wiersz, int kolumna, int& w, int& k);

void wyb_pionka(bool& mozliwosc, int PLANSZA[MAX_W][MAX_K], int gracz, int& wp, int& kp, int stan_przed);

void wyb_pola_b(bool& mozliwosc, int PLANSZA[MAX_W][MAX_K], int& gracz, int wp, int kp, int& u);

void wyb_pola(bool& mozliwosc, int PLANSZA[MAX_W][MAX_K], int gracz, int wp, int kp);

bool szuk_wroga(int PLANSZA[MAX_W][MAX_K], int wp, int kp, int gracz);

bool spr_mozliwosci_ruchu(int gracz,int PLANSZA[MAX_W][MAX_K],int wp,int kp);

void uwaga_bicie(int PLANSZA[MAX_W][MAX_K], int gracz, int& stan_przed);

bool warunek_wygranej(int PLANSZA[MAX_W][MAX_K], int gracz);

void ruch_zwykly_trans(int& s,int wp,int kp,int wr,int kr,int PLANSZA[MAX_W][MAX_K], int gracz);

void bicie_trans(int gracz, int PLANSZA[MAX_W][MAX_K], int wp, int kp, int wb, int kb, int& k, int& u);

void bicie_trans_O(int gracz, int PLANSZA[MAX_W][MAX_K], int wp, int kp, int wb, int kb, int& k, int& u);

void bicie_trans_X(int gracz, int PLANSZA[MAX_W][MAX_K], int wp, int kp, int wb, int kb, int& k, int& u);

void the_library_is_open(int X,int Y,int& wiersz,int& kolumna);


int main()
{

	setlocale(LC_ALL, ""); //strona kodowa CP852 

	int PLANSZA[MAX_W][MAX_K];
	int k = 0;
	int gracz = 3;

	menu();

	gen_planszy(PLANSZA, k);

	ruch(gracz, PLANSZA);


	system("PAUSE");

	return 0;
}


void menu() {

	cout << endl;
	cout << "Witaj w grze warcaby!" << endl;
	cout << endl;

		cout << "----------------------" << endl;
		cout << "                  Z  A  S  A  D  Y    G  R  Y                                                                                                         " << endl;
		cout << endl;
		cout << "Gra w warcaby jest przeznaczona dla dwóch graczy. Na planszy 32 polowej umieszczonych jest 8 figur ‘o’ i 8 figur ‘x’." << endl;
		cout << "Gracze poruszają się na zmianę, pierwsza figurami ‘x’, drugimi figurami ‘o’. Figury mogą przekształcać się w figury przez ‘X’ oraz ‘O’." << endl;
		cout << "W jednej turze gracz musi poruszać się jedną figurą. Możliwe ruchy:" << endl;
		cout << endl;
		cout << "	Figury ‘o’, ‘x’ mogą się poruszać po przekątnej o jedno pole do przodu." << endl;
		cout << endl;
		cout << "	Figury ‘o’, ‘x’ mogą bić w przód, czyli przeskakiwać figurę przeciwnika na pole znajdujące się tuż za nim, pole to musi być wolne." << endl;
		cout << endl;
		cout << "	Figury ‘O’, ‘X’ mogą wykonywać te same ruchy co ‘o’, ‘x’ w dowolnym kierunku." << endl;
		cout << endl;
		cout << "Jeśli figura ‘o’ lub ‘x’ skończy swój ruch na ostatnim polu, wtedy zamienia się w figurę ‘O’ lub ‘X’." << endl;
		cout << "Po zbiciu figura jest zdejmowana z planszy.Bicie jest wymagane.Możliwe jest wielokrotne bicie." << endl;
		cout <<	"Gracz przegrywa jeśli nie może poruszać się żadną z figur lub wszystkie straci." << endl;
		cout << endl;
		cout << "-----------------------" << endl;
		cout << endl;
}


void gen_planszy(int PLANSZA[][MAX_K], int k) {

	cout << endl;
	cout << "   +--------+" << endl;

	for (int i = 0; i < 8; i++) {
		if (i == 0) cout << "A  |";
		if (i == 1) cout << "B  |";
		if (i == 2) cout << "C  |";
		if (i == 3) cout << "D  |";
		if (i == 4) cout << "E  |";
		if (i == 5) cout << "F  |";
		if (i == 6) cout << "G  |";
		if (i == 7) cout << "H  |";
		for (int j = 0; j < 8; j++)
		{
			if (k == 0)
				plansza_startowa(PLANSZA, i, j);
			plansza_dalsza(PLANSZA, i, j, k);

		}
		cout << "|" << endl;
	}
	cout << "   +--------+" << endl;
	cout << "    12345678 " << endl;
	cout << endl;
}


void plansza_startowa(int PLANSZA[][MAX_K], int i, int j) {

	// wolne pole
	if (((i == 2 || i == 4) && (j == 0 || j == 2 || j == 4 || j == 6)) || ((i == 3 || i == 5) && (j == 1 || j == 3 || j == 5 || j == 7)))
		PLANSZA[i][j] = 0;

	//zablokowane pole
	if ((i == 0 || i == 2 || i == 4 || i == 6) && (j == 1 || j == 3 || j == 5 || j == 7) || ((i == 1 || i == 3 || i == 5 || i == 7) && (j == 0 || j == 2 || j == 4 || j == 6)))
		PLANSZA[i][j] = 1;

	//x
	if (i == 0 && (j == 0 || j == 2 || j == 4 || j == 6) || (i == 1 && (j == 1 || j == 3 || j == 5 || j == 7)))
		PLANSZA[i][j] = 2;

	//o
	if (i == 6 && (j == 0 || j == 2 || j == 4 || j == 6) || (i == 7 && (j == 1 || j == 3 || j == 5 || j == 7)))
		PLANSZA[i][j] = 3;
}


void plansza_dalsza(int PLANSZA[][MAX_K], int i, int j, int k) {

	if (PLANSZA[i][j] == 0) cout << " ";
	else
		if (PLANSZA[i][j] == 1) cout << ".";
		else
			if (PLANSZA[i][j] == 2) cout << "x";
			else
				if (PLANSZA[i][j] == 3) cout << "o";
				else
					if (PLANSZA[i][j] == 4) cout << "X";
					else
						if (PLANSZA[i][j] == 6) cout << "O";
	k++;
}


void ruch(int gracz, int PLANSZA[MAX_W][MAX_K]) {

	bool koniec_gry = false;

	while (koniec_gry == false) {

		char strona;
		int wp = 0, kp = 0, k = 1, stan_przed = 0, u = 0;
		bool mozliwosc = false, wrog = false;

		if (gracz == 3) strona = 'o';
		else strona = 'x';

		koniec_gry = warunek_wygranej(PLANSZA, gracz);
		if (koniec_gry == false) {

			cout << "Czas na ruch gracza " << strona << " ." << endl;

				uwaga_bicie(PLANSZA, gracz, stan_przed);

			if (stan_przed != 0) cout << "Graczu! Musisz wykonać bicie!" << endl;

				wyb_pionka(mozliwosc, PLANSZA, gracz, wp, kp, stan_przed);
		 
				wrog = szuk_wroga(PLANSZA, wp, kp, gracz);

			if (wrog == true) {
				wyb_pola_b(mozliwosc, PLANSZA, gracz, wp, kp, u);
			}
			else {
				wyb_pola(mozliwosc, PLANSZA, gracz, wp, kp);
			}

			if (u == 0) {
				if (gracz == 3) gracz = 2;
				else gracz = 3;
			}

				system("cls");
				gen_planszy(PLANSZA, k);
		}

		else koniec_gry = true;
	}
}


//pionek
void interpretacja(char wiersz, int kolumna, int& w, int& k) {

	w = wiersz;
	k = kolumna;
}


//pionek
bool istnienie_pionka(int wp, int kp, int gracz, int PLANSZA[MAX_W][MAX_K]) {

	if (gracz == 3 && (PLANSZA[wp][kp] == 3 || PLANSZA[wp][kp] == 6)) return true;
	else if (gracz == 2 && (PLANSZA[wp][kp] == 2 || PLANSZA[wp][kp] == 4)) return true;
	else return false;
}  


//pole
bool spr_puste(int w, int k, int PLANSZA[MAX_W][MAX_K]) {

	if (PLANSZA[w][k] != 0) { return true; }
	else { return false; }
}


//pionek
void wyb_pionka(bool& mozliwosc, int PLANSZA[MAX_W][MAX_K], int gracz, int& wp, int& kp, int stan_przed) {

	bool mozliwosc2 = false;
	bool mozliwosc3 = false;

	while (mozliwosc == false || mozliwosc2 == false || mozliwosc3 == false) {

		char X, Y;
		int kolumna, wiersz;

			cout << "Jakim pionkiem chcesz się ruszyć? Podaj wiersz A-H oraz kolumne 1-8." << endl;
				cin >> X;
				cin >> Y;

		the_library_is_open(X, Y, wiersz, kolumna);

		interpretacja(wiersz, kolumna, wp, kp);

			mozliwosc = istnienie_pionka(wp, kp, gracz, PLANSZA);

			mozliwosc2 = spr_mozliwosci_ruchu(gracz, PLANSZA, wp, kp);

		if (stan_przed != 0)
			mozliwosc3 = szuk_wroga(PLANSZA, wp, kp, gracz);

		else mozliwosc3 = true;

		if (mozliwosc == false || mozliwosc2 == false || mozliwosc3 == false) {

			if (PLANSZA[wp][kp] == 2 || PLANSZA[wp][kp] == 4 || PLANSZA[wp][kp] == 3 || PLANSZA[wp][kp] == 6)
				cout << "Nie możesz ruszyć sie tym pionkiem!" << endl;

			else cout << "Hej! To nie jest pionek!" << endl;
			}
	}
}


void wyb_pola_b(bool& mozliwosc, int PLANSZA[MAX_W][MAX_K], int& gracz, int wp, int kp, int& u) {

	int k = 0;

	while (k == 0) {

		int kolumna, wb = 0, kb = 0, wiersz = 0;
		char X, Y;

		cout << "Gdzie chcesz sie ruszyć? Podaj wiersz A-H oraz kolumne 1-8." << endl;
		cin >> X;
		cin >> Y;

		the_library_is_open(X, Y, wiersz, kolumna);

		interpretacja(wiersz, kolumna, wb, kb);

		if (PLANSZA[wb][kb] == 2 || PLANSZA[wb][kb] == 4 || PLANSZA[wb][kb] == 6 || PLANSZA[wb][kb] == 3) {
			cout << "Musisz wybrać pole za przeciwnikiem." << endl;
		}
		else {
			bicie_trans(gracz, PLANSZA, wp, kp, wb, kb, k, u);
			mozliwosc = spr_puste(wb, kb, PLANSZA);
		}

		if (mozliwosc == false) cout << "Wybrałeś złe pole!" << endl;
	}
}


void wyb_pola(bool& mozliwosc, int PLANSZA[MAX_W][MAX_K], int gracz, int wp, int kp) {

	while (mozliwosc == true ) {

		char X, Y;
		int kolumna, wr = 0, kr = 0, wiersz = 0;

		cout << "Gdzie chcesz się ruszyć? Podaj wiersz A-H oraz kolumne 1-8." << endl;
		cin >> X;
		cin >> Y;  

		the_library_is_open(X, Y, wiersz, kolumna);

		interpretacja(wiersz, kolumna, wr, kr);

		mozliwosc = spr_puste(wr, kr, PLANSZA);

		if (mozliwosc == false) {

			int s = 0;

			ruch_zwykly_trans(s, wp, kp, wr, kr, PLANSZA, gracz);

			if (s == 0 && (PLANSZA[wr][kr] == 1 || PLANSZA[wr][kr] == 2 || PLANSZA[wr][kr] == 4 || PLANSZA[wr][kr] == 6)) { cout << "Tu nie mozesz sie ruszyc!" << endl; mozliwosc = true; }
			else if (s == 0) { cout << "Za daleko!" << endl; mozliwosc = true; }
		}

		if (mozliwosc == true) { cout << "Wybrałeś złe pole!" << endl; mozliwosc = true; }
	}
}


bool szuk_wroga(int PLANSZA[MAX_W][MAX_K], int wp, int kp, int gracz) {

	int s = 0;

	if (gracz == 3 && (PLANSZA[wp - 1][kp + 1] == 2 || PLANSZA[wp - 1][kp + 1] == 4) && PLANSZA[wp - 2][kp + 2] == 0) { return true; s++; }

	if (gracz == 3 && (PLANSZA[wp - 1][kp - 1] == 2 || PLANSZA[wp - 1][kp - 1] == 4) && PLANSZA[wp - 2][kp - 2] == 0) { return true; s++; }
		
	if (gracz == 2 && (PLANSZA[wp + 1][kp + 1] == 3 || PLANSZA[wp + 1][kp + 1] == 6) && PLANSZA[wp + 2][kp + 2] == 0) { return true; s++; }

	if (gracz == 2 && (PLANSZA[wp + 1][kp - 1] == 3 || PLANSZA[wp + 1][kp - 1] == 6) && PLANSZA[wp + 2][kp - 2] == 0) { return true; s++; }

	if (gracz == 3 && PLANSZA[wp][kp] == 6 && (PLANSZA[wp + 1][kp - 1] == 2 || PLANSZA[wp + 1][kp - 1] == 4) && PLANSZA[wp + 2][kp - 2] == 0) { return true; s++; }

	if (gracz == 3 && PLANSZA[wp][kp] == 6 && (PLANSZA[wp + 1][kp + 1] == 2 || PLANSZA[wp + 1][kp + 1] == 4) && PLANSZA[wp + 2][kp + 2] == 0) { return true; s++; }

	if (gracz == 2 && PLANSZA[wp][kp] == 4 && (PLANSZA[wp - 1][kp - 1] == 3 || PLANSZA[wp - 1][kp - 1] == 6) && PLANSZA[wp - 2][kp - 2] == 0) { return true; s++; }

	if (gracz == 2 && PLANSZA[wp][kp] == 4 && (PLANSZA[wp - 1][kp + 1] == 3 || PLANSZA[wp - 1][kp + 1] == 6) && PLANSZA[wp - 2][kp + 2] == 0) { return true; s++; }

	if (s == 0) return false;
}


bool spr_mozliwosci_ruchu(int gracz, int PLANSZA[MAX_W][MAX_K], int wp, int kp) {

	if (PLANSZA[wp][kp] == 3) {

		int s = 0;

		if (PLANSZA[wp - 1][kp + 1] == 0 || PLANSZA[wp - 1][kp - 1] == 0) { return true; s++;}

		if ((PLANSZA[wp - 2][kp + 2] == 0 && (PLANSZA[wp - 1][kp + 1] == 2 || PLANSZA[wp - 1][kp + 1] == 4))  || 
			(PLANSZA[wp - 2][kp - 2] == 0 && (PLANSZA[wp - 1][kp - 1] == 2 || PLANSZA[wp - 1][kp - 1] == 4))) { return true; s++;}

		if (s == 0) return false;
	}

	if (PLANSZA[wp][kp] == 2) {

		int s = 0;

		if ((PLANSZA[wp + 1][kp + 1] == 0 || PLANSZA[wp + 1][kp - 1] == 0)) { return true; s++;}

		if ((PLANSZA[wp + 2][kp + 2] == 0 && (PLANSZA[wp + 1][kp + 1] == 3 || PLANSZA[wp + 1][kp + 1] == 6))  ||     
			(PLANSZA[wp + 2][kp - 2] == 0 && (PLANSZA[wp + 1][kp - 1] == 3 || PLANSZA[wp + 1][kp - 1] == 6))) { return true; s++;}

		if (s == 0) return false;
	}

	if (PLANSZA[wp][kp] == 4 || PLANSZA[wp][kp] == 6) {

		int s = 0;

		if (szuk_wroga(PLANSZA, wp, kp, gracz) == false) {

			if (PLANSZA[wp + 1][kp + 1] == 0 || PLANSZA[wp + 1][kp - 1] == 0 || PLANSZA[wp - 1][kp + 1] == 0 || PLANSZA[wp - 1][kp - 1] == 0) { return true; s++; }
		
		}
		if (PLANSZA[wp][kp] == 4) {

			if ((PLANSZA[wp + 2][kp + 2] == 0 && (PLANSZA[wp + 1][kp + 1] == 3 || PLANSZA[wp + 1][kp + 1] == 6)) ||
				(PLANSZA[wp + 2][kp - 2] == 0 && (PLANSZA[wp + 1][kp - 1] == 3 || PLANSZA[wp + 1][kp - 1] == 6))) 
				return true; s++; 

			if ((PLANSZA[wp - 2][kp + 2] == 0 && (PLANSZA[wp - 1][kp + 1] == 3 || PLANSZA[wp - 1][kp + 1] == 6)) ||
				(PLANSZA[wp - 2][kp - 2] == 0 && (PLANSZA[wp - 1][kp - 1] == 3 || PLANSZA[wp - 1][kp - 1] == 6))) 
				return true; s++;
		}
		if (PLANSZA[wp][kp] == 6) {

			if ((PLANSZA[wp + 2][kp + 2] == 0 && (PLANSZA[wp + 1][kp + 1] == 2 || PLANSZA[wp + 1][kp + 1] == 4)) ||
				(PLANSZA[wp + 2][kp - 2] == 0 && (PLANSZA[wp + 1][kp - 1] == 2 || PLANSZA[wp + 1][kp - 1] == 4))) 
				return true; s++; 

			if ((PLANSZA[wp - 2][kp + 2] == 0 && (PLANSZA[wp - 1][kp + 1] == 2 || PLANSZA[wp - 1][kp + 1] == 4)) ||
				(PLANSZA[wp - 2][kp - 2] == 0 && (PLANSZA[wp - 1][kp - 1] == 2 || PLANSZA[wp - 1][kp - 1] == 4))) 
				return true; s++;
		}
		if (s == 0) return false;
	}
}


void uwaga_bicie(int PLANSZA[MAX_W][MAX_K], int gracz, int& stan_przed) {  //na calej planszy sprawdzamy czy wystepuja bicia

	if (gracz == 3) {
		for (int w = 0; w < 8; w++)
			for (int k = 0; k < 8; k++) {

				if ((PLANSZA[w][k] == 3) && (((PLANSZA[w - 1][k + 1] == 2 || PLANSZA[w - 1][k + 1] == 4) && (PLANSZA[w - 2][k + 2] == 0)) || ((PLANSZA[w - 1][k - 1] == 2 || PLANSZA[w - 1][k - 1] == 4) && (PLANSZA[w - 2][k - 2] == 0))))
					stan_przed++;

				//   O do przodu
				if ((PLANSZA[w][k] == 6) && (((PLANSZA[w - 1][k + 1] == 2 || PLANSZA[w - 1][k + 1] == 4) && (PLANSZA[w - 2][k + 2] == 0)) || ((PLANSZA[w - 1][k - 1] == 2 || PLANSZA[w - 1][k - 1] == 4) && (PLANSZA[w - 2][k - 2] == 0))))
					stan_przed++;

				//   O do tyłu
				if ((PLANSZA[w][k] == 6) && (((PLANSZA[w + 1][k + 1] == 2 || PLANSZA[w + 1][k + 1] == 4) && (PLANSZA[w + 2][k + 2] == 0)) || ((PLANSZA[w + 1][k - 1] == 2 || PLANSZA[w + 1][k - 1] == 4) && (PLANSZA[w + 2][k - 2] == 0))))
					stan_przed++;
			}
	}

	if (gracz == 2) {
		for (int w = 0; w < 8; w++)
			for (int k = 0; k < 8; k++) {

				if ((PLANSZA[w][k] == 2) && (((PLANSZA[w + 1][k + 1] == 3 || PLANSZA[w + 1][k + 1] == 6) && (PLANSZA[w + 2][k + 2] == 0)) || ((PLANSZA[w + 1][k - 1] == 3 || PLANSZA[w + 1][k - 1] == 6) && (PLANSZA[w + 2][k - 2] == 0))))
					stan_przed++;

				//   X do przodu
				if ((PLANSZA[w][k] == 4) && (((PLANSZA[w + 1][k + 1] == 3 || PLANSZA[w + 1][k + 1] == 6) && (PLANSZA[w + 2][k + 2] == 0)) || ((PLANSZA[w + 1][k - 1] == 3 || PLANSZA[w + 1][k - 1] == 6) && (PLANSZA[w + 2][k - 2] == 0))))
					stan_przed++;

				//   X do tyłu
				if ((PLANSZA[w][k] == 4) && (((PLANSZA[w - 1][k + 1] == 3 || PLANSZA[w - 1][k + 1] == 6) && (PLANSZA[w - 2][k + 2] == 0)) || ((PLANSZA[w - 1][k - 1] == 3 || PLANSZA[w - 1][k - 1] == 6) && (PLANSZA[w - 2][k - 2] == 0))))
					stan_przed++;

			}
	}
}


bool warunek_wygranej(int PLANSZA[MAX_W][MAX_K], int gracz) {

	int pionki_o = 0, pionki_x = 0, ruch_o = 0, ruch_x = 0;
	bool ruch_bo = false, ruch_bx = false;

	for(int w = 0 ; w < 8 ; w++)
		for (int k = 0; k < 8; k++) {

			if (PLANSZA[w][k] == 2 || PLANSZA[w][k] == 4) {              // sprawdzamy ilosc pionkow oraz mozliwe ruchy tych pionkow
				pionki_x++;
				ruch_bx = spr_mozliwosci_ruchu(gracz, PLANSZA, w, k);
				if (ruch_bx == true) ruch_x++;
			}

			if (PLANSZA[w][k] == 3 || PLANSZA[w][k] == 6) {
				pionki_o++;
				ruch_bo = spr_mozliwosci_ruchu(gracz, PLANSZA, w, k);
				if (ruch_bo == true) ruch_o++;
			}
		}

	if (pionki_x == 0 || ruch_x == 0) {
		cout << "Gratulacje! Gracz  o  wygrał!" << endl;
		return true;
	}

	if (pionki_o == 0 || ruch_o == 0) {
		cout << "Gratulacje! Gracz  x  wygrał" << endl;
		return true;
	}

	if (pionki_o != 0 || pionki_x != 0) return false;
}


void ruch_zwykly_trans(int& s, int wp, int kp, int wr, int kr, int PLANSZA[MAX_W][MAX_K], int gracz) {

	if (gracz == 3 && (((wp - 1) == wr) && (((kp + 1) == kr) || ((kp - 1) == kr)))) {

		PLANSZA[wp][kp] = 0;

		if (wr == 0) PLANSZA[wr][kr] = 6;         // przemiana o w O
		else PLANSZA[wr][kr] = 3;

		s++;
	}
	if (gracz == 2 && (((wp + 1) == wr) && (((kp + 1) == kr) || ((kp - 1) == kr)))) {

		PLANSZA[wp][kp] = 0;

		if (wr == 7) PLANSZA[wr][kr] = 4;
		else PLANSZA[wr][kr] = 2;

		s++;
	}
	if (gracz == 3 && PLANSZA[wp][kp] == 6 && (((wp + 1) == wr || (wp - 1) == wr) && (((kp + 1) == kr) || ((kp - 1) == kr)))) {

		PLANSZA[wp][kp] = 0;
		PLANSZA[wr][kr] = 6;
		s++;
	}
	if (gracz == 2 && PLANSZA[wp][kp] == 4 && ((((wp - 1) == wr) || ((wp + 1) == wr)) && (((kp + 1) == kr) || ((kp - 1) == kr)))) {

		PLANSZA[wp][kp] = 0;
		PLANSZA[wr][kr] = 4;
		s++;
	}

}


void bicie_trans(int gracz,int PLANSZA[MAX_W][MAX_K],int wp,int kp,int wb,int kb,int& k, int& u) {

	if (gracz == 3 && (PLANSZA[wb + 1][kb + 1] == 2 || PLANSZA[wb + 1][kb + 1] == 4) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 3) {

		PLANSZA[wp][kp] = 0;

		if(wb == 0) PLANSZA[wb][kb] = 6;   //dojscie do konca planszy i przemiana
		else PLANSZA[wb][kb] = 3;

		PLANSZA[wb + 1][kb + 1] = 0;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false) {
			k++, gracz = 2, u = 0;
		}
		else {                             // wielokrotne bicie
			k++; u++;
		}
	}
	if (gracz == 3 && (PLANSZA[wb + 1][kb - 1] == 2 || PLANSZA[wb + 1][kb - 1] == 4) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 3) {

		PLANSZA[wb + 1][kb - 1] = 0;
		PLANSZA[wp][kp] = 0;

		if (wb == 0) PLANSZA[wb][kb] = 6;
		else PLANSZA[wb][kb] = 3;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false){
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}
	if (gracz == 2 && (PLANSZA[wb - 1][kb + 1] == 3 || PLANSZA[wb - 1][kb + 1] == 6) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 2) {

		PLANSZA[wb - 1][kb + 1] = 0;
		PLANSZA[wp][kp] = 0;

		if (wb == 7) PLANSZA[wb][kb] = 4;
		else PLANSZA[wb][kb] = 2;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false){
			k++, gracz = 3;
		}
		else {
			k++; u++;
		}
	}

	if (gracz == 2 && (PLANSZA[wb - 1][kb - 1] == 3 || PLANSZA[wb - 1][kb - 1] == 6) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 2) {

		PLANSZA[wb - 1][kb - 1] = 0;
		PLANSZA[wp][kp] = 0;

		if (wb == 7) PLANSZA[wb][kb] = 4;
		else PLANSZA[wb][kb] = 2;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false){
			k++, gracz = 3;
		}
		else {
			k++; u++;
		}
	}

	bicie_trans_O(gracz, PLANSZA, wp, kp, wb, kb, k, u);

	bicie_trans_X(gracz, PLANSZA, wp, kp, wb, kb, k, u);
}


void bicie_trans_O(int gracz, int PLANSZA[MAX_W][MAX_K], int wp, int kp, int wb, int kb, int& k, int& u) {

	if (gracz == 3 && (PLANSZA[wp + 1][kp - 1] == 2 || PLANSZA[wp + 1][kp - 1] == 4) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 6) {

			PLANSZA[wp][kp] = 0;
			PLANSZA[wb][kb] = 6;
			PLANSZA[wp + 1][kp - 1] = 0;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false) {
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}

	if (gracz == 3 && (PLANSZA[wp + 1][kp + 1] == 2 || PLANSZA[wp + 1][kp + 1] == 4) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 6) {

			PLANSZA[wp + 1][kp + 1] = 0;
			PLANSZA[wp][kp] = 0;
			PLANSZA[wb][kb] = 6;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false){
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}

	if (gracz == 3 && (PLANSZA[wp - 1][kp + 1] == 2 || PLANSZA[wp - 1][kp + 1] == 4) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 6) {

			PLANSZA[wp - 1][kp + 1] = 0;
			PLANSZA[wp][kp] = 0;
			PLANSZA[wb][kb] = 6;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false){
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}

	if (gracz == 3 && (PLANSZA[wp - 1][kp - 1] == 2 || PLANSZA[wp - 1][kp - 1] == 4) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 6) {

			PLANSZA[wp - 1][kp - 1] = 0;
			PLANSZA[wp][kp] = 0;
			PLANSZA[wb][kb] = 6;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false) {
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}

}


void bicie_trans_X(int gracz, int PLANSZA[MAX_W][MAX_K], int wp, int kp, int wb, int kb, int& k, int& u) {

	if (gracz == 2 && (PLANSZA[wp + 1][kp - 1] == 3 || PLANSZA[wp + 1][kp - 1] == 6) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 4) {

			PLANSZA[wp][kp] = 0;
			PLANSZA[wb][kb] = 4;
			PLANSZA[wp + 1][kp - 1] = 0;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false) {
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}

	if (gracz == 2 && (PLANSZA[wp + 1][kp + 1] == 3 || PLANSZA[wp + 1][kp + 1] == 6) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 4) {

			PLANSZA[wp + 1][kp + 1] = 0;
			PLANSZA[wp][kp] = 0;
			PLANSZA[wb][kb] = 4;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false) {
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}
	if (gracz == 2 && (PLANSZA[wp - 1][kp + 1] == 3 || PLANSZA[wp - 1][kp + 1] == 6) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 4) {

			PLANSZA[wp - 1][kp + 1] = 0;
			PLANSZA[wp][kp] = 0;
			PLANSZA[wb][kb] = 4;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false) {
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}

	if (gracz == 2 && (PLANSZA[wp - 1][kp - 1] == 3 || PLANSZA[wp - 1][kp - 1] == 6) && PLANSZA[wb][kb] == 0 && PLANSZA[wp][kp] == 4) {

			PLANSZA[wp - 1][kp - 1] = 0;
			PLANSZA[wp][kp] = 0;
			PLANSZA[wb][kb] = 4;

		if (szuk_wroga(PLANSZA, wb, kb, gracz) == false) {
			k++, gracz = 2;
		}
		else {
			k++; u++;
		}
	}
}


void the_library_is_open(int X, int Y, int& wiersz, int& kolumna) {
	switch (X)
	{
		case 'A': wiersz = 0; break;
		case 'B': wiersz = 1; break;
		case 'C': wiersz = 2; break;
		case 'D': wiersz = 3; break;
		case 'E': wiersz = 4; break;
		case 'F': wiersz = 5; break;
		case 'G': wiersz = 6; break;
		case 'H': wiersz = 7; break;
		case 'a': wiersz = 0; break;
		case 'b': wiersz = 1; break;
		case 'c': wiersz = 2; break;
		case 'd': wiersz = 3; break;
		case 'e': wiersz = 4; break;
		case 'f': wiersz = 5; break;
		case 'g': wiersz = 6; break;
		case 'h': wiersz = 7; break;
		case '1': kolumna = 0; break;
		case '2': kolumna = 1; break;
		case '3': kolumna = 2; break;
		case '4': kolumna = 3; break;
		case '5': kolumna = 4; break;
		case '6': kolumna = 5; break;
		case '7': kolumna = 6; break;
		case '8': kolumna = 7; break;
	}

	switch (Y)
	{
		case 'A': wiersz = 0; break;
		case 'B': wiersz = 1; break;
		case 'C': wiersz = 2; break;
		case 'D': wiersz = 3; break;
		case 'E': wiersz = 4; break;
		case 'F': wiersz = 5; break;
		case 'G': wiersz = 6; break;
		case 'H': wiersz = 7; break;
		case 'a': wiersz = 0; break;
		case 'b': wiersz = 1; break;
		case 'c': wiersz = 2; break;
		case 'd': wiersz = 3; break;
		case 'e': wiersz = 4; break;
		case 'f': wiersz = 5; break;
		case 'g': wiersz = 6; break;
		case 'h': wiersz = 7; break;
		case '1': kolumna = 0; break;
		case '2': kolumna = 1; break;
		case '3': kolumna = 2; break;
		case '4': kolumna = 3; break;
		case '5': kolumna = 4; break;
		case '6': kolumna = 5; break;
		case '7': kolumna = 6; break;
		case '8': kolumna = 7; break;
	}
}
