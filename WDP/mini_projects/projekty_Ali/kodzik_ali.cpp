#include<iostream>
#include<cstdio>

using namespace std;

double wzrost, dlugosc_femur, typ_nogi;

int main()
{
    printf("\033[45m");
   cout << "\nJak optymalnie robic przysiady z sztanga?" << endl << endl;
   cout << "\nZmierz swoj wzrost ciala i zapisz wynik" << endl;
   cout << "\nteraz usiadz na krzesle i zmierz dlugosc od konca posladka do przodu kolana, zapisz wynik" << endl;
    cout << "\nPodaj ile masz wzrostu?(cm)" << endl;
    cin >> wzrost;
    cout << "\nPodaj jak dluga jest twoja kosc udowa(cm)?" << endl;
    cin >> dlugosc_femur;
    typ_nogi = (wzrost/dlugosc_femur)* 100;
    cout << endl;
    if (typ_nogi < 25) 
    {
        cout << "masz typ krotkiej kosci udowej" << endl;
        cout << "aby robic optymalne przysiady z sztanga:" << endl;
        cout << "stoj z nogami na szerokosci bioder" << endl;
        cout << "robiac przysiad utrzymuj bardziej wyprostowana sylwetke";
    }
    if (typ_nogi >= 25 && typ_nogi < 30) 
    {
        cout << "masz typ normalny kosci udowej" << endl;
        cout << "aby robic optymalne przysiady z sztanga:" << endl;
        cout << "stoj z nogami na szerokosci barkow" << endl;
        cout << "robiac przysiad utrzymuj lekko pochylona sylwetke";
    }
     if (typ_nogi >= 30)
    {
        cout << "masz typ dlugiej kosci udowej" << endl;
        cout << "aby robic optymalne przysiady z sztanga:" << endl;
        cout << "stoj z nogami na szerokosci barkow" << endl;
        cout << "robiac przysiad utrzymuj bardziej pochylona sylwetke";
    }

    cout << "\nteraz mozesz robic przysiady optymalnie dla twojego typu ciala!" << endl;
    cout << "\npowodzenia w treningu!" << endl;
    printf("\033[0m");
    return 0;
}


