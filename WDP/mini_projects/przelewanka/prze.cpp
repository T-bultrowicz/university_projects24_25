/**
 * Zadanie 6: Przelewanka
 *
 * autor: Adam Bęcłowicz
 *        grupa 12
 *
 * code review: Michał Szydło
 *              grupa 14
 */

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <algorithm>

constexpr long long PRIME1 = 47, MOD1 = 998244353;
constexpr long long PRIME2 = 53, MOD2 = 1e9 + 7;

int n;
std::vector<int> x, y;

std::vector<std::pair<long long, long long>> prime_pow;
std::unordered_map<long long, bool> hash_used;

struct State {
    int operations = 0;
    std::vector<int> amount;
    std::pair<long long, long long> hash;

    State(std::vector<int> amounts) {
        amount.resize(n);

        for(int i = 0; i < n; i++) {
            change_amount(i, amounts[i]);
        }
    }

    void change_amount(int idx, int new_amount) {
        hash = {
            (((hash.first - ((amount[idx] * prime_pow[idx].first) % MOD1)) % MOD1) + MOD1) % MOD1, 
            (((hash.second - ((amount[idx] * prime_pow[idx].second) % MOD2)) % MOD2) + MOD2) % MOD2 
        };

        amount[idx] = new_amount;
        
        hash = {
            (hash.first + ((amount[idx] * prime_pow[idx].first) % MOD1)) % MOD1, 
            (hash.second + ((amount[idx] * prime_pow[idx].second) % MOD2)) % MOD2
        };
    }

    State with_amount(int idx, int new_amount) {
        State new_state = *this;
        new_state.change_amount(idx, new_amount);
        
        return new_state;
    }
};

long long pair_hash(std::pair<long long, long long> hash) {
    return (hash.first << 31) + hash.second;
}

void add(std::queue<State> &states, State new_state) {
    if(!hash_used[pair_hash(new_state.hash)]) {
        states.push(new_state);
        states.back().operations++;

        hash_used[pair_hash(new_state.hash)] = true;
    }
}

int solve() {
    std::queue<State> states;
    
    add(states, State(std::vector<int>(n, 0)));
    State target = State(y);

    while(!states.empty()) {
        State state = states.front();
        states.pop();

        if(state.hash == target.hash) {
            return state.operations - 1;
        }

        for(int i = 0; i < n; i++) {
            if(state.amount[i] < x[i]) {
                add(states, state.with_amount(i, x[i]));
            }

            if(state.amount[i] > 0) {
                add(states, state.with_amount(i, 0));
            }

            for(int j = 0; j < n; j++) {
                if(i != j && state.amount[i] > 0 && state.amount[j] < x[j]) {
                    int change = std::min(state.amount[i], x[j] - state.amount[j]);

                    add(states, state
                        .with_amount(i, state.amount[i] - change)
                        .with_amount(j, state.amount[j] + change)
                    );
                }
            }
        }
    }

    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n;

    if(n == 0) {
        std::cout << 0;
        return 0;
    }

    x.resize(n);
    y.resize(n);

    for(int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    int gcd = x[0];
    for(int i = 1; i < n; i++) {
        gcd = std::__gcd(gcd, x[i]);
    }

    if(gcd == 0) {
        std::cout << 0;
        return 0;
    }

    for(int i = 0; i < n; i++) {
        if(y[i] % gcd != 0) {
            std::cout << -1;
            return 0;
        }
    }

    int max = 0;
    bool empty_full = false;

    for(int i = 0; i < n; i++) {
        max = std::max(max, y[i]);
        empty_full |= (y[i] == 0 || y[i] == x[i]);
    }

    if(max > 0 && !empty_full) {
        std::cout << -1;
        return 0;
    }

    prime_pow.push_back({1, 1});
    for(int i = 1; i < n; i++) {
        prime_pow.push_back({
            (prime_pow.back().first * PRIME1) % MOD1, 
            (prime_pow.back().second * PRIME2) % MOD2
        });
    }

    std::cout << solve();
    return 0;
}