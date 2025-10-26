#include<bits/stdc++.h>
using namespace std;

int r_nar(const vector<vector <int>>& amp, vector <pair <int,int>>& track, int x, int y, vector <vector <bool>>& visit) {
    if(x == amp.size() - 1 && y == amp[0].size() - 1) {
        track.push_back({amp.size() - 1, amp[0].size() - 1});
        return 0;
    }
    vector<pair <int,int>> poss; 
    int maks = -1;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    for(int i = 0; i < 4; i++) {
        if((x + dx[i] >= 0) && (x + dx[i] < amp.size()) && (y + dy[i] >= 0) && (y + dy[i] < amp[0].size())) {
            if(!visit[x + dx[i]][y + dy[i]] && amp[x + dx[i]][y + dy[i]] < amp[x][y]) {
                visit[x + dx[i]][y + dy[i]] = true;
                int d = r_nar(amp, track, x + dx[i], y + dy[i], visit);
                if(d > maks) {
                    maks = d;
                    poss = track;
                }
                track.clear();
            }
        }
    }
    track = poss;
    track.push_back({x, y});
    return (maks == -1) ? -1 : maks + 1;
}


int narty(const vector<vector <int>>& amp, vector<vector <bool>>& course) {
    vector <pair <int,int>> track;
    vector <vector <bool>> visit;
    visit.resize(amp.size());
    for(int i = 0; i < amp.size(); i++) {
        for(int j = 0; j < amp[0].size(); j++) {
            visit[i].push_back(false);
        } 
    }
    visit[0][0] = true;
    int res = r_nar(amp, track, 0, 0, visit);
    for(pair<int,int> a : track) {
        course[a.first][a.second] = 1;
    }
    return res;
}

int main() {
    int a, b, c;
    if(scanf("%d %d", &a, &b) != 2) {
        return -1;
    }
    vector <vector <int>> amp;
    vector <vector <bool>> course;
    amp.resize(a);
    course.resize(a);
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            if(scanf("%d", &c) != 1) {
                return -1;
            }
            amp[i].push_back(c);
            course[i].push_back(0);
        }
    }
    int ll = narty(amp, course);
    printf("%d\n", ll);
    if(ll != -1) {
        for(int i = 0; i < a; i++) {
            for(int j = 0; j < b; j++) {
                printf("%d ", course[i][j] ? 1 : 0);
            }
            printf("\n");
        }
    }
    return 0;
}