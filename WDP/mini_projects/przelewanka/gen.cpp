#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    // Sprawdzenie, czy podano odpowiednią liczbę argumentów
    if (argc != 3) {
        std::cerr << "Usage: " << argv[1] << " <number_of_pairs>\n";
        return 1;
    }

    // Pobranie liczby par z argumentów
    int number_of_pairs = std::atoi(argv[1]);

    // Walidacja liczby par
    if (number_of_pairs <= 0) {
        std::cerr << "Error: number_of_pairs must be a positive integer.\n";
        return 1;
    }

    // Inicjalizacja generatora liczb losowych
    std::srand(std::stoi(argv[2]));

    // Wypisanie liczby par
    std::cout << number_of_pairs << "\n";

    // Generowanie i wypisywanie par liczb
    for (int i = 0; i < number_of_pairs; ++i) {
        int a = std::rand() % 20;
        int b = std::rand() % (a + 1);
        std::cout << a << " " << b << "\n";
    }

    return 0;
}