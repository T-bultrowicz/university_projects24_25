#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

// trzyma dane o pierwszych trojkach po lewej i prawej stronie
typedef struct brzegi {
    int lewy[3]; // wartosci lewy
    int prawy[3]; // wartosci prawy
    int h_lewy[3]; // hotele lewy
    int h_prawy[3]; // hotele prawy
} brzegi;

// znajduje min dwoch liczb
int mini(int a, int b) {
    return (a < b) ? a : b;
}

// znajduje max dwoch liczb
int maxi(int a, int b) {
    return (a > b) ? a : b;
}

// tworzy strukture brzegi dla danych zadania
brzegi stworz_brzegi(int s, int* siec, int* odl) {
    brzegi res;

    // tworzenie lewego brzegu
    res.lewy[0] = odl[0];
    res.h_lewy[0] = siec[0];
    int il_roznych = 1;
    for(int i = 1; i < s; i++) {
        if(il_roznych == 1 && siec[i] != res.h_lewy[0]) {
            res.h_lewy[1] = siec[i];
            res.lewy[1] = odl[i];
            il_roznych++;
        } else if(il_roznych == 2 && siec[i] != res.h_lewy[0] && siec[i] != res.h_lewy[1]) {
            res.h_lewy[2] = siec[i];
            res.lewy[2] = odl[i];
            il_roznych++;
            break;
        }
    }
    // warunek autostrady bez trzech sieci hoteli
    if(il_roznych < 3) {
        res.lewy[0] = -1;
        return res;
    }

    // tworzenie prawego brzegu
    res.prawy[2] = odl[s - 1];
    res.h_prawy[2] = siec[s - 1];
    il_roznych = 1;
    for(int j = s - 2; j >= 0; j--) {
        if(il_roznych == 1 && siec[j] != res.h_prawy[2]) {
            res.h_prawy[1] = siec[j];
            res.prawy[1] = odl[j];
            il_roznych++;
        } else if(il_roznych == 2 && siec[j] != res.h_prawy[2] && siec[j] != res.h_prawy[1]) {
            res.h_prawy[0] = siec[j];
            res.prawy[0] = odl[j];
            il_roznych++;
            break;
        }
    }
    return res;
}

// zwraca najblizsza trojke, wykorzystuje przesuwajaca sie trojke hoteli roznych sieci
// korzysta z faktu, ze optymalne rozwiazanie albo jest spojna trojka, albo trojka
// pomiedzy ktorej skrajnymi el. znajduja sie tylko hotele tej samej sieci
int min_odl(int s, int* siec, int* odl) {
    brzegi fala;
    int res = INT_MAX;

    if(s == 0) { // nieladne dane wejsciowe
        return 0;
    }
    // pierwsza trojka specjalnie tworzona
    fala.h_lewy[1] = -1; // na wypadek gdyby undefined, zwraca error
    fala.lewy[2] = -1; // analogicznie
    fala.h_lewy[2] = -1; // analogicznie
    fala.lewy[0] = odl[0];
    fala.h_lewy[0] = siec[0];
    int k = 1, il_roznych = 1;
    int ind_l, ind_p;
    while(k < s) {
        if(il_roznych == 1 && siec[k] != fala.h_lewy[0]) {
            fala.h_lewy[1] = siec[k];
            il_roznych++;
        } else if(il_roznych == 2 && siec[k] != fala.h_lewy[0] && siec[k] != fala.h_lewy[1]) {
            fala.h_lewy[2] = siec[k];
            fala.lewy[2] = odl[k];
            il_roznych++;
            break;
        }
        k++;
    }
    if(il_roznych < 3) { // nie znaleziono 3 roznych elementow
        return 0;
    }

    ind_p = k;
    // dobranie dobrze wszystkich elementow trojki zaczynajacej iteracje po tablicy,
    if(fala.h_lewy[1] == siec[k - 1]) {
        fala.lewy[1] = odl[k - 1];
        while(k >= 1 && fala.h_lewy[1] == siec[k - 1]) {
            k--;
        }
        ind_l = k - 1;
        fala.lewy[0] = odl[k - 1];
    } else {
        fala.h_lewy[0] = fala.h_lewy[1];
        fala.h_lewy[1] = siec[k - 1];
        fala.lewy[1] = odl[k - 1];
        while(k >= 1 && fala.h_lewy[1] == siec[k - 1]) {
            k--;
        }
        ind_l = k - 1;
        fala.lewy[0] = odl[k - 1];
    }

    // update minimum o wszystko co moglo sie wydarzyc przy wybieraniu trojki
    for(int i = ind_l + 1; i < ind_p; i++) {
        res = mini(res, maxi(odl[ind_p] - odl[i], odl[i] - odl[ind_l]));
    }

    // przesuwanie trojki akumulujac potencjalny wynik
    ind_p++;
    while(ind_p < s) {
        if(siec[ind_p] == fala.h_lewy[2]) {
			// skomplikowany przypadek - z optymalizacji niekorzystnych warunkow:
			// wiemy, ze najbliszy mozliwie optymalny przypadek, to dopiero przypadek wykorzystujacy min. dwa nowe elementy,
			// w tym jeden nierowny h_lewy[2] i h_lewy[1]
            k = ind_p;
            while(k < s) {
                if(siec[k] != fala.h_lewy[2] && siec[k] != fala.h_lewy[1]) {
                    break;
                }
                k++;
            }
            if(k == s) {
                break;
            }
            ind_l = k;

            // pierwszy przypadek sieci w srodku
            if(fala.h_lewy[1] == siec[k - 1]) {
				// znalezienie pierwszego wystapienia trzeciej sieci
                while(fala.h_lewy[1] == siec[k - 1]) {
                    k--;
                }
                fala.h_lewy[0] = fala.h_lewy[2];
                fala.lewy[0] = odl[k - 1];

			// drugi przypadek sieci w srodku
            } else {
				// znalezienie pierwszego wystapienia trzeciej sieci
                while(fala.h_lewy[2] == siec[k - 1]) {
                    k--;
                }
                fala.h_lewy[0] = fala.h_lewy[1];
                fala.lewy[0] = odl[k - 1];
            }
            fala.h_lewy[2] = siec[ind_l];
            fala.lewy[2] = odl[ind_l];
            fala.h_lewy[1] = siec[ind_l - 1];
            fala.lewy[1] = odl[ind_l - 1];
            for(int i = k; i < ind_l; i++) {
                res = mini(res, maxi(odl[ind_l] - odl[i], odl[i] - odl[k - 1]));
            }
            ind_p = ind_l;

		// przypadek zamiany srodkowego elementu fali - na pewno nie optymalny, ale konieczny by przejsc dalej
        } else if(siec[ind_p] == fala.h_lewy[1]) {
            fala.h_lewy[1] = fala.h_lewy[2];
            fala.lewy[1] = fala.lewy[2];
            fala.h_lewy[2] = siec[ind_p];
            fala.lewy[2] = odl[ind_p];

        // przypadek nowej sieci lub sieci rownej pierwszemu elementowi - sprawdzamy i przesuwamy
        } else {
            res = mini(res, maxi(odl[ind_p] - fala.lewy[2], fala.lewy[2] - fala.lewy[1]));
            fala.h_lewy[0] = fala.h_lewy[1];
            fala.lewy[0] = fala.lewy[1];
            fala.h_lewy[1] = fala.h_lewy[2];
            fala.lewy[1] = fala.lewy[2];
            fala.h_lewy[2] = siec[ind_p];
            fala.lewy[2] = odl[ind_p];
        }
        ind_p++;
    }
    return res;
}

// zwraca najdalsza trojke, wykorzystuje dwa stale ustalone "brzegi" - skrajne trojki hoteli roznych firm
// poniewaz dla optymalnego rozwiazania co najmniej dwa hotele musza sie znajdowac na przeciwleglych brzegach,
// a trzeciego szuka w czasie liniowym
int max_odl(int s, int* siec, int* odl) {
    if(s == 0) { // nieladne dane wejsciowe
        return 0;
    }
    brzegi pot = stworz_brzegi(s, siec, odl);
    if(pot.lewy[0] == -1) {
        return 0;
    }

    // sprawdza wszystkie kombinacje potencjalnych kandydatow na najlepsza trojke
    // w czasie O(n)
    int res = 0;

    for(int k = 0; k < s; k++) {
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(siec[k] != pot.h_lewy[i] && siec[k] != pot.h_prawy[j] && pot.h_lewy[i] != pot.h_prawy[j]) {
					res = maxi(res, mini(odl[k] - pot.lewy[i], pot.prawy[j] - odl[k]));
				}
			}
		}
    }

    return res;
}



int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    int *siec = malloc((unsigned)a * sizeof(int));
    int *odl = malloc((unsigned)a * sizeof(int));
    for(int i = 0;i < a; i++) {
        if(scanf("%d%d",siec + i, odl + i) != 2) {
            return -1;
        }
    }
    printf("%d %d\n",min_odl(a, siec, odl), max_odl(a, siec, odl));
    free(siec);
    free(odl);
    return 0;
}
