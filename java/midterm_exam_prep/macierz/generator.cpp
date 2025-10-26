#include <iostream>
#include <random>

double losujDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

int main() {
    int r1, r2, rW;
    std::cin >> r1 >> r2 >> rW;
    std::cout << r1 << " " << r2 << " " << rW << "\n";
    for(int i = 0; i < r1; i++) {
        for(int j = 0; j < rW; j++) {
            std::cout << losujDouble(0, 200) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for(int i = 0; i < rW; i++) {
        for(int j = 0; j < r2; j++) {
            std::cout << losujDouble(0, 200) << " ";
        }
        std::cout << "\n";
    }
}