package lotto;

import java.util.Random;

import wyjątki.SpozaZasięgu;
import wyjątki.UjemnaWartość;

import java.util.Arrays;

public abstract class MaszynaLosująca implements Lotto {
    
    // dane
    static private Random rng = new Random();

    // techniczne

    static public int przedział(int from, int to) {
        if(from < 0 || to < 0)
            throw new UjemnaWartość("MaszynaLosująca.przedział()");
        if (from > to) {
            throw new SpozaZasięgu(from, to, 
            "MaszynaLosująca.przedział(), pierwszy parametr musi być krótszy");
        }
        return (rng.nextInt(to - from + 1) + from);
    }

    static public int losowaCyfra() {
        return przedział(0, 9);
    }

    static public int[] losujLiczby(int ilość, int zakresDół, int zakresGóra) {
        if (ilość <= 0 || zakresDół < 0) {
            throw new UjemnaWartość("MaszynaLosująca.losujLiczby()");
        }
        if (zakresDół >= zakresGóra) {
            throw new SpozaZasięgu(zakresDół, zakresGóra, 
            "MaszynaLosująca.losujLiczby(), drugi parametr musi być" + 
                                        " mnijeszy niż trzeci");
        }
        int[] liczby = new int[ilość];
        boolean temp;
        for (int i = 0; i < ilość; i++) {
            do {
                temp = false;
                liczby[i] = MaszynaLosująca.przedział(zakresDół, zakresGóra);
                for (int j = 0; j < i; j++) {
                    if (liczby[i] == liczby[j]) {
                        temp = true;
                        break;
                    }
                }
            } while(temp);
        }
        Arrays.sort(liczby);
        return liczby; 
    }

    static public Blankiet losowyBlankiet() {
        Blankiet blankiet = new Blankiet();
        int ilośćTypów = przedział(1, ILOŚĆ_TYPÓW);
        int ilośćZakładów = przedział(1, ILOŚĆ_ZAKŁADÓW);
        blankiet.zaznaczIlośćZakładów(ilośćZakładów);

        for(int i = ilośćTypów + 1; i < ILOŚĆ_TYPÓW; i++) {
            blankiet.zaznaczAnuluj(i);
        }

        for(int i = 0; i < ilośćTypów; i++) {
            int[] t = losujLiczby(TYPOWANYCH_LICZB, 1, ILOŚĆ_LICZB);
            for(int a : t) {
                blankiet.zaznaczTyp(i + 1, a);
            }
        }
        return blankiet;
    }
}
