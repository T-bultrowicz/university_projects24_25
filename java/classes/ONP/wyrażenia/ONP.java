package wyrażenia;

import struktury_danych.*;

public class ONP {
    // Klas do wyliczania wartości wyrażeń zapisanych w ONP

    // Dane
    // Techniczna
    // Operacja
    public int policz(String wyrażenieONP) throws ZłyRozmiar,
            ZbytZłożoneWyrażenie,
            BłędneWyrażenie,
            DzieleniePrzezZero {
        // Oblicza wartość zadanego wyrażenie w ONP,
        // zakładamy, że:
        //   - liczby są jednocyfrowe,
        //   - operatory to +,-,*,/  (/ jako dzielenie całkowite),
        //
        //   - wyrażenie nie zawiera białych znaków (tylko cyfry i operatory)
        // Stos stos = new Stos(wyrażenieONP.length() / 4); // dzielenie przez 4 żeby coś się działo
        Stos stos = new Stos(wyrażenieONP.length()); // dzielenie przez 4 żeby coś się działo
        for (int i = 0; i < wyrażenieONP.length(); i++) {
            char zn = wyrażenieONP.charAt(i);
            if (zn >= '0' && zn <= '9') {
                // liczba
                try {
                    stos.wstaw(zn - '0'); // wstawiamy liczbę na stos
                } catch (BrakMiejsca e) {
                    throw new ZbytZłożoneWyrażenie(wyrażenieONP);
                }
            } else {
                // operator
                int a, b;
                try {
                    b = stos.NaWierzchołku();
                    stos.pobierz();
                    a = stos.NaWierzchołku();
                    stos.pobierz();
                } catch (PustyStos e) {
                    throw new BłędneWyrażenie(wyrażenieONP);
                }
                try {
                    switch (zn) {
                        case '+':
                            stos.wstaw(a + b);
                            break;
                        case '-':
                            stos.wstaw(a - b);
                            break;
                        case '*':
                            stos.wstaw(a * b);
                            break;
                        case '/':
                            if (b == 0)
                                throw new DzieleniePrzezZero(wyrażenieONP);
                            else
                                stos.wstaw(a / b);
                            break;
                        default:
                            throw new BłędneWyrażenie(wyrażenieONP + " zawiera niedozwolony znak " + zn);
                    }
                } catch (BrakMiejsca e) {
                    throw new RuntimeException(e);
                }

            } // else


        } //for

        try {
            int wynik = stos.NaWierzchołku();
            stos.pobierz();
            if (!stos.czyPusty())
                throw new BłędneWyrażenie(wyrażenieONP);
            else
                return wynik;
        } catch (PustyStos e) {
            throw new BłędneWyrażenie(wyrażenieONP);
        }
    } // policz
} // ONP


