package test;

import javax.crypto.Mac;

// import org.junit.jupiter.api.Test;
import tablice.*;
import wyjątki.*;


import test.MojaMaszynkaTestująca.Test;

import static test.MojaMaszynkaTestująca.*;
import static test.MojaMaszynkaTestująca.assertArrayEquals;
import static test.MojaMaszynkaTestująca.assertEquals;

public class Zad1TestyBezJUnit {
    // Testy z treści zadania.
    // Wydanie kompletne i uzupełnione o własne metody assert*.


    @Test
    void testWłasnościSkalarów() {
        Skalar skalar = new Skalar(1.0);
        assertEquals(0, skalar.wymiar());
        assertArrayEquals(new int[]{}, skalar.kształt());
        assertEquals(1, skalar.liczbaElementów());
    }

    @Test
    void testWłasnościWektorów() throws ZłeArgumentyFunkcji {
        Wektor wektor1 = new Wektor(new double[]{1.0, 2.0, 1.0}, true);
        Wektor wektor2 = new Wektor(new double[]{2.0, 2.0, 3.0}, false);
        assertEquals(1, wektor1.wymiar());
        assertArrayEquals(new int[]{3}, wektor1.kształt());
        assertEquals(3, wektor1.liczbaElementów());
        assertEquals(1, wektor2.wymiar());
        assertArrayEquals(new int[]{3}, wektor2.kształt());
        assertEquals(3, wektor2.liczbaElementów());
    }

    @Test
    void testWłasnościMacierzy() throws ZłeArgumentyFunkcji {
        Macierz matrix = new Macierz (new double[][]{
                {1.0, 0.0, 2.0},
                {2.0, 1.0, 3.0},
                {1.0, 1.0, 1.0},
                {2.0, 3.0, 1.0}
        });
        assertEquals(2, matrix.wymiar());
        assertArrayEquals(new int[]{4, 3}, matrix.kształt());
        assertEquals(12, matrix.liczbaElementów());
    }

    @Test
    void testArytmetykiSkalarów() throws ZłeArgumentyFunkcji {
        Skalar skalar1 = new Skalar(3.5);
        Skalar skalar2 = new Skalar(11.5);
        assertEquals(new Skalar(15.0), skalar1.suma(skalar2));

        Skalar skalar3 = new Skalar(3.0);
        Skalar skalar4 = new Skalar(12.0);
        assertEquals(new Skalar(36.0), skalar3.iloczyn(skalar4));
    }

    @Test
    void testArytmetykiSkalarWektor() throws ZłeArgumentyFunkcji {
        for(boolean b: new boolean[]{true, false}) {
            // 3.0 + [1.0, 2.5] = [4.0, 5.5]
            Skalar skalar = new Skalar(3.0);
            Wektor wektor1 = new Wektor(new double[]{1.0, 2.5}, b);
            assertEquals(new Wektor(new double[]{4.0, 5.5}, b), skalar.suma(wektor1));

            // 4.0 * [1.5, 2.25] = [6.0, 9.0]
            Wektor wektor2 = new Wektor(new double[]{1.5, 2.25}, b);
            assertEquals(new Wektor(new double[]{6.0, 9.0}, b),
                          new Skalar(4.0).iloczyn(wektor2));
        }  // for b
    }

    @Test
    void testArytmetykiWektorSkalar() throws ZłeArgumentyFunkcji {
        for(boolean b: new boolean[]{true, false}) {
            // [1.0, 2.5] + 3.0 = [4.0, 5.5]
            Skalar skalar = new Skalar(3.0);
            Wektor wektor1 = new Wektor(new double[]{1.0, 2.5}, b);
            assertEquals(new Wektor(new double[]{4.0, 5.5}, b),
                           wektor1.suma(skalar));

            // [1.5, 2.25] * 4.0 = [6.0, 9.0]
            Wektor wektor2 = new Wektor(new double[]{1.5, 2.25}, b);
            assertEquals(new Wektor(new double[]{6.0, 9.0}, b),
                         wektor2.iloczyn(new Skalar(4.0)));
        }  // for b
    }

    @Test
    void testArytmetykiSkalarMacierz() throws ZłeArgumentyFunkcji{
        Skalar skalar = new Skalar(3.0);
        Macierz macierz = new Macierz(new double[][]{
                {1.25, 3.0, -12.0},
                {-51.0, 8.0, 3.5}
        });
        Macierz oczekiwanyWynikDodawania = new Macierz(new double[][]{
                {4.25, 6.0, -9.0},
                {-48.0, 11.0, 6.5}
        });
        assertEquals(oczekiwanyWynikDodawania, skalar.suma(macierz));

        Skalar skalar2 = new Skalar(-3.0);
        Macierz oczekiwanyWynikMnożenia = new Macierz(new double[][]{
                {-3.75, -9.0, 36.0},
                {153.0, -24.0, -10.5}
        });
        assertEquals(oczekiwanyWynikMnożenia, skalar2.iloczyn(macierz));

        // Odwrotna Kolejność
        assertEquals(oczekiwanyWynikDodawania, macierz.suma(skalar));
        assertEquals(oczekiwanyWynikMnożenia, macierz.iloczyn(skalar2));
    }

    @Test
    void testDodawaniaIMnożeniaWektorWektor() throws ZłeArgumentyFunkcji {
        // Wektor + Wektor
        Wektor wektor1 = new Wektor(new double[]{1.0, 2.0, 3.0}, true);
        Wektor wektor2 = new Wektor(new double[]{1.0, 1.0, -2.0}, true);
        assertEquals(new Wektor(new double[]{2.0, 3.0, 1.0}, true),
                wektor1.suma(wektor2));

        Wektor wektor3 = new Wektor(new double[]{-2.0, 5.0}, false);
        Wektor wektor4 = new Wektor(new double[]{-5.0, 2.0}, false);
        assertEquals(new Wektor(new double[]{-7.0, 7.0}, false),
                wektor3.suma(wektor4));

        // Wektor * Wektor (Scalar result)
        Wektor wektor5 = new Wektor(new double[]{3.0, 2.0, -1.0}, true);
        Wektor wektor6 = new Wektor(new double[]{-2.0, 2.0, 1.0}, true);
        assertEquals(new Skalar(-3.0), wektor5.iloczyn(wektor6));

        Wektor wektor7 = new Wektor(new double[]{-2.0, -5.0, 1.0, 3.0}, false);
        Wektor wektor8 = new Wektor(new double[]{-5.0, 1.0, 2.0, -3.0}, false);
        assertEquals(new Skalar(-2.0), wektor7.iloczyn(wektor8));

        Wektor wektor9 = new Wektor(new double[]{1.0, 1.0, -2.0}, false);
        assertEquals(new Macierz(new double[][]{{-3.0}}), wektor1.iloczyn(wektor9));

        Wektor wektor10 = new Wektor(new double[]{1.0, 2.0, 3.0}, false);
        Wektor wektor11 = new Wektor(new double[]{1.0, 1.0, -2.0}, true);
        assertEquals(new Macierz(new double[][]{
                {1.0, 1.0, -2.0},
                {2.0, 2.0, -4.0},
                {3.0, 3.0, -6.0}
                }), wektor10.iloczyn(wektor11));
    }

    @Test
    void testDodawaniaWektorMacierz() throws ZłeArgumentyFunkcji {
        // Wektor + Macierz
        Wektor wektor1 = new Wektor(new double[]{3.0, 1.5, -2.0}, true);
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 3.5, -12.0},
                {-5.0, 8.0, 3.0}
        });
        assertEquals(new Macierz(new double[][]{
                {4.0, 5.0, -14.0},
                {-2.0, 9.5, 1.0}
        }), wektor1.suma(macierz1));

        Wektor wektor2 = new Wektor(new double[]{7.5, -5.0}, false);
        assertEquals(new Macierz(new double[][]{
                {8.5, 11.0, -4.5},
                {-10.0, 3.0, -2.0}
        }), wektor2.suma(macierz1));

        // Odwrotna Kolejność

        // Macierz + Wektor (odwrotna kolejność)
        assertEquals(new Macierz(new double[][]{
                {4.0, 5.0, -14.0},
                {-2.0, 9.5, 1.0}
        }), macierz1.suma(wektor1));

        assertEquals(new Macierz(new double[][]{
                {8.5, 11.0, -4.5},
                {-10.0, 3.0, -2.0}
        }), macierz1.suma(wektor2));

    }

    @Test
    void testMnożeniaWektorMacierz() throws ZłeArgumentyFunkcji {
        // Wektor * Macierz
        Wektor wektor1 = new Wektor(new double[]{1.0, 2.0, 3.0}, true);
        Wektor wektor2 = new Wektor(new double[]{1.0, 1.0, -2.0}, false);
        assertEquals(new Macierz(new double[][]{{-3.0}}), wektor1.iloczyn(wektor2));

        Wektor wektor3 = new Wektor(new double[]{1.0, 2.0, 3.0}, false);
        Wektor wektor4 = new Wektor(new double[]{1.0, 1.0, -2.0}, true);
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 1.0, -2.0},
                {2.0, 2.0, -4.0},
                {3.0, 3.0, -6.0}
        });
        assertEquals(macierz1, wektor3.iloczyn(wektor4));
    }

    @Test
    void testMnożeniaMacierzWektor() throws ZłeArgumentyFunkcji {
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, -2.0},
                {2.0, 1.0}
        });
        Wektor wektor1 = new Wektor(new double[]{-1.0, 3.0}, false);
        Wektor oczekiwany1 = new Wektor(new double[]{5.0, -9.0, 1.0}, false);
        assertEquals(oczekiwany1, macierz1.iloczyn(wektor1));

        // [1.0, -1.0, 2.0] * [[1.0, 2.0], [3.0, -2.0], [2.0, 1.0]] = [2.0, 6.0]
        Wektor wektor2 = new Wektor(new double[]{1.0, -1.0, 2.0}, true);
        Macierz macierz2 = new Macierz(new double[][]{
                {1.0, 2.0},
                {3.0, -2.0},
                {2.0, 1.0}
        });
        Wektor oczekiwany2 = new Wektor(new double[]{2.0, 6.0}, true);
        assertEquals(oczekiwany2, wektor2.iloczyn(macierz2));
    }

    @Test
    void testDodawaniaMacierzMacierz() throws ZłeArgumentyFunkcji {
        // [[1.0, -2.0, 3.0], [2.0, 1.0, -1.0]] + [[3.0, -1.0, 2.0], [1.0, 1.0, -2.0]] = [[4.0, -3.0, 5.0], [3.0, 2.0, -3.0]]
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, -2.0, 3.0},
                {2.0, 1.0, -1.0}
        });
        Macierz macierz2 = new Macierz(new double[][]{
                {3.0, -1.0, 2.0},
                {1.0, 1.0, -2.0}
        });
        Macierz oczekiwany = new Macierz(new double[][]{
                {4.0, -3.0, 5.0},
                {3.0, 2.0, -3.0}
        });
        assertEquals(oczekiwany, macierz1.suma(macierz2));
    }

    @Test
    void testMnożeniaMacierzMacierz() throws ZłeArgumentyFunkcji {
        // [[2.0, 0.5], [1.0, -2.0], [-1.0, 3.0]] * [[2.0, -1.0, 5.0], [-3.0, 2.0, -1.0]] = [[2.5, -1.0, 9.5], [8.0, -5.0, 7.0], [-11.0, 7.0, -8.0]]
        Macierz macierz1 = new Macierz(new double[][]{
                {2.0, 0.5},
                {1.0, -2.0},
                {-1.0, 3.0}
        });
        Macierz macierz2 = new Macierz(new double[][]{
                {2.0, -1.0, 5.0},
                {-3.0, 2.0, -1.0}
        });
        Macierz oczekiwany = new Macierz(new double[][]{
                {2.5, -1.0, 9.5},
                {8.0, -5.0, 7.0},
                {-11.0, 7.0, -8.0}
        });
        assertEquals(oczekiwany, macierz1.iloczyn(macierz2));
    }

    @Test
    void testNegacji() throws ZłeArgumentyFunkcji {
        Skalar skalar = new Skalar(17.0);
        assertEquals(new Skalar(-17.0), skalar.negacja());

        Wektor wektor = new Wektor(new double[]{10.0, -45.0, 0.0, 29.0, -3.0}, true);
        assertEquals(new Wektor(new double[]{-10.0, 45.0, 0.0, -29.0, 3.0}, true),
                wektor.negacja());

        Macierz macierz = new Macierz(new double[][]{
                {0.0, 0.5, -1.25},
                {11.0, -71.0, -33.5},
                {-2.0, -1.75, -99.0}
        });
        Macierz oczekiwany = new Macierz(new double[][]{
                {0.0, -0.5, 1.25},
                {-11.0, 71.0, 33.5},
                {2.0, 1.75, 99.0}
        });
        assertEquals(oczekiwany, macierz.negacja());
    }

    @Test
    void testPrzypisaniaSkalarów() {
        try {
        // Przypisz skalar [0.5] do skalara [1.0]
        Skalar skalar1 = new Skalar(1.0);
        skalar1.przypisz(new Skalar(0.5));
        assertEquals(new Skalar(0.5), skalar1);

        // Przypisz skalar [0.5] do wektora [1.0, 2.0, 3.0]
        Wektor wektor1 = new Wektor(new double[]{1.0, 2.0, 3.0}, true);
        wektor1.przypisz(new Skalar(0.5));
        assertEquals(new Wektor(new double[]{0.5, 0.5, 0.5}, true), wektor1);

        // Przypisz skalar [0.5] do macierzy
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0},
                {-3.0, -4.0},
                {5.0, -6.0}
        });
        macierz1.przypisz(new Skalar(0.5));
        assertEquals(new Macierz(new double[][]{
                {0.5, 0.5},
                {0.5, 0.5},
                {0.5, 0.5}
        }), macierz1);
        } catch(Exception e) {System.out.println(e);}
    }

    @Test
    void testPrzypisaniaWektorów() throws ZłeArgumentyFunkcji {
        // Przypisz wektor [1.5, 2.5, 3.5] do wektora [-1.0, 0.0, 1.0]
        Wektor wektor1 = new Wektor(new double[]{1.5, 2.5, 3.5}, false);
        Wektor wektor2 = new Wektor(new double[]{-1.0, 0.0, 1.0}, false);
        wektor2.przypisz(wektor1);
        assertEquals(new Wektor(new double[]{1.5, 2.5, 3.5}, false), wektor2);

        // Przypisz wektor [1.5, 2.5, 3.5] do wektora [-1.0, 0.0, 1.0] (wektor wierszowy i kolumnowy)
        Wektor wektor3 = new Wektor(new double[]{-1.0, 0.0, 1.0}, true);
        wektor3.przypisz(wektor1);
        assertEquals(new Wektor(new double[]{1.5, 2.5, 3.5}, false), wektor3);

        // Przypisz wektor [1.5, 2.5, 3.5] do macierzy
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0, -1.0, -2.0},
                {-3.0, -4.0, 3.0, 4.0},
                {5.0, -6.0, -5.0, 6.0}
        });
        macierz1.przypisz(wektor1);
        assertEquals(new Macierz(new double[][]{
                {1.5, 1.5, 1.5, 1.5},
                {2.5, 2.5, 2.5, 2.5},
                {3.5, 3.5, 3.5, 3.5}
        }), macierz1);
    }

    @Test
    void testPrzypisaniaMacierzy() throws ZłeArgumentyFunkcji {
        // Przypisz macierz [10.5, 20.5, 30.5; -1.5, 0.0, 1.5] do macierzy [1.0, 2.0, 3.0; 3.0, 2.0, 1.0]
        Macierz macierz1 = new Macierz(new double[][]{
                {1.0, 2.0, 3.0},
                {3.0, 2.0, 1.0}
        });
        Macierz macierz2 = new Macierz(new double[][]{
                {10.5, 20.5, 30.5},
                {-1.5, 0.0, 1.5}
        });

        macierz1.przypisz(macierz2);
        assertEquals(macierz2, macierz1);
    }

    @Test
    void testWycinków() throws ZłeArgumentyFunkcji {
        Skalar skalar = new Skalar(13.125);
        assertEquals(skalar, skalar.wycinek());

        Wektor wektor = new Wektor(new double[]{1.0, 21.0, 32.0, 43.0, 54.0}, true);
        Wektor oczekiwanyWycinekWektora = new Wektor(new double[]{32.0, 43.0}, true);
        assertEquals(oczekiwanyWycinekWektora, wektor.wycinek(2, 3));

        Macierz macierz = new Macierz(new double[][]{
                {7.0, -21.0, 15.0, -31.0, 25.0},
                {-21.0, 15.0, -31.0, 25.0, 7.0},
                {15.0, -31.0, 25.0, -7.0, -21.0},
                {-31.0, 25.0, 7.0, -21.0, 15.0}
        });
        Macierz oczekiwanyWycinekMacierzy = new Macierz(new double[][]{
                {15.0, -31.0},
                {-31.0, 25.0},
                {25.0, 7.0}
        });
        assertEquals(oczekiwanyWycinekMacierzy, macierz.wycinek(1, 3, 1, 2));
    }

    @Test
    void testWycinkówAdvanced() throws ZłeArgumentyFunkcji {
        Skalar skalar1 = new Skalar(11);
        Macierz macierz1 = new Macierz(new double[][]{
                {3, 7, 9},
                {13, 17.5, 5},
                {1, 3.2, 22},
                {2, 2, 2}
        });
        Wektor wektor1 = new Wektor(new double[]{4, 5, 6,  7}, true);
        Wektor wektor2 = wektor1.wycinek(0, 2);
        macierz1.przypisz(wektor2);

        assertEquals(macierz1, new Macierz(new double[][]{
            {4, 5, 6},
            {4, 5, 6},
            {4, 5, 6},
            {4, 5, 6}
        }, false));


        Macierz macierz2 = macierz1.wycinek(1, 2, 1, 2);
        Wektor wektor3 = wektor1.wycinek(2, 3);
        
        assertEquals(macierz2, new Macierz(new double[][]{
            {5, 6},
            {5, 6},
        }, false));

        wektor3.transponuj();
        macierz2.przypisz(wektor3);

        assertEquals(macierz1, new Macierz(new double[][]{
            {4, 5, 6},
            {4, 6, 6},
            {4, 7, 7},
            {4, 5, 6}
        }, false));

        macierz2.przypisz(skalar1);
        assertEquals(macierz1, new Macierz(new double[][]{
            {4, 5, 6},
            {4, 11, 11},
            {4, 11, 11},
            {4, 5, 6}
        }, false));

        Macierz macierz4 = new Macierz(new double[][]{
                {0.0, 1},
                {3, -3}
        });

        macierz4.transponuj();
        macierz2.przypisz(macierz4);
        assertEquals(macierz1, new Macierz(new double[][]{
            {4, 5, 6},
            {4, 0, 3},
            {4, 1, -3},
            {4, 5, 6}
        }, false));        
    }

    @Test
    void wypisBłędów() throws ZłeArgumentyFunkcji {
        Skalar skalarnull = null;
        Wektor wektornull = null;
        Macierz macierznull = null;

        Skalar skalar = new Skalar(15);
        Wektor wektor = new Wektor(new double[5], true);
        Wektor wektor2 = new Wektor(new double[5], false);
        Macierz macierz = new Macierz(new double[4][5]);
        Macierz macierz2 = new Macierz(new double[5][4]);

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 5; j++) {
                wektor.ustaw(i, j);
                wektor2.ustaw(j, j);
                macierz.ustaw(j, i, j);
                macierz2.ustaw(i, j, i);
            }
        }

        for(int i = 0; i < 23; i++) {
            try {
                if(i == 0) skalar.dodaj(skalarnull);
                if(i == 1) wektor.dodaj(wektornull);
                if(i == 2) macierz.przemnóż(macierznull);
                if(i == 3) macierz.przypisz(macierznull);
                if(i == 4) macierz.wycinek(0, 0, 7, 7);
                if(i == 5) wektor.wycinek(0, 5);
                if(i == 6) wektor.dodaj(wektor2);
                if(i == 7) wektor.ustaw(i, 1, 5 ,7);
                if(i == 8) wektor.daj();
                if(i == 9) macierz.ustaw(1 ,2);
                if(i == 10) skalar.daj(3);
                if(i == 11) macierz.wycinek(2, 2, 2, 3);
                if(i == 12) {
                    wektor.przypisz(wektor2);
                    System.out.println(wektor);
                }
                if(i == 13) {
                    macierz.przemnóż(macierz2);
                }
                if(i == 14) {
                    Macierz a = macierz.iloczyn(macierz2);
                    System.out.println(a);
                }
                if(i == 15) {
                    wektor.przemnóż(macierz);
                }
                if(i == 16) {
                    wektor.przemnóż(wektor2);
                }
                if(i == 17) {
                    System.out.println(wektor.iloczyn(wektor2));
                }
                if(i == 18) {
                    Macierz a = new Macierz(-3, 7);
                }
                if(i == 18) {
                    double[][] t = new double[][]{
                        {1, 3, 4},
                        {1, 2}
                    };
                    Macierz a = new Macierz(t, false);
                }
                if(i == 19) {
                    Wektor a = new Wektor(-1, false);
                }
                if(i == 20) {
                    System.out.println("i == 20\n");
                    Wektor a = new Wektor(null, false);
                }
                if(i == 21) {
                    System.out.println("i == 21\n");
                    double[][] a = new double[3][];
                    a[0] = new double[]{3, 3, 3};
                    a[1] = null;
                    a[2] = null;
                    Macierz b = new Macierz(a, false);
                }
                if(i == 22) {
                    System.out.println("i == 22\n");
                    double[][] a = new double[2][];
                    a[0] = new double[]{};
                    a[1] = new double[]{};
                    Macierz b = new Macierz(a, false);
                }
            } catch(Exception e) {System.out.println(e); System.out.println("\n");}
        }
    }

    @Test
    void testWycinekWycinka() throws ZłeArgumentyFunkcji {
        Macierz macierz = new Macierz(new double[][]{
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25}
        });
        Macierz wycinek1 = macierz.wycinek(1, 3, 1, 3);
        Macierz wycinek2 = wycinek1.kopia();
        Macierz wycinek3 = wycinek2.wycinek(0, 1, 0, 2);

        wycinek3.przemnóż(new Macierz(new double[][]{{2, 2, 2}, {9, 8, 7}, {1, 1, 1}}));
        wycinek2.dodaj(new Wektor(new double[]{4, 5, 6}, false));

        assertEquals(macierz, new Macierz(new double[][]{
            {1, 2, 3, 4, 5},
            {6, 99, 91, 83, 10},
            {11, 160, 147, 134, 15},
            {16, 23, 24, 25, 20},
            {21, 22, 23, 24, 25}
        }, false));   
        wycinek1.przemnóż(wycinek2);

        assertEquals(macierz, new Macierz(new double[][]{
            {1, 2, 3, 4, 5},
            {6, 26270, 24378, 22486, 10},
            {11, 42442, 39385, 36328, 15},
            {16, 6692, 6221, 5750, 20},
            {21, 22, 23, 24, 25}
        }, false));        
    }

    public static void main(String[] args) {

        MojaMaszynkaTestująca.wykonajTesty(Zad1TestyBezJUnit.class);

    }

}
