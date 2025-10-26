#!/bin/bash

for ((i=0; i <= 50000; i+=1)); do
    echo "Test #$i"

    # Krok 1: generowanie testu
    ./gen "$i"
    if [ $? -ne 0 ]; then
        echo "Błąd: ./gen $i zakończył się niepowodzeniem"
        exit 1
    fi

    # Krok 2: uruchomienie programu testowanego
    ./freverse dane.txt
    if [ $? -ne 0 ]; then
        echo "Błąd: ./freverse dane.txt zakończył się niepowodzeniem"
        exit 1
    fi

    # Krok 3: porównanie wyników
    if ! diff -q dane.txt wzorzec.txt > /dev/null; then
        echo "Błąd w teście #$i: różnice między dane.txt i wzorzec.txt"
        diff dane.txt wzorzec.txt
        exit 1
    fi
done

echo "Wszystkie testy zakończone sukcesem!"
