package główny;

import struktury_danych.Stos;
import struktury_danych.ZłyRozmiar;
import wyrażenia.BłędneWyrażenie;
import wyrażenia.DzieleniePrzezZero;
import wyrażenia.ONP;
import wyrażenia.ZbytZłożoneWyrażenie;

public class Main {
 
    void test0() throws ZłyRozmiar {
        Stos st = new Stos(-13);
    }

    void test1() throws ZłyRozmiar {
        int n = 3;
        Stos st = new Stos(n);
        for (int i = 0; i < n+1; i++) {
            try {
                st.wstaw(i);
            } catch (Exception e) {
                System.out.println("Nie udało się wstawić " + i);
            }
        }



    }
    public static void main(String[] args) throws ZłyRozmiar {
        System.out.println("Hej ONP!");

        Main m = new Main();
        try {
            m.test0();
            m.test1();            
        } catch (ZłyRozmiar e) {
            System.out.println(e);
        }
        ONP onp = new ONP();

        try {
            System.out.println(onp.policz("23+4*"));
        }
        catch (ZbytZłożoneWyrażenie | BłędneWyrażenie | DzieleniePrzezZero e) {
                System.out.println("Nie udało się policzyć tego wyrażenia");
        }

        System.out.println("Koniec!");
    }
}