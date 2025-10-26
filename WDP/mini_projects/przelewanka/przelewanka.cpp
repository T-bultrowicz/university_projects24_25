#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

int nwd(int a, int b) {
    if(!b) return a;
    return nwd(b, a % b);
}

bool sprawdz_problem_nwd(const vector<int>& X, const vector<int>& Y) {
    int nwd_x = X[0];
    for(size_t i = 1; i < X.size(); i++) {
        nwd_x = nwd(nwd_x, X[i]);
    }
    for(int j : Y) {
        if(j % nwd_x) return true;
    }
    return false;
}

//hashuje wektor, używana do tworzenia unordered_set wektorów, zapożyczona z CHATGPT
struct Hashprocedure {
    size_t operator()(const vector<int>& v) const {
        size_t res = v.size();
        for (int i = 0; i < (int) v.size(); i++) {
            res ^= hash<int>{}(v[i]) + 0x9e3779b9 + (res << 6) + (res >> 2);
        }
        return res;
    }
};

//sprawdza pelne/puste przypadki
pair<bool,int> sprawdzaj_proste(const vector<int>& X, const vector<int>& Y) {
    int res = 0;
    bool da_sie = false, wszystko = true;
    for(size_t i = 0; i < Y.size(); i++) {
        if(Y[i]==X[i] && Y[i]) res++;
        if(!Y[i] || Y[i] == X[i]) da_sie = true;
        else wszystko = false;
    }
    return (da_sie) ? make_pair(wszystko, res) : make_pair(wszystko, -1);
}

//wrzuca na kolejke nowy stan wypelnienia szklanek razem z parametrami
typedef struct task {
    vector<int> stan;
    int moves;
    int on_place;
} task;

task make_task(vector<int> a, int b, int c) {
    task res;
    res.stan = a;
    res.moves = b;
    res.on_place = c;
    return res;
}

//dodaje do kolejki i setu oraz sprawdza ruchy dolewające
int sprawdz_dolanie(task& t, queue<task>& q, unordered_set<vector<int>, Hashprocedure>& set, const vector<int>& X, const vector <int>& Y) {
    size_t n = X.size();
    for(size_t i = 0; i < n; i++) {
        if(t.stan[i] != X[i]) {
            int mem_stan = t.stan[i], mem_on_place = t.on_place;
            t.moves++;
            t.stan[i] = X[i];
            if(set.find(t.stan) == set.end()) {
                if(t.stan[i] == Y[i]) t.on_place++;
                if(mem_stan == Y[i]) t.on_place--;
                if((size_t) t.on_place == n) return t.moves;
                set.insert(t.stan);
                q.push(t);
            }
            t.stan[i] = mem_stan;
            t.moves--;
            t.on_place = mem_on_place;
        }
    }
    return 0;
}

//dodaje do kolejki i setu oraz sprawdza ruchy wylewające
int sprawdz_wylanie(task& t, queue<task>& q, unordered_set<vector<int>, Hashprocedure>& set, const vector<int>& X, const vector <int>& Y) {
    size_t n = X.size();
    for(size_t i = 0; i < n; i++) {
        if(t.stan[i] != 0) {
            int mem_stan = t.stan[i], mem_on_place = t.on_place;
            t.moves++;
            t.stan[i] = 0;
            if(set.find(t.stan) == set.end()) {
                if(t.stan[i] == Y[i]) t.on_place++;
                if(mem_stan == Y[i]) t.on_place--;
                if((size_t) t.on_place == n) return t.moves;
                set.insert(t.stan);
                q.push(t);
            }
            t.stan[i] = mem_stan;
            t.moves--;
            t.on_place = mem_on_place;
        }
    }
    return 0;
}

//dodaje do kolejki i setu, oraz sprawdza ruchy przelewające
int sprawdz_przelanie(task& t, queue<task>& q, unordered_set<vector<int>, Hashprocedure>& set, const vector<int>& X, const vector <int>& Y) {
    size_t n = X.size();
    for(size_t i = 0 ; i < n; i++) {
        for(size_t j = 0; j < n; j++) {
            if(t.stan[i] != 0 && t.stan[j] != X[j] && i != j) {
                int mem_i = t.stan[i], mem_j = t.stan[j], mem_place = t.on_place;
                t.moves++;
                int ilosc = min(X[j] - t.stan[j], t.stan[i]);
                t.stan[i] -= ilosc, t.stan[j] += ilosc;
                if(set.find(t.stan) == set.end()) {
                    if(t.stan[i] == Y[i]) t.on_place++;
                    if(mem_i == Y[i]) t.on_place--;
                    if(t.stan[j] == Y[j]) t.on_place++;
                    if(mem_j == Y[j]) t.on_place--;
                    if((size_t) t.on_place == n) return t.moves;
                    set.insert(t.stan);
                    q.push(t);
                }
                t.stan[i] = mem_i, t.stan[j] = mem_j, t.on_place = mem_place;
                t.moves--;
            }
        }
    }
    return 0;
}

//sprawdza wszystkie mozliwe przejscia i wrzuca je na q oraz do set, jesli nie pokrywaja sie z setem
//ponadto wykrywa znalezienie juz dojscia do wektora q, i przerywa wtedy proces
int dodaj_sprawdz_ruchy(task& t, queue<task>& q, unordered_set<vector<int>, Hashprocedure>& set, const vector<int>& X, const vector <int>& Y) {
    int res = sprawdz_dolanie(t, q, set, X, Y);
    if(!res) res = sprawdz_wylanie(t ,q, set, X, Y);
    if(!res) res = sprawdz_przelanie(t, q, set, X, Y);
    return res; 
}

int przelej(const vector<int>& X, const vector<int>& Y) {
    size_t n = X.size();
    int res;

    //war brzegowe
    if(!n) return 0;
    auto check = sprawdzaj_proste(X, Y);
    if(check.second == -1) return -1;
    if(check.first) return check.second;
    if(sprawdz_problem_nwd(X, Y)) return -1;

    //poczatkowe struktury danych
    queue<task> q;
    unordered_set<vector<int>, Hashprocedure> set;
    set.insert(vector<int>(n, 0));
    q.push(make_task(vector<int>(n, 0), 0, 0));
    for(size_t i = 0; i < n; i++) {
        if(0 == Y[i]) q.front().on_place++;
    }

    //puszczanie bfs - nie powtarzajac stanow
    while(!q.empty()) {
        auto t = q.front();
        q.pop();
        res = dodaj_sprawdz_ruchy(t, q, set, X, Y);
        if(res) {
            return res;
        }
    }
    return -1;
}

int main() {
    int a, b, c;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    vector<int> szk, ogr;
    for(int i = 0; i < a; i++) {
        if(scanf("%d %d", &b, &c) != 2) {
            return -1;
        }
        szk.push_back(b);
        ogr.push_back(c);
    }
    printf("%d", przelej(szk, ogr));
    return 0;
}

