package tablice;

import java.util.Arrays;
import wyjątki.*;

public class Macierz extends Tablica {

    //dane
    protected double[][] tab;
    // Mówi, czy macierz jest obrócona, macierz sama w sobie nie obraca się,
    // tylko operacje opierają się na tej wartości.
    protected boolean czyObrócona;

    //techniczne
    // kopiuj = true przekazuje tabelę double[][] nie przez referencję
    public Macierz(double[][] macierz, boolean kopiuj) throws ZłeArgumentyFunkcji {
        super(2);
        nullCheck(macierz, " w .Macierz()");
        if (macierz.length == 0) throw new ZłyIndeks
        ("konstrukotrze Macierz(), podano tablicę o zerowym wymiarze");
        nullCheck(macierz[0], " w .Macierz()");
        if (macierz[0].length == 0) throw new ZłyIndeks
        ("konstrukotrze Macierz(), podano tablicę o zerowym wymiarze");  

        int rozmiar = macierz[0].length;
        if(kopiuj) tab = new double[macierz.length][];
        for (int i = 0; i < macierz.length; i++) {
            nullCheck(macierz[i], " w .Macierz()");
            if (macierz[i].length != rozmiar) throw new NiezgodnyKształt
            ("konstrukotrze Macierz(), tablica ma różne wymiary wierszy");
            if(kopiuj) tab[i] = macierz[i].clone();
        }
        if(!kopiuj) tab = macierz;
        czyObrócona = false;
    }

    public Macierz(double[][] macierz) throws ZłeArgumentyFunkcji {
        super(2);
        nullCheck(macierz, " w .Macierz()");
        if (macierz.length == 0) throw new ZłyIndeks
        ("konstrukotrze Macierz(), podano tablicę o zerowym wymiarze");
        if (macierz[0].length == 0) throw new ZłyIndeks
        ("konstrukotrze Macierz(), podano tablicę o zerowym wymiarze");

        int rozmiar = macierz[0].length;
        tab = new double[macierz.length][];
        for (int i = 0; i < macierz.length; i++) {
            nullCheck(macierz[i], " w .Macierz()");
            if (macierz[i].length != rozmiar) throw new NiezgodnyKształt
            ("konstrukotrze Macierz(), tablica ma różne wymiary wierszy");
            tab[i] = macierz[i].clone();
        }
        czyObrócona = false;
    }

    public Macierz(int x, int y) throws ZłeArgumentyFunkcji {
        super(2);
        if (x <= 0 || y <= 0) throw new ZłyIndeks
            ("konstrukotrze Macierz(), wprowadzono zerowy/ujemny wymiar");
        tab = new double[x][y];
        czyObrócona = false;
    }

    @Override
    public String toString() {
        int t[] = kształt();
        StringBuilder sb = new StringBuilder();
        sb.append("Macierz: kształt - '").append(Arrays.toString(t)).append("'\n");

        for (int i = 0; i < t[0]; i++) {
            sb.append("[");
            for (int j = 0; j < t[1]; j++) {
                sb.append(tab[kordX(i, j)][kordY(i, j)]);
                if (j < t[1] - 1) {
                    sb.append(", ");
                }
            }
            sb.append("]\n");
        }
        return sb.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Macierz)) return false;
        Macierz druga = (Macierz) obj;
    
        int[] t1 = kształt(), t2 = druga.kształt();
        if (t1[0] != t2[0] || t1[1] != t2[1]) return false;
    
        try {
            for (int i = 0; i < t1[0]; i++) {
                for (int j = 0; j < t1[1]; j++) {
                    if (!doubleRowne(daj(i, j), druga.daj(i, j), 1e-9)) return false;
                }
            }
        } catch(Exception e) {System.out.println(e);}
    
        return true;
    }

    //protected - metody pomocnicze, sprawdzające Wyjątki

    protected int kordX(int i, int j) {
        return czyObrócona ? j : i;
    }

    protected int kordY(int i, int j) {
        return czyObrócona ? i : j;
    }

    protected void sprawdźKształt(Wektor w) throws ZłeArgumentyFunkcji {
        int t[] = kształt();
        int x = w.liczbaElementów();
        if (w.orientacja() && x != t[1])
            throw new NiezgodnyKształt(this + " długość wektora " + w 
                        + "\n Wynosi: " + x + " zamiast: " + t[1]);
        if (!w.orientacja() && x != t[0])
            throw new NiezgodnyKształt(this + " długość wektora " + w 
                        + "\n Wynosi: " + x + " zamiast: " + t[0]);            
    }

    protected void sprawdźIdentKształt(Macierz m, String mes) 
                                    throws ZłeArgumentyFunkcji {
        int[] t1 = kształt(), t2 = m.kształt(); 
        if(t1[0] != t2[0] || t1[1] != t2[1]) {
            throw new NiezgodnyKształt(mes + " kształty macierzy różnią się");
        } 
    }

    protected void sprawdźMnożkształt(Macierz m, String mes) 
                                    throws ZłeArgumentyFunkcji {
        int[] t1 = kształt(), t2 = m.kształt();
        if(t2[0] != t1[1] || t2[1] != t1[1]) {
            throw new NiezgodnyKształt(mes + " kształty macierzy różnią się");
        } 
    }

    protected void sprawdźWycinek(int[] param) throws ZłeArgumentyFunkcji {
        if (param.length != 4) throw new ZłaIlośćArgumentów
            (".wycinek(), " + this + "\n Z parametrami " + Arrays.toString(param) 
            + " zamiast [int_low, int_hi, int_2low, int2_hi].");
        if (param[0] > param[1] || param[2] > param[3]) 
            throw new ZłyIndeks(".wycinek(), " + this + "\n podano " 
                                + Arrays.toString(param) + 
                                "zamiast [int_low, int_hi, int_2low, int2_hi].");
        int t[] = kształt();
        if (param[1] >= t[0] || param[3] >= t[1] || param[0] < 0 || param[2]<0) 
            throw new ZłyIndeks(".wycinek(), " + this + "\n Podano " + 
                        Arrays.toString(param) + " spoza zakresu macierzy.");
    }

    protected void sprawdźDajUstaw(int[] param) throws ZłeArgumentyFunkcji {
        if (param.length != 2) throw new ZłaIlośćArgumentów
            (".daj() wywołując dla" + this + "\n Z parametrami " +
                    Arrays.toString(param) + " zamiast [int, int].");
        int t[] = kształt();
        if(param[0] < 0 || param[0] >= t[0]) 
            throw new ZłyIndeks(this + " dla .daj()");
        if(param[1] < 0 || param[1] >= t[1])
            throw new ZłyIndeks(this + " dla .daj()");        
    }

    //metody udostępnione użytkownikom
    @Override
    public int liczbaElementów() {
        return tab.length * tab[0].length;
    }

    @Override
    public int[] kształt() {
        if(!czyObrócona) return new int[]{tab.length, tab[0].length};
        return new int[]{tab[0].length, tab.length};
    }

    @Override
    public void transponuj() {
        czyObrócona = !czyObrócona;
    }

    @Override
    public void zaneguj() {
        int t[] = kształt();
        for(int i = 0; i < t[0]; i++)
            for(int j = 0; j < t[1]; j++)
                tab[kordX(i, j)][kordY(i, j)] *= -1;
    }

    @Override
    public void dodaj(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, "dla .dodaj()");
        double val = skalar.daj();
        int t[] = kształt();
        for(int i = 0; i < t[0]; i++)
            for(int j = 0; j < t[1]; j++)
                tab[kordX(i, j)][kordY(i, j)] += val;
    }

    @Override
    public void dodaj(Macierz macierz) throws ZłeArgumentyFunkcji {
        nullCheck(macierz, " dla .dodaj()");
        sprawdźIdentKształt(macierz, "dla .dodaj(), " + this);

        int t[] = kształt();
        // Konieczne zapisywanie wyników w macierzy - na wypadek interakcji
        //                      dwóch wycinków tej samej macierzy.

        double[][] nadpisywanaMacierz = new double[t[0]][t[1]];
        for(int i = 0; i < t[0]; i++)
            for(int j = 0; j < t[1]; j++)
                nadpisywanaMacierz[i][j] = macierz.daj(i, j) + daj(i, j);  
        przypisz(new Macierz(nadpisywanaMacierz, false));   
    }

    @Override
    public void dodaj(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, " dla .dodaj()");
        sprawdźKształt(wektor);

        int t[] = kształt();
        boolean or = wektor.orientacja();
        for(int i = 0; i < t[0]; i++)
            for(int j = 0; j < t[1]; j++)
                tab[kordX(i, j)][kordY(i, j)] += wektor.daj(or ? j : i);        
    }

    @Override
    public void przemnóż(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, "dla .przemnóż()");
        double val = skalar.daj();
        int t[] = kształt();
        for(int i = 0; i < t[0]; i++)
            for(int j = 0; j < t[1]; j++)
                tab[kordX(i, j)][kordY(i, j)] *= val;
    }

    @Override
    public void przemnóż(Macierz macierz) throws ZłeArgumentyFunkcji {
        nullCheck(macierz, "dla .przemnóż()");
        sprawdźMnożkształt(macierz, ".przemnóż(), " + this);

        int t1[] = kształt(), t2[] = macierz.kształt();
        // Konieczne zapisywanie wyników w macierzy - na wypadek interakcji
        //                      dwóch wycinków tej samej macierzy.

        double[][] nadpisywanaMacierz = new double[t1[0]][t1[1]];
        double val;
        for(int i = 0; i < t1[0]; i++) {
            for(int j = 0; j < t2[1]; j++) {
                val = 0;
                for(int k = 0; k < t1[1]; k++) {
                    val += daj(i, k) * macierz.daj(k, j);
                }
                nadpisywanaMacierz[i][j] = val;
            }
        }
        przypisz(new Macierz(nadpisywanaMacierz, false));
    }

    @Override
    public void przypisz(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, "dla .przypisz()");
        double val = skalar.daj();
        int t[] = kształt();
        for(int i = 0; i < t[0]; i++)
            for(int j = 0; j < t[1]; j++)
                tab[kordX(i, j)][kordY(i, j)] = val;
    }

    @Override
    public void przypisz(Macierz macierz) throws ZłeArgumentyFunkcji  {
        nullCheck(macierz, "dla .przypisz()");
        sprawdźIdentKształt(macierz, "dla .przypisz()" + this);

        int t[] = kształt();
        for(int i = 0; i < t[0]; i++)
            for(int j = 0; j < t[1]; j++)
                tab[kordX(i, j)][kordY(i, j)] = macierz.daj(i, j);    
    }

    @Override
    public void przypisz(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, "dla .przypisz()");
        sprawdźKształt(wektor);

        int t[] = kształt();
        boolean or = wektor.orientacja();
        for(int i = 0; i < t[0]; i++)
            for(int j = 0; j < t[1]; j++)
                tab[kordX(i, j)][kordY(i, j)] = wektor.daj(or ? j : i);          
    }

    @Override
    public Macierz negacja() {
        try {
            Macierz res = kopia();
            res.zaneguj();
            return res;
        } catch(Exception e) {
            System.out.println(e);
            return null;
        }
    }

    @Override
    public Macierz kopia() {
        try {
            Macierz res = new Macierz(tab, true);
            return res;
        } catch(ZłeArgumentyFunkcji zaf) {
            System.out.println(zaf);
            return null;
        }
    }

    @Override
    public MacierzWycinek wycinek(int... param) throws ZłeArgumentyFunkcji {
        sprawdźWycinek(param);
        if(czyObrócona) {
            int swap = param[0];
            param[0] = param[2];
            param[2] = swap;
            swap = param[1];
            param[1] = param[3];
            param[3] = swap;
        }
        return new MacierzWycinek(tab, czyObrócona, param);
    }

    @Override
    public Macierz suma(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, "dla .suma()");
        Macierz res = kopia();
        res.dodaj(skalar);
        return res;
    }

    @Override
    public Macierz suma(Macierz macierz) throws ZłeArgumentyFunkcji {
        nullCheck(macierz, "dla .suma()");
        sprawdźIdentKształt(macierz, ".suma()" + this);
        Macierz res = kopia();
        res.dodaj(macierz);
        return res;
    }

    @Override
    public Macierz suma(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, "dla .suma()");
        sprawdźKształt(wektor);
        Macierz res = kopia();
        res.dodaj(wektor);
        return res;
    }

    @Override
    public Macierz iloczyn(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, "dla .iloczyn()");
        Macierz res = kopia();
        res.przemnóż(skalar);
        return res;
    }

    @Override
    public Macierz iloczyn(Macierz macierz) throws ZłeArgumentyFunkcji {
        nullCheck(macierz, "dla .iloczyn()");
        int t1[] = kształt(), t2[] = macierz.kształt();
        if(t1[1] != t2[0]) throw new NiezgodnyKształt(" .iloczyn()" + this
        + " * " + macierz + "\n  nierówne wymiary: " + t1[1] + "!= " + t2[0]);

        double val;
        Macierz res = new Macierz(t1[0], t2[1]);
        for(int i = 0; i < t1[0]; i++) {
            for(int j = 0; j < t2[1]; j++) {
                val = 0;
                for(int k = 0; k < t1[1]; k++) {
                    val += daj(i, k) * macierz.daj(k, j);
                }
                res.ustaw(val, i, j);
            }
        }
        return res;
    }

    @Override
    public Wektor iloczyn(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, "dla .iloczyn()");
        transponuj();
        sprawdźKształt(wektor);
        transponuj();

        int t[] = kształt();
        boolean or = wektor.orientacja();
        int dlugoscWektora = or ? t[1] : t[0];
        int iloscMnozen = or ? t[0] : t[1];
        Wektor res = new Wektor(dlugoscWektora, or);
        double val;
        for(int i = 0; i < dlugoscWektora; i++) {
            val = 0;
            for(int j = 0; j < iloscMnozen; j++) {
                val += (or ? daj(j, i) : daj(i, j)) * wektor.daj(j);
            }
            res.ustaw(val, i);
        }
        return res;
    }

    @Override
    public double daj(int... param) throws ZłeArgumentyFunkcji {
        sprawdźDajUstaw(param);
        int logiczna = czyObrócona ? 1 : 0;
        return tab[param[logiczna]][param[1 - logiczna]];
    }

    @Override
    public void ustaw(double val, int... param) throws ZłeArgumentyFunkcji {
        sprawdźDajUstaw(param);
        int logiczna = czyObrócona ? 1 : 0;
        tab[param[logiczna]][param[1 - logiczna]] = val;
    }

    @Override
    public void ustaw(double val) throws ZłeArgumentyFunkcji {
        throw new ZłaIlośćArgumentów(".wycinek() wywołując" + 
                                " bez parametrów zamiast z [int, int]");
    }

    @Override
    public void ustaw(double val, int i) throws ZłeArgumentyFunkcji {
        throw new ZłaIlośćArgumentów(".wycinek() wywołując z parametrem "
                                    + i + " zamiast z [int, int]");
    }

    @Override
    public void ustaw(double val, int i, int j) throws ZłeArgumentyFunkcji {
        ustaw(val, new int[]{i, j});
    }

    @Override
    public double daj() throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar("dla .daj()" + this);
    }

    @Override
    public double daj(int i) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar("dla .daj()" + this);
    }

    @Override
    public double daj(int i, int j) throws ZłeArgumentyFunkcji {
        return daj(new int[]{i, j});
    }  

    //metody niepoprawne    
    @Override
    public void przemnóż(Wektor wektor) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " mnożąc przez wektor");
    }

    // Klasa wewnętrzna, by konstruktory udostępniać użytkownikowi
    // jedynie przez zabezpieczone metody .wycinek() - 
    //               SAM KONSTRUKTOR NIE MA WSZYSTKICH ZABEZPIECZEŃ!
    private class MacierzWycinek extends Macierz {
        // dane
        int góra, dół, lewo, prawo;

        // techniczne
        private MacierzWycinek(double[][] tab, boolean obrót, int[] brzegi) 
                                        throws ZłeArgumentyFunkcji {
            super(tab, false);
            czyObrócona = obrót;
            this.góra = brzegi[0];
            this.dół = brzegi[1] + 1;
            this.lewo = brzegi[2];
            this.prawo = brzegi[3] + 1;
        }

        //metody pomocnicze - głęboka kopia wnętrza wycinka
        @Override
        protected int kordX(int i, int j) {
            return czyObrócona ? j + lewo : i + góra;
        }

        @Override
        protected int kordY(int i, int j) {
            return czyObrócona ? i + góra : j + lewo;
        }

        private double[][] kopiujWnętrze() throws ZłeArgumentyFunkcji {
            int t[] = kształt();
            double[][] res = new double[t[1]][t[0]];
            for(int i = 0; i < t[1]; i++)
                for(int j = 0; j < t[0]; j++)
                    res[i][j] = daj(i, j);
            return res;
        }

        // metody - ich wersje bez sprawdzania błędów, z dod. parametrami
        // są w klasie Macierz, pozostaje sprawdzić błędy dodać opakowania

        @Override
        public int liczbaElementów() {
            return (prawo - lewo) * (dół - góra);
        }
        
        @Override
        public int[] kształt() {
            if(czyObrócona) return new int[]{prawo - lewo, dół - góra};
            return new int[]{dół - góra, prawo - lewo};
        }
    
        @Override
        public Macierz negacja() {
            try {
                Macierz res = new Macierz(kopiujWnętrze(), false);
                res.zaneguj();
                return res;
            } catch(Exception e) {
                System.out.println(e);
                return null;
            }
        }

        @Override
        public MacierzWycinek kopia() {
            int[] brzegi = new int[]{góra, dół - 1, lewo, prawo - 1};
            try {
                return new MacierzWycinek(tab, czyObrócona, brzegi);
            } catch(Exception e) {
                System.out.println(e);
                return null;
            }
            // Catch tylko bo Java wymaga - 
            //                  dobry obiekt i tak kopiuje się poprawnie.
        }

        @Override
        public MacierzWycinek wycinek(int... param) throws ZłeArgumentyFunkcji {
            sprawdźWycinek(param);
            param[0] += góra;
            param[1] += góra;
            param[2] += lewo;
            param[3] += lewo;
            return new MacierzWycinek(tab, czyObrócona, param);
        }

        @Override
        public Macierz suma(Skalar skalar) throws ZłeArgumentyFunkcji {
            nullCheck(skalar, "dla .suma()");
            Macierz res = new Macierz(kopiujWnętrze(), false);
            res.dodaj(skalar);
            return res;
        }
    
        @Override
        public Macierz suma(Macierz macierz) throws ZłeArgumentyFunkcji {
            nullCheck(macierz, "dla .suma()");
            sprawdźIdentKształt(macierz, ".suma()" + this);
            Macierz res = new Macierz(kopiujWnętrze(), false);
            res.dodaj(macierz);
            return res;
        }
    
        @Override
        public Macierz suma(Wektor wektor) throws ZłeArgumentyFunkcji {
            nullCheck(wektor, "dla .suma()");
            sprawdźKształt(wektor);
            Macierz res = new Macierz(kopiujWnętrze(), false);
            res.dodaj(wektor);
            return res;
        }
    
        @Override
        public Macierz iloczyn(Skalar skalar) throws ZłeArgumentyFunkcji {
            nullCheck(skalar, "dla .iloczyn()");
            Macierz res = new Macierz(kopiujWnętrze(), false);
            res.przemnóż(skalar);
            return res;
        }
    
        @Override
        public double daj(int... param) throws ZłeArgumentyFunkcji {
            sprawdźDajUstaw(param);
            param[0] += czyObrócona ? lewo : góra;
            param[1] += czyObrócona ? góra : lewo;
            int logiczna = czyObrócona ? 1 : 0;
            return tab[param[logiczna]][param[1 - logiczna]];
        }

        @Override
        public void ustaw(double val, int... param) throws ZłeArgumentyFunkcji {
            sprawdźDajUstaw(param);
            param[0] += czyObrócona ? lewo : góra;
            param[1] += czyObrócona ? góra : lewo;
            int logiczna = czyObrócona ? 1 : 0;
            tab[param[logiczna]][param[1 - logiczna]] = val;
        }
    }
}
