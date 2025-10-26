#include <random>
#include <string>
#include <iostream>
#include <climits>
#include <algorithm>

constexpr int MAX_N = 1e3;
constexpr int MAX_Q = 1e3;
constexpr int MIN_VAL = INT_MIN;
constexpr int MAX_VAL = INT_MAX;

std::mt19937 eng;

int rand(int l, int r) {
    return std::uniform_int_distribution<int>{l, r}(eng);
}

int main(int argc, char *argv[]) {
    eng.seed(std::stoi(argv[1]));

    int n = rand(0, MAX_N);
    int q = rand(0, MAX_Q);

    std::cout << n << ' ' << q << '\n';

    for(int i = 1; i <= n; i++) {
        std::cout << rand(MIN_VAL, MAX_VAL) << ' ';
    }

    std::cout << '\n';

    for(int i = 1; i <= q; i++) {
        if(rand(0, 1) == 0 || n == 0) {
            n++;

            std::cout << "+ " << rand(MIN_VAL, MAX_VAL) << '\n';
        }
        else {
            int lo = rand(MIN_VAL, MAX_VAL), hi = rand(MIN_VAL, MAX_VAL);

            if(lo > hi) {
                std::swap(lo, hi);
            }

            std::cout << "? " << rand(0, n - 1) << ' ' << lo << ' ' << hi << '\n';
        }
    }
}