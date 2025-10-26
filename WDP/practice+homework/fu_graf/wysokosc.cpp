#include<bits/stdc++.h>
using namespace std;

typedef struct pole {
    int wys;
    int kor_x, kor_y;
    bool visit;
    pole(int a, int b, int c, bool d) {
        wys = a, kor_x = b, kor_y = c, visit = d;
    }
} pole;

struct compare {
    bool operator()(pole const& p1, pole const&p2) {
        return p1.wys > p2.wys;
    }
};

int wysokosc(const vector <vector <int>>& amp) {
    int x = amp.size(), y = amp[0].size();
    if(x == 1 && y == 1) {
        return amp[0][0];
    }
    priority_queue<pole, vector <pole>, compare> kol;
    vector <vector <pole>> mapa;
    mapa.resize(x);
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            pole a(-1, i, j, false);
            mapa[i].push_back(a);
        }
    }
    mapa[0][0].wys = amp[0][0];
    kol.push(mapa[0][0]);
    while(!kol.empty()) {
        pole p = kol.top();
        if(p.kor_x == x - 1 && p.kor_y == y - 1) {
            return p.wys;
        }
        mapa[p.kor_x][p.kor_y].visit = true;
        kol.pop();
        for(int i = -1; i <= 1; i++) {
            if(p.kor_x + i >= 0 && p.kor_x + i < x) {
                if(!mapa[p.kor_x + i][p.kor_y].visit) {
                    mapa[p.kor_x + i][p.kor_y].wys = max(mapa[p.kor_x][p.kor_y].wys, amp[p.kor_x + i][p.kor_y]);
                    kol.push(mapa[p.kor_x + i][p.kor_y]);
                }
            }
        }
        for(int i = -1; i <= 1; i++) {
            if(p.kor_y + i >= 0 && p.kor_y + i < y) {
                if(!mapa[p.kor_x][p.kor_y + i].visit) {
                    mapa[p.kor_x][p.kor_y + i].wys = max(mapa[p.kor_x][p.kor_y].wys, amp[p.kor_x][p.kor_y + i]);
                    kol.push(mapa[p.kor_x][p.kor_y + i]);
                }
            }
        }
    }
    return -69420;
}

bool r_pat(vector <vector <pole>>& mapa, const vector <vector <int>>& amp, vector <pair <int,int>>& kord, int height, int x, int y) {
    if(x == 0 && y == 0) {
        kord.push_back({x,y});
        return true;
    }
    if(x - 1 >= 0) {
        if(!mapa[x - 1][y].visit && amp[x - 1][y] <= height) {
            mapa[x - 1][y].visit = true;
            if(r_pat(mapa, amp, kord, height, x - 1, y)) {
                kord.push_back({x,y});
                return true;
            }
        }
    }
    if(y - 1 >= 0) {
        if(!mapa[x][y - 1].visit && amp[x][y - 1] <= height) {
            mapa[x][y - 1].visit = true;
            if(r_pat(mapa, amp, kord, height, x, y - 1)) {
                kord.push_back({x,y});
                return true;
            }            
        }
    }
    if(x + 1 < amp.size()) {
        if(!mapa[x + 1][y].visit && amp[x + 1][y] <= height) {
            mapa[x + 1][y].visit = true;
            if(r_pat(mapa, amp, kord, height, x + 1, y)) {
                kord.push_back({x,y});
                return true;
            }            
        }
    }
    if(y + 1 < amp[0].size()) {
        if(!mapa[x][y + 1].visit && amp[x][y + 1] <= height) {
            mapa[x][y + 1].visit = true;
            if(r_pat(mapa, amp, kord, height, x, y + 1)) {
                kord.push_back({x,y});
                return true;
            }            
        }
    }
    return false;
}

vector<pair <int, int>> wys_path(const vector <vector <int>>& amp, int height) {
    vector <pair <int,int>> kord;
    kord.push_back({amp.size() - 1, amp[0].size() - 1});
    vector <vector <pole>> mapa;
    mapa.resize(amp.size());
    for(int i = 0; i < amp.size(); i++) {
        for(int j = 0; j < amp[0].size(); j++) {
            pole a(-1, i, j, false);
            mapa[i].push_back(a);
        }
    }
    mapa[amp.size() - 1][amp[0].size() - 1].visit = true;
    r_pat(mapa, amp, kord, height, amp.size() - 1, amp[0].size() - 1);
    return kord;
}

int main() {
    int a, b, c;
    if(scanf("%d %d", &a, &b) != 2) {
        return -1;
    }
    vector <vector <int>> amp;
    amp.resize(a);
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            if(scanf("%d", &c) != 1) {
                return -1;
            }
            amp[i].push_back(c);
        }
    }
    printf("%d\n", wysokosc(amp));
    vector <pair <int,int>> read = wys_path(amp, wysokosc(amp));
    bool print[a][b];
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            print[i][j] = 0;
        }
    }
    for(int j = 0; j < read.size();j++) {
        print[read[j].first][read[j].second] = 1;
    }
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            printf("%d ", print[i][j]);
        }
        printf("\n");
    }
    return 0;
}