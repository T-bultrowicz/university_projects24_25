package glowny;

import lotto.*;

public class Main {

    public static final int MINKW = 3000;
    public static final int MAXKW = 300000;
    public static void wykonajTest() {
        System.out.println("Start!");


        BudżetPaństwa państwo = new BudżetPaństwa();
        CentralaTotolotka centrala = new CentralaTotolotka(państwo);
        Kolektura[] kolektury = new Kolektura[10];
        for(int i = 0; i < 10; i++) {
            kolektury[i] = new Kolektura(centrala);
        }

        GraczLosowy[] graczeLosowi = new GraczLosowy[200];
        GraczMinimalista[] graczeMinimaliści = new GraczMinimalista[200];
        GraczStałoblankietowy[] graczeStałoBlankietowi = new GraczStałoblankietowy[200];
        GraczStałoliczbowy[] graczeStałoliczbowi = new GraczStałoliczbowy[200];
        Gracz[] gracze = new Gracz[800];

        for(int i = 0; i < 200; i++) {
            graczeLosowi[i] = new GraczLosowy("Jan", "Kowalski", "12345678901", centrala);
            graczeMinimaliści[i] = new GraczMinimalista("Grzegorz", "Brzęczy", 
            "1347894", MaszynaLosująca.przedział(MINKW, MAXKW),kolektury[i % 10],centrala);
            // okrojone konstruktory - dobierają jako ulubione losowe kolektury z wszystkich w grze,
            // losowe stałe Blankiety / Liczby;
            graczeStałoliczbowi[i] = new GraczStałoliczbowy("Jakiś", "Ważny", "14356354", 
                                MaszynaLosująca.przedział(MINKW, MAXKW), centrala);
            graczeStałoBlankietowi[i] = new GraczStałoblankietowy("Kasia", "Margaryna", "123321", 
                                MaszynaLosująca.przedział(MINKW, MAXKW), centrala);
        }
        System.arraycopy(graczeLosowi, 0, gracze, 0, 200);
        System.arraycopy(graczeMinimaliści, 0, gracze, 200, 200);
        System.arraycopy(graczeStałoBlankietowi, 0, gracze, 400, 200);
        System.arraycopy(graczeStałoliczbowi, 0, gracze, 600, 200);
        boolean skip = false;
        for(int j = 0; j < 20; j++) {
            for(Gracz a : gracze) {
                a.zakupLosowania();
            }
            centrala.noweLosowanie();
            for(int i = 0; i < 800; i++) {
                gracze[i].sprawdźKupony();
            }
            if(j >= 1) {
                if(centrala.historia().pobierzLosowanie(j).wartNagród()[3] < centrala.historia().pobierzLosowanie(j - 1).wartNagród()[3]) {
                    System.out.println("Mamy jackpot!!\n");
                    System.out.println(centrala.oLosowaniu(j));
                    System.out.println();
                    skip = true;
                    break;
                }
            }
        }

        if(!skip) {
            // już nie kupują tylko sprawdzają wygrane
            for(int j = 20; j < 30; j++) {
                centrala.noweLosowanie();
                for(Gracz a : gracze) {
                    a.sprawdźKupony();
                }
            }
        }

        for(Gracz a : gracze) {
            System.out.println(a);
        }
        System.out.println(centrala);
        System.out.println(państwo);
        System.out.println(Kwota.kwota(centrala.pobraneSubwencje()));

        for(int i = 1; i < centrala.historia().nrAktLosowania() - 1; i++) {
            System.out.println(centrala.oLosowaniu(i));
        }
        System.out.println("Koniec");
    }
    public static void main(String[] argv) {
        wykonajTest();
    }
}
