#include<bits/stdc++.h>
using namespace std;

typedef struct tile {
    int id;
    int x, y;
    bool type, visited;
    int cluster_value;
} tile;

tile make_tile(int id_, int x_, int y_, bool type_, bool visited_, int cluster_value_) {
    tile a = {
        .id = id_,
        .x = x_,
        .y = y_,
        .type = type_,
        .visited = visited_,
        .cluster_value = cluster_value_,
    };
    return a;
}

//napelnia sasiadujacymi blokami
void saturate(int s, vector<pair<int,int>>& t, vector<tile>& res) {
    tile til;
    for(int k = 0; k < s; k++) {
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                til = make_tile(-1, t[k].first + i, t[k].second + j, false, false, -1);
                if(!i && !j) {
                    til.type = true;
                    til.id = k;
                }
                res.push_back(til);
            }
        }
    }
    return;
}

vector<tile> counting_sort_1D(bool sorting_by_x, const vector<tile>& to_be_sorted, int s) {
    vector<int> count(2 * s + 3, 0);
    vector<tile> printout(to_be_sorted.size());
    for(const auto& a : to_be_sorted) {
        count[sorting_by_x ? a.x + s + 1 : a.y + s + 1]++;
    }
    for(int i = 1; i < 2 * s + 3; i++) {
        count[i] += count[i - 1];
    }
    for(int i = to_be_sorted.size() - 1; i >= 0; i--) {
        int val = sorting_by_x ? to_be_sorted[i].x + s + 1 : to_be_sorted[i].y + s + 1;
        printout[--count[val]] = to_be_sorted[i];
    }
    return printout;
}

vector<tile> counting_sort(bool x_before_y, const vector<tile>& to_be_sorted, int s) {
    vector<tile> partial = counting_sort_1D(!x_before_y, to_be_sorted, s);
    return counting_sort_1D(x_before_y, partial, s);
}

vector<tile> remove_repetitions_gv_ids(vector<tile>& t, int s) {
    int n = t.size(), id_giver = s;
    tile to_add;
    vector<tile> res;
    for(int i = 0; i < n; i++) {
        to_add = t[i];
        while(i + 1 < n && t[i].x == t[i + 1].x && t[i].y == t[i + 1].y) {
            if(t[i + 1].type) to_add = t[i + 1];
            i++;
        }
        res.push_back(to_add);
    }
    for(int i = 0; i < res.size(); i++) {
        if(!res[i].type) {
            res[i].id = id_giver++;
        }
    }
    return res;
}

void add_graph_neighs(vector<vector <int>>& graph, vector<tile>& tab, bool which_way_x) {
    for(int i = 0; i < tab.size() - 1; i++) {
        if(which_way_x && tab[i].x == tab[i + 1].x && tab[i].y + 1 == tab[i + 1].y) {
            graph[tab[i].id].push_back(tab[i + 1].id);
            graph[tab[i + 1].id].push_back(tab[i].id);
        } else if(!which_way_x && tab[i].y == tab[i + 1].y && tab[i].x + 1 == tab[i + 1].x) {
            graph[tab[i].id].push_back(tab[i + 1].id);
            graph[tab[i + 1].id].push_back(tab[i].id);;            
        }
    }
    return;
}

void pin_to_ids(vector<tile*>& id_to_obj, vector<tile>& obj) {
    id_to_obj.resize(obj.size());
    for(int i = 0; i < obj.size(); i++) {
        id_to_obj[obj[i].id] = &obj[i];
    }
    return;
}

int bfs_through_integrity(vector <vector <int>>& graph, vector <tile*>& id_to_obj, queue <int>& integrity, int cluster_count) {
    int found_clusters = cluster_count;
    queue <int> to_visit;
    bool first_time = true;
    while(!integrity.empty()) {
        int a = integrity.front();
        integrity.pop();
        if(id_to_obj[a]->visited) {
            id_to_obj[a]->visited = false;
            to_visit.push(a);
            id_to_obj[a]->cluster_value = first_time ? 0 : ++found_clusters;
        }
        while(!to_visit.empty()) {
            int a = to_visit.front();
            to_visit.pop();
            for(int k : graph[a]) {
                if(id_to_obj[k]->visited && !id_to_obj[k]->type) {
                    id_to_obj[k]->visited = false;
                    to_visit.push(k);
                    id_to_obj[k]->cluster_value = first_time ? 0 : found_clusters;
                }
            }
        }
        if(first_time) first_time = false;
    }
    return found_clusters - cluster_count;
}

void bfs_name_clusters(vector<vector<int>>& graph, vector<bool>& is_cluster_accurate, vector<tile*>& id_to_obj, int s) {
    int cluster_count = 0;
    queue <int> integrity, to_visit;

    //loop to find integrities
    for(int i = s; i < id_to_obj.size(); i++) {

        //catching integrity
        if(!id_to_obj[i]->type && id_to_obj[i]->cluster_value == -1) {
            integrity.push(i);
            to_visit.push(i);
            id_to_obj[i]->visited = true;
        }
        while(!to_visit.empty()) {
            int a = to_visit.front();
            to_visit.pop();
            for(int k : graph[a]) {
                if(!id_to_obj[k]->visited) {
                    id_to_obj[k]->visited = true;
                    to_visit.push(k);
                    if(!id_to_obj[k]->type) integrity.push(k);
                }
            }
        }

        //running bfs trough it to name cluster
        if(!integrity.empty()) cluster_count += bfs_through_integrity(graph, id_to_obj, integrity, cluster_count);
    }
    is_cluster_accurate.assign((unsigned) cluster_count + 1, true);
    return;
}

bool exists_null(vector< vector <int>>& graph, int i, vector <tile*> id_to_obj) {
    for(int k : graph[i]) {
        if(!id_to_obj[k]->type && !id_to_obj[k]->cluster_value) {
            return true;
        }
    }
    return false;
}

int exists_other_accurate(vector< vector <int>>& graph, int i, vector<bool>& ica, vector <tile*> id_to_obj) {
    for(int k : graph[i]) {
        if(!id_to_obj[k]->type && ica[id_to_obj[k]->cluster_value] && id_to_obj[k]->cluster_value) {
            return k;
        }
    }
    return 0;
}

int solve_kartka(int s, vector<pair<int,int>>& t) {
    //inicjalizacja
    int res = -1;
    vector <tile> pre_sorted;
    vector <tile> sorted;
    vector <vector <int>> neighs_graph;
    vector <bool> is_cluster_accurate;
    vector <tile*> id_to_object;

    //preprocess - sortowanie po wspolrzednych
    saturate(s, t, pre_sorted);
    sorted = counting_sort(true, pre_sorted, s);
    sorted = remove_repetitions_gv_ids(sorted, s);
    neighs_graph.resize(sorted.size());
    add_graph_neighs(neighs_graph, sorted, true);
    sorted = counting_sort(false, sorted, s);
    add_graph_neighs(neighs_graph, sorted, false);

    //znajdywanie clusterów
    pin_to_ids(id_to_object, sorted);
    bfs_name_clusters(neighs_graph, is_cluster_accurate, id_to_object, s);

    //zapisywanie zmian
    for(int i = s - 1; i >= 0; i--) {
        int val = exists_other_accurate(neighs_graph, i, is_cluster_accurate, id_to_object);
        if(exists_null(neighs_graph, i, id_to_object) && val) {
            is_cluster_accurate[id_to_object[val]->cluster_value] = false;
            res = i;
        }
    }
    return res;
}

int main() {
    int x, y, z;
    scanf("%d", &x);
    vector <pair<int,int>> cords;
    for(int i = 0; i < x; i++) {
        scanf("%d %d", &y, &z);
        cords.push_back(make_pair(y, z));
    }
    printf("%d", solve_kartka(x, cords));
    return 0;
}