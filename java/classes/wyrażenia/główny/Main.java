package główny;
import wyrażenia.*;

public class Main {

    public void testuj(Wyrażenie w){
        double x = 4;
        double a = 0.0;
        double b = 10.0;
        int n = 1000;

        System.out.println("w = " + w);
        System.out.println("w(" + x + ") = " + w.oblicz(x));
        System.out.println("w' = " + w.pochodna());
        System.out.println(" całka z w od " + a + " do " + b + " z " +
                           n + " krokami = " + w.całka(a, b, n));
    }

    public void testujMnożenie() {
        testuj(new Pomnóż(new Dodaj(new Stała(-4), new Stała(5)), new Zmienna()));
        testuj(new Pomnóż(new Dodaj(new Stała(0), new Stała(1)), new Zmienna()));
        testuj(new Pomnóż(new Stała(1), 
                            new Pomnóż(new Zmienna(), new Zmienna())));
        testuj(new Dodaj(new Pomnóż(new Zero(), new Zmienna())
                            , new Dodaj(new Stała(0), 
                                            new Cos(new Zmienna()))));
        Wyrażenie w = new Pomnóż(new Stała(0), new Zmienna());
        for(int i = 0; i < 10; i++) {
            w = new Pomnóż(new Zmienna(), w);
        }
        testuj(w);
    }

    public static void main(String[] args) {
        System.out.println("Hej świecie wyrażeń!");

        Main m = new Main();
        m.testuj(new Stała(3.14));
        m.testuj(new Zmienna());
        m.testuj(new Dodaj(new Stała(3.14), new Zmienna()));
        m.testuj(new Pomnóż(new Cos(new Zmienna()),
                            new Sin(new Stała(3.14))
                            )
                );
        m.testuj(new Zero().dodaj(new Zmienna()));
        m.testuj(new Zmienna().dodaj(new Zero()));
        m.testuj(new Stała(1).dodaj(new Stała(2)));


        m.testujMnożenie();
        System.out.println("Koniec");

    }
}