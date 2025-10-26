package główny;
import java.util.Random;
import java.util.Arrays;
import tablice.*;

public class Main {

    /* O algorytmie - symukujemy ruch dwóch "piłek" wewnątrz tablicy. Zaczynają
     * ruch w pounkcie rozmiar / 2. Następnie, w każdej iteracji przesuwamy je
     * o tyle pól, ile wynosi ich prędkość (ew. z zwrotem ujemnym), przedtem
     * modyfikując je o wartość odczytywaną z tablicyZLicznikiem - tab. przyspieszeń.
     * Piłki "odbijają się" od brzegów tablicy, wtedy zmieniamy zwrot prędkości.
     */
    static Random rng = new Random();


    public int[] ustalPozycje(int x, int v, int size) {
        if(size == 1) return new int[]{0, 1};
        if(v < 0) {
            if(x + v < 0) {
                v = -v - x;
                x = 0;
                int t[] = ustalPozycje(x, v, size);
                return new int[]{t[0], 0-t[1]};
            }
        } else {
            if(x + v >= size) {
                v -= (size - x - 1);
                int flips = v / (size - 1);
                int move = v % (size - 1);
                if((flips & 1) == 0) {
                    return new int[]{size - 1 - move, -1};
                } else {
                    return new int[]{move, 1};
                }
            }
        }
        return new int[]{x + v, 1};
    }

    public void symulacjaDla(int rozmiar, int predkosc, int[] przyspieszenia) 
                                                throws ZłyIndeks {
        assert rozmiar > 0 : "Rozmiar tablicy musi być większy od 0";
        assert przyspieszenia != null : "Tablica przyspieszeń nie może być pusta";
        assert przyspieszenia.length == rozmiar : "Zły rozmair tablicy przyspieszeń";

        TablicaZLicznikami<Integer> tab = new TablicaZLicznikami<>(rozmiar);
        for(int k = 0; k < tab.dajRozmiar(); k++) {
            tab.ustaw(k, przyspieszenia[k]);
        }
        int predkosc1 = predkosc;
        int mem = predkosc1;
        int predkosc2 = predkosc1 * -1;
        int pozycja1 = rozmiar / 2, pozycja2 = rozmiar / 2; 
        for(int j = 0; j < 4 * rozmiar; j++) {
            predkosc1 += tab.daj(pozycja1);
            predkosc2 += tab.daj(pozycja2);
            int[] t = ustalPozycje(pozycja1, predkosc1, rozmiar);
            pozycja1 = t[0];
            predkosc1 *= t[1];
            t = ustalPozycje(pozycja2, predkosc2, rozmiar);
            pozycja2 = t[0];
            predkosc2 *= t[1];
        }
        System.out.print("predkosc startowa - " + mem + " {");
        for(int j = 0; j < rozmiar; j++) {
            System.out.print(tab.dajLicznikOdczytów(j) + ", ");
        }
        System.out.print("\b\b}\n");       
    }


    public void testuj1() throws ZłyIndeks {
        System.out.println("test1\n");
        int rozmiar = 100;
        int[] przyspiesz = new int[rozmiar];
        // korzystamy z wypełnienia zerami
        for(int i = 0; i < 10; i++) {
            int predkosc = rng.nextInt(rozmiar);
            symulacjaDla(rozmiar, predkosc, przyspiesz);
        }
        System.out.println("\n\n\n\n"); 
    }

    public void testuj2() throws ZłyIndeks {
        System.out.println("test2\n");
        int rozmiar = 1002; // test gdy rozmiar - 1 jest l.pierwszą
        int[] przyspiesz = new int[rozmiar];
        // korzystamy z wypełnienia zerami
        for(int i = 0; i < 3; i++) {
            int predkosc = rng.nextInt(rozmiar);
            symulacjaDla(rozmiar, predkosc, przyspiesz);
        }
        System.out.println("\n\n\n\n");
    }

    public void testuj3() throws ZłyIndeks {
        System.out.println("test3\n");
        int rozmiar = 100;
        int predkosc = 50;
        int[] przyspiesz = new int[rozmiar];
        for(int i = 0; i < rozmiar; i++) {
            przyspiesz[i] = rng.nextInt(4) - 1; // przyspieszenie -1, 0, 1 lub 2
        }

        for(int i = 0; i < 5; i++) {
            symulacjaDla(rozmiar, predkosc, przyspiesz);
        }
        System.out.println("\n\n\n\n");
    }

    public void testuj4() throws ZłyIndeks {
        System.out.println("test4\n");
        int rozmiar = 100;
        int[] przyspiesz = new int[rozmiar];
        Arrays.fill(przyspiesz, 1); // stałe przyspieszenie
        for(int i = 0; i < 5; i++) {
            int predkosc = rng.nextInt(rozmiar / 2);
            symulacjaDla(rozmiar, predkosc, przyspiesz);
        }
        System.out.println("\n\n\n\n");
    } 

    public static void main(String[] args) {
        System.out.println("start\n");
        Main m = new Main();
        try {
            m.testuj1();
            m.testuj2();
            m.testuj3();
            m.testuj4();
        } catch(Exception e) {System.out.println(e);}

        /*  Wnioski z testów:
         * - Rozkład zawsze jest równomierny, jednak w przypadku gdy prędkość stale jest
         * dzielnikiem rozmiaru tabeli - 1, wiele pól odczytu jest równe zero.
         * - Wyjątkiem w równomiernym rozkładzie są brzegi - które asymptotycznie występują
         * dwa razy rzadziej niż pozostałe pola.
         * - Dla przyspieszeń rozkład staje się bardzo losowy.
         */
        System.out.println("end\n");
    }
}
