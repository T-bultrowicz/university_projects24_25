 #!/bin/bash

# Sprawdzenie liczby argumentów
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <number_of_tests>"
    exit 1
fi

# Pobranie liczby testów
num_tests=$1

# Ścieżki do programów
GENERATOR="./gen.e"
PRZE="./prze.e"
PRZELEWANKA="./przelewanka.e"

# Sprawdzenie, czy wymagane pliki istnieją
if [ ! -f "$GENERATOR" ] || [ ! -f "$PRZE" ] || [ ! -f "$PRZELEWANKA" ]; then
    echo "Error: One or more required executables ($GENERATOR, $PRZE, $PRZELEWANKA) are missing."
    exit 1
fi

# Iteracja po testach
for ((i=1; ; i++)); do
    echo "Running test #$i..."

    # Generowanie testu
    $GENERATOR $num_tests $i > test.in

    # Uruchamianie programów
    $PRZE < test.in > prze.out
    $PRZELEWANKA < test.in > przelewanka.out

    # Porównywanie wyników
    if diff -q prze.out przelewanka.out > /dev/null; then
        echo "Test #$i: PASSED"
        cat prze.out
    else
        echo "Test #$i: FAILED"
        echo "Input:"
        cat test.in
        echo "prze Output:"
        cat prze.out
        echo "przelewanka Output:"
        cat przelewanka.out
        exit 1
    fi

    # Czyszczenie plików
    rm -f test.in

done

echo "All $num_tests tests passed."

