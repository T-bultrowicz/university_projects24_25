#include<iostream>
#include<fstream>
#include<random>
#include<cstdlib>
using namespace std;

#define ROZMIAR_STRO (int)4096
#define NEW_LINE (int)10
int main(int argc, char* argv[]) {
    if(argc != 2) {
        return 1;
    }
    // random_device rd;
    mt19937 gen(2137);
    uniform_int_distribution<> dist(97, 122);
    ofstream fout("dane.txt", ios::out | ios::trunc);
    ofstream fout2("wzorzec.txt", ios::out | ios::trunc);
    vector <char> jes;
    uint64_t x = atoi(argv[1]);
    cout << "Dla dł pliku = " << x << endl;
    for(uint64_t i = 0; i < x; i++) {
        jes.push_back((char) dist(gen));
        if(i % 40 == 39) jes.push_back((char) 10);
    }
    for(uint64_t i = 0; i < jes.size(); i++) {
        fout << jes[i];
        fout2 << jes[jes.size() - i - 1];
    }   
    fout.close();
    fout2.close();
    return 0;
}