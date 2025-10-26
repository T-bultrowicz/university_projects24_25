import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.ArrayList;
import java.lang.reflect.Field;
import glowny.Main;
import lotto.*;
import wyjątki.*;

/* Na potrzeby testów zwiększono widoczności niektórych obiektów, 
 * co umożliwia większą swobodę, kosztem zapewne możliwych nadużyć,
 * ze strony klientów chcących wygrać. W szczególności np. losowanie z
 * ustalonymi liczbami.
 */

public class LottoWszystkieTest {
    
    /* ---------------------------------------------
     * Pożyczyłem z ChataGPT, bo nie wiedziałem jak elegancko inaczej 
     * możnaby obejść konieczność ustawiania liczników w nrLosowań itd. 
     * na 1 przykażdym wywołaniu testu. -- Moje rozwiązanie by działało,
     * logicznie, wymaga by 1 losowanie, 1 kolektura itd... miało nr 1
    */ 
    @BeforeEach
    void resetStaticCounters() throws Exception {
        resetStaticField(Kolektura.class, "NR_GENERATOR");
        resetStaticField(Kupon.class, "ID_GENERATOR");
        resetStaticField(Losowanie.class, "ID_GENERATOR");
    }
    private void resetStaticField(Class<?> clazz, String fieldName) throws Exception {
        Field field = clazz.getDeclaredField(fieldName);
        field.setAccessible(true);
        field.set(null, 1);
    }
    // ----------------------------------------------


    @Test @SuppressWarnings("all")
    void wypełnianieBlankietów() throws ZłyBlankiet {
        // startowe twory
        BudżetPaństwa państwo = new BudżetPaństwa();
        CentralaTotolotka centrala = new CentralaTotolotka(państwo);
        Kolektura k = new Kolektura(centrala);

        // poprawne wypełnienie blankietu
        Blankiet blankiet = new Blankiet();
        blankiet.zaznaczIlośćZakładów(1);
        int[] t = new int[]{3, 5, 6, 18, 32, 49};

        for(int liczba : t) {
            blankiet.zaznaczTyp(1, liczba);
        } 
        Kupon a = Weryfikacje.przekształćBlankiet(blankiet, k, 1);
        Typowanie[] typowanie = a.zakłady();
        assertEquals(typowanie.length, 1);
        assertArrayEquals(typowanie[0].typowaneLiczby(), t);

        // częściowo niepoprawne wypełnienia blakietu - 
        //         zakładamy, że jak dobrze zaznaczona ilość Losowań wprzód,
        //         oraz choć jedno typowanie liczb to można zamienić w Kupon
        Blankiet blankiet2 = new Blankiet();
        blankiet2.zaznaczIlośćZakładów(1);
        int[] t2 = new int[]{3, 4, 5, 6};
        for(int liczba : t) {
            blankiet2.zaznaczTyp(3, liczba);
            blankiet2.zaznaczTyp(7, liczba);
            blankiet2.zaznaczTyp(8, liczba);
        }
        for(int liczba2 : t2) blankiet2.zaznaczTyp(2, liczba2);
        blankiet2.zaznaczAnuluj(7);
        typowanie = Weryfikacje.przekształćBlankiet(blankiet2, k, 3).zakłady();
        assertEquals(typowanie.length, 2);
        assertArrayEquals(typowanie[0].typowaneLiczby(), t);
        assertArrayEquals(typowanie[1].typowaneLiczby(), t);


        // niepoprawne wypełniania blankietu
        assertThrows(SpozaZasięgu.class, () -> {
            blankiet2.zaznaczAnuluj(9);
        });
        assertThrows(SpozaZasięgu.class, () -> {
            blankiet2.zaznaczTyp(5, 51);
        });
        assertThrows(SpozaZasięgu.class, () -> {
            blankiet2.zaznaczTyp(9, 3);
        });
        assertThrows(SpozaZasięgu.class, () -> {
            blankiet2.zaznaczIlośćZakładów(11);
        });

        Blankiet blankiet3 = new Blankiet();
        assertThrows(ZłyBlankiet.class, () -> {
            Kupon kupon = Weryfikacje.przekształćBlankiet(blankiet3, k, 1);
        });
        for(int liczba2 : t2) {
            blankiet3.zaznaczTyp(1, liczba2);
        }
        blankiet3.zaznaczTyp(3, 17);
        assertThrows(ZłyBlankiet.class, () -> {
            Kupon kupon = Weryfikacje.przekształćBlankiet(blankiet3, k, 1);            
        });

        Blankiet blankiet4 = new Blankiet();
        for(int liczba : t) {
            blankiet4.zaznaczTyp(1, liczba);
            blankiet4.zaznaczTyp(4, liczba);
        }
        blankiet4.zaznaczIlośćZakładów(1);
        blankiet4.zaznaczIlośćZakładów(2);
        assertThrows(ZłyBlankiet.class, () -> {
            Kupon kupon = Weryfikacje.przekształćBlankiet(blankiet4, k, 1);            
        });

        System.out.println(blankiet4);
    }

    @Test 
    void wyliczanieNagród() {
        BudżetPaństwa państwo = new BudżetPaństwa();
        CentralaTotolotka centrala = new CentralaTotolotka(państwo);
        ArrayList<Long> al = new ArrayList<>();
        for(int i = 0; i < 100; i++) {
            al.add(5L);
        }
        assertEquals(500L, centrala.opodatkujWygraną(al));
        al.clear();
        al.add(1000000L);
        assertEquals(900000L, centrala.opodatkujWygraną(al));
        // taka skomplikowana ujemna wartość ponieważ centrala nie miała pieniędzy,
        // a funkcja .opodatkujWygraną() odrazu rozlicza centralę z wypłacenia jej.
        // Ponadto centrala pożycza pieniądze na wypłatę, a przyjąłem strategię, że
        // gdy jej brakuje "dopożycza" sobie do miliona.
        assertEquals(-99900500L, państwo.bilans());
        assertEquals(99100000L, centrala.fundusz());

        System.out.println(państwo);
        System.out.println(centrala);
    }

    @Test
    void wyliczaniePuli() {
        CentralaTotolotka centrala = new CentralaTotolotka(new BudżetPaństwa());
        long kwota = 100000000; //MILION
        long[] ilZwycięzców = new long[]{1000, 100, 10, 1};
        assertArrayEquals(new long[]{2400, 211200, 392000, 200000000}, 
                                        centrala.wyliczPula(kwota, ilZwycięzców));
        ilZwycięzców = new long[]{1, 0, 0, 0};
        assertArrayEquals(new long[]{2400, 23517600, 3920000, 200000000}, 
                                        centrala.wyliczPula(kwota, ilZwycięzców));
        ilZwycięzców = new long[]{0, 1, 0, 0}; // wchodzi efekt kumulacji
        assertArrayEquals(new long[]{2400, 23520000, 3920000, 221560000}, 
                                        centrala.wyliczPula(kwota, ilZwycięzców));
        ilZwycięzców = new long[]{0, 0, 1, 0};
        assertArrayEquals(new long[]{2400, 23520000, 3920000, 243120000}, 
                                        centrala.wyliczPula(kwota, ilZwycięzców));
        ilZwycięzców = new long[]{0, 0, 0, 1};
        assertArrayEquals(new long[]{2400, 23520000, 3920000, 264680000}, 
                                        centrala.wyliczPula(kwota, ilZwycięzców));
        assertEquals(200000000, centrala.wyliczPula(kwota, ilZwycięzców)[3]);   
    }

    @Test
    void kupowanieKuponów() throws ZłyBlankiet {
        CentralaTotolotka centrala = new CentralaTotolotka(new BudżetPaństwa());
        Kolektura[] kolektury = new Kolektura[3];
        for(int i = 0; i < 3; i++) kolektury[i] = new Kolektura(centrala);
        GraczStałoliczbowy gsl = new GraczStałoliczbowy("a", "b", "1", 2900, centrala);
        GraczStałoblankietowy gsb = new GraczStałoblankietowy("a", "b", "1", 0, centrala);
        GraczMinimalista gm = new GraczMinimalista("a", "b", "1", 200, kolektury[0], centrala);
        GraczLosowy gl = new GraczLosowy("a", "b", "1", centrala);
        // nie kupią biletu
        gm.zakupLosowania();
        gsl.zakupLosowania();
        assertEquals(200, gm.stanKonta());
        assertEquals(2900, gsl.stanKonta());
        assertEquals(0, gm.ilośćKuponów());
        assertEquals(0, gsl.ilośćKuponów());

        gm.pobierzFundusze(100);
        gsl.pobierzFundusze(100);
        // kupią bilet
        gm.zakupLosowania();
        gsl.zakupLosowania();
        assertEquals(1, gm.ilośćKuponów());
        assertEquals(1, gsl.ilośćKuponów());
        assertEquals(0, gm.stanKonta());
        assertEquals(0, gsl.stanKonta());

        Long kwota = gl.stanKonta();
        if(kwota > 2400000) { // na pewno wtedy kupi każdą ilość biletów
            gl.zakupLosowania();
            Long wydane = 0L;
            for(Kupon a : gl.kupony()) wydane += a.cena();
            assertEquals(kwota - wydane, gl.stanKonta());
        }
        long cena = Weryfikacje.przekształćBlankiet(gsb.swójBlankiet(), 
                                        kolektury[0], 1).cena();
        gsb.pobierzFundusze(cena + 100);
        gsb.zakupLosowania();
        assertEquals(1, gsb.ilośćKuponów());
        assertEquals(100L, gsb.stanKonta());
    }

    @Test
    void liczenieIlościZwycięzców() throws ŹlePodaneLiczby {
        CentralaTotolotka centrala = new CentralaTotolotka(new BudżetPaństwa());
        ArrayList<Kolektura> al = new ArrayList<>();
        for(int i = 0; i < 3; i++) al.add(new Kolektura(centrala));
        int[][] typy = new int[][]{
            {1, 2, 3, 4, 5, 6},
            {1, 2, 3, 4, 5, 7},
            {1, 40, 41, 42, 43, 44},
            {1, 2, 3, 8, 9, 10},
            {8, 9, 10, 4, 5, 6},
            {1, 2, 7, 8, 9, 6},
            {1, 2, 7, 8, 5, 6}
        };
        int[][] wynkiLosowań = new int[][] {
            {1, 2, 3, 4, 5, 6},
            {4, 5, 7, 11, 1, 36},
            {1, 2, 3, 8, 9, 10},
            {8, 4, 9, 6, 10, 5}
        };
        long[][] spodziewane = new long[][]{
            {3, 1, 1, 1},
            {2, 1, 0, 0},
            {4, 1, 0, 1},
            {4, 0, 0, 1}
        };
        Gracz[] g = new Gracz[typy.length];
        for(int i = 0; i < g.length; i++) {
            g[i] = new GraczStałoliczbowy
                    ("a", "b", "c", 3000, centrala, al, typy[i]);
            g[i].zakupLosowania();
        }
        for(int i = 0; i < 4; i++) {
            assertArrayEquals(spodziewane[i], centrala.wyliczZwycięzców
                                    (new Losowanie(wynkiLosowań[i])));
        }

    }

    @Test @SuppressWarnings("all")
    void trochęWyjątków() {
        CentralaTotolotka centrala = new CentralaTotolotka(new BudżetPaństwa());
        Kolektura[] kolektury = new Kolektura[5];
        for(int i = 0; i < 4; i++) kolektury[i] = new Kolektura(centrala);
        assertThrows(NullWartość.class, () -> {
            kolektury[4] = new Kolektura(null);
        });
        assertThrows(NullWartość.class, () -> {
            centrala.dodajKolekturę(null);
        });
        assertThrows(NullWartość.class, () -> {
            Gracz g = new GraczMinimalista(null, "a", "b", 0, kolektury[1], centrala);
        });
        assertThrows(NullWartość.class, () -> {
            Gracz g = new GraczMinimalista("a", null, "b", 0, kolektury[1], centrala);
        });
        assertThrows(NullWartość.class, () -> {
            Gracz g = new GraczMinimalista("a", "a", null, 0, kolektury[1], centrala);
        });   
        assertThrows(NullWartość.class, () -> {
            Gracz g = new GraczMinimalista("c", "a", "b", 0, null, centrala);
        });
        assertThrows(UjemnaWartość.class, () -> {
            Gracz g = new GraczMinimalista("a", "b", "c", -5, kolektury[1], centrala);
        });

        ArrayList<Kolektura> k = new ArrayList<>();
        k.add(kolektury[0]);
        assertThrows(ŹlePodaneLiczby.class, () -> {
            Gracz g = new GraczStałoliczbowy("a", "b", "c", 50000, 
                        centrala, k, new int[]{1,3,5,6,6,11});
        });
        assertThrows(NullWartość.class, () -> {
            Gracz g = new GraczStałoliczbowy("a", "b", "c", 50000, 
                        centrala, k, null);
        });
        assertThrows(ŹlePodaneLiczby.class, () -> {
            Gracz g = new GraczStałoliczbowy("a", "b", "c", 50000, 
                        centrala, k, new int[]{1,3,5, 7, 14, 50});
        });
        assertThrows(ŹlePodaneLiczby.class, () -> {
            Gracz g = new GraczStałoliczbowy("a", "b", "c", 50000, 
                        centrala, k, new int[]{1,3,5,7 });
        });
        Gracz g = new GraczMinimalista("c", "a", "b", 
                                   6000, kolektury[1], centrala);
        g.zakupLosowania();
        centrala.noweLosowanie();
        assertThrows(BrakKuponuBaza.class, () -> {
            g.odbierzNagrodę(g.kupony().get(0).id(), kolektury[2]);
        });
        assertEquals(1, g.kupony().size());
        assertThrows(NieMaKuponu.class, () -> {
            g.odbierzNagrodę(Weryfikacje.przekształćBlankiet
                (MaszynaLosująca.losowyBlankiet(), kolektury[1], 1).id());
        });
        assertEquals(2, centrala.historia().nrAktLosowania());
        g.odbierzNagrodę(g.kupony().get(0).id(), kolektury[1]);
        assertEquals(0, g.kupony().size());
        g.zakupLosowania();
        centrala.noweLosowanie();
        String id = g.kupony().get(0).id();
        g.odbierzNagrodę(id, kolektury[1]);        
        assertThrows(NieMaKuponu.class, () -> {
            g.odbierzNagrodę(id);
        });   
    }

    @Test
    void GłównaSymulacja() {
        Main.wykonajTest();
    }
}
