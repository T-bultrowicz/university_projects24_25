package lotto;
import java.util.ArrayList;

import wyjątki.NullWartość;
import wyjątki.ZłyBlankiet;

public abstract class Weryfikacje implements Lotto {
    
    public static long sumaCyfr(long liczba) {
        long suma = 0;
        while (liczba > 0) {
            suma += liczba % 10;
            liczba /= 10;
        }
        return suma;
    }

    public static Kupon przekształćBlankiet(Blankiet blankiet, 
                    Kolektura k, int nrLosowania) throws ZłyBlankiet {
        if (blankiet == null || k == null) {
            throw new NullWartość("Weryfikacje.przekształćBlankiet()");
        }
        boolean[] anulowane = blankiet.anulowane();
        boolean[][] plTypowane = blankiet.polaTypowane();
        boolean[] ilZakładów = blankiet.ilośćZakładów();
        ArrayList<Integer> zaznaczone = new ArrayList<>();
        int pop_zaznaczeń = 0;
        Typowanie[] typowane = new Typowanie[ILOŚĆ_TYPÓW];
        for(int i = 0; i < ILOŚĆ_TYPÓW; i++) {
            for(int j = 0; j < ILOŚĆ_LICZB; j++) {
                if(plTypowane[i][j]) {
                   zaznaczone.add(j + 1);
                }
            }
            if(!anulowane[i] && zaznaczone.size() == TYPOWANYCH_LICZB) {
                try {
                typowane[pop_zaznaczeń++] = new Typowanie(zaznaczone.stream().
                                    mapToInt(Integer::intValue).toArray());
                } catch(Exception e) {
                    // Wymagane przez kompilator, nie może się zdarzyć.    
                }
            }
            zaznaczone.clear();
        }
        int zakłady = 0;
        for(int i = 0; i < ILOŚĆ_ZAKŁADÓW; i++) {
            if(ilZakładów[i] && zakłady == 0) {
                zakłady = i + 1;
            } else if(ilZakładów[i]) {
                throw new ZłyBlankiet("2 zaznaczenia w il losowań!", blankiet);
            }
        }
        if(zakłady == 0) zakłady++;
        if(pop_zaznaczeń == 0) {
            throw new ZłyBlankiet("Zero poprawnych zaznaczeń", blankiet);
        }
        Typowanie[] finalTyp = new Typowanie[pop_zaznaczeń];
        System.arraycopy(typowane, 0, finalTyp, 0, pop_zaznaczeń);
        return new Kupon(k.nrKolektury(), nrLosowania, zakłady, finalTyp);
    }

    public static int policzTrafienia(Typowanie próba, Losowanie wzorzec) {
        int[] sprawdź = próba.typowaneLiczby();
        int[] poprawne = wzorzec.wylosowane();
        int j, k;
        int trafienia = 0;
        for (j = 0, k = 0; j < sprawdź.length && k < poprawne.length;) {
            if (sprawdź[j] == poprawne[k]) {
                trafienia++;
                j++;
                k++;
            } else if (sprawdź[j] < poprawne[k]) {
                j++;
            } else {
                k++;
            }
        }
        return trafienia;
    }

    public static boolean dobrzePodaneLiczby(int[] liczby) {
        if(liczby == null || liczby.length != TYPOWANYCH_LICZB) {
            return false;
        }
        for(int i = 0; i < liczby.length; i++) {
            if(liczby[i] < 1 || liczby[i] > ILOŚĆ_LICZB) {
                return false;
            }
            for(int j = i + 1; j < liczby.length; j++) {
                if(liczby[i] == liczby[j]) {
                    return false;
                }
            }
        }
        return true;
    }
}
