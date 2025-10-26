package tablice;

import java.util.Arrays;
import wyjątki.*;

public class Wektor extends Tablica {

    //dane
    protected double[] tab;
    protected boolean poziomy;

    //techniczne
    
    public Wektor(double[] tab, boolean poziomy, boolean kopiuj) 
                                            throws ZłeArgumentyFunkcji {
        super(1);
        nullCheck(tab, "dla .Wektor()");
        if(tab.length == 0) throw new ZłyIndeks
            ("konstruktorze Wektor(), podana tablica ma zerowy wymiar");

        this.tab = kopiuj ? tab.clone() : tab;
        this.poziomy = poziomy;
    }

    public Wektor(double[] tab, boolean poziomy) throws ZłeArgumentyFunkcji {
        super(1);
        nullCheck(tab, "dla .Wektor()");
        if(tab.length == 0) throw new ZłyIndeks
            ("konstruktorze Wektor(), podana tablica ma zerowy wymiar");
        this.tab = tab.clone();
        this.poziomy = poziomy;        
    }

    public Wektor(int x, boolean poziomy) throws ZłeArgumentyFunkcji {
        if (x <= 0)
            throw new ZłyIndeks
            ("konstruktorze Wektor(), wprowadzono zerowy/ujemny wymiar");

        tab = new double[x];
        this.poziomy = poziomy;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Wektor: kształt - '" + Arrays.toString(kształt()));
        sb.append("', orientacja - '");
        sb.append(poziomy ? "pozioma',\n" : "pionowa',\n");
        sb.append(Arrays.toString(tab));
        return sb.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Wektor)) return false;
        Wektor drugi = (Wektor) obj;
    
        if (liczbaElementów() != drugi.liczbaElementów()) return false;
        if (orientacja() != drugi.orientacja()) return false;
    
        try {
            for (int i = 0; i < this.liczbaElementów(); i++) {
                if (!doubleRowne(daj(i), drugi.daj(i), 1e-9)) return false;
            }
        } catch(Exception e) {System.out.println(e);}
        return true;
    }

    // Metody wewnętrzne, sprawdzające i wyrzucające wyjątki.

    protected int kordX(int i) {
        return i;
    }

    private void sprawdźKształtRozmiar(Wektor w) throws ZłeArgumentyFunkcji {
        if (w.orientacja() != poziomy
            || w.liczbaElementów() != tab.length) {
            throw new NiezgodnyKształt(this + 
            ",\n orientacja/kształt inne niż dla argumentu" + w);
        }   
    }

    protected void sprawdźDajUstaw(int[] param) throws ZłeArgumentyFunkcji {
        if (param.length != 1) throw new ZłaIlośćArgumentów
            (".daj() wywołując dla" + this + "\n Z parametrami " +
                    Arrays.toString(param) + " zamiast [int].");
        if (param[0] < 0 || param[0] >= liczbaElementów())
            throw new ZłyIndeks(this + " dla .daj()");
    }

    protected void sprawdźWycinek(int[] param) throws ZłeArgumentyFunkcji {
        if (param.length != 2) throw new ZłaIlośćArgumentów
            (".wycinek() wywołując dla" + this + "\n Z parametrami " +
                Arrays.toString(param) + " zamiast [int_lo, int_hi].");
        if (param[0] > param[1]) 
            throw new ZłyIndeks(this + 
            " \n dla .wycinek(), pierwszy parametr nie może być większy!");
        if (param[0] < 0 || param[1] >= liczbaElementów()) 
            throw new ZłyIndeks(".wycinek(), " + this + "\n Podano " + 
                        Arrays.toString(param) + " spoza zakresu wektora.");
    }

    //metody
    public boolean orientacja() {
        return poziomy;
    }

    @Override
    public int liczbaElementów() {
        return tab.length;
    }

    @Override
    public int[] kształt() {
        return new int[]{tab.length};
    }

    @Override
    public void transponuj() {
        poziomy = !poziomy;
    }

    // Metody udostępnione użytkownikom - sprawdzają i zgłąszają
    // wyjątki.
    @Override
    public void zaneguj() {
        for(int i = 0; i < liczbaElementów(); i++) {
            tab[kordX(i)] *= -1;
        }
    }

    @Override
    public void dodaj(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .dodaj()");
        double val = skalar.daj();
        for(int i = 0; i < liczbaElementów(); i++) {
            tab[kordX(i)] += val;
        }
    }

    @Override
    public void dodaj(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, " dla .dodaj()");
        sprawdźKształtRozmiar(wektor);
        for(int i = 0; i < liczbaElementów(); i++) {
            tab[kordX(i)] += wektor.daj(i);
        }     
    }

    @Override
    public void przemnóż(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .przemnóż()");
        double val = skalar.daj();
        for(int i = 0; i < liczbaElementów(); i++) {
            tab[kordX(i)] *= val;
        }
    }

    @Override
    public void przypisz(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .przypisz()");
        double val = skalar.daj();
        for(int i = 0; i < liczbaElementów(); i++) {
            tab[kordX(i)] = val;
        }
    }

    @Override
    public void przypisz(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, " dla .przypisz()");
        if(tab.length != wektor.liczbaElementów())
            throw new NiezgodnyKształt(".przypisz() dla '" + 
            this + "'\n oraz '" + wektor + "'\n, liczba el. nie zgodna"); 
        for(int i = 0; i < liczbaElementów(); i++) {
            tab[kordX(i)] = wektor.daj(i);
        }
        poziomy = wektor.orientacja();
    }

    @Override
    public Wektor negacja() {
        try {
            Wektor res = kopia();
            res.zaneguj();
            return res;
        } catch(Exception e) {
            System.out.println(e);
            return null;
        }
    }

    @Override
    public Wektor kopia() {
        try {
            return new Wektor(tab, poziomy, true);
        } catch(ZłeArgumentyFunkcji zaf) {
            System.out.println(zaf);
            return null;
        }
    }

    @Override
    public WektorWycinek wycinek(int... param) throws ZłeArgumentyFunkcji {
        sprawdźWycinek(param);
        return new WektorWycinek(tab, poziomy, param);
    }

    @Override
    public Wektor suma(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .suma()");
        Wektor res = kopia();
        res.dodaj(skalar);
        return res;
    }

    @Override
    public Macierz suma(Macierz macierz) throws ZłeArgumentyFunkcji {
        nullCheck(macierz, " dla .suma()");
        return macierz.suma(this);
    }

    @Override
    public Wektor suma(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, " dla .suma()");
        sprawdźKształtRozmiar(wektor);
        Wektor res = kopia();
        res.dodaj(wektor);
        return res;
    }

    @Override
    public Wektor iloczyn(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .iloczyn()");
        Wektor res = kopia();
        res.przemnóż(skalar);
        return res;
    }

    @Override
    public Wektor iloczyn(Macierz macierz) throws ZłeArgumentyFunkcji {
        nullCheck(macierz, " dla .iloczyn()");
        return macierz.iloczyn(this);
    }

    @Override
    public Tablica iloczyn(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, "dla .iloczyn()");

        //pierwszy pionowy drugi poziomy
        if (!poziomy && wektor.orientacja()) {
            int k = liczbaElementów();
            int l = wektor.liczbaElementów();
            Macierz res = new Macierz(k, l);
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < l; j++) {
                    res.ustaw(daj(i) * wektor.daj(j), i, j);
                }
            }
            return res;
        }

        if (wektor.liczbaElementów() != tab.length) 
            throw new NiezgodnyKształt("dla .iloczyn() " + this +
                "\n ma inna liczbę elementów niż " + wektor);
        double val = 0;
        for  (int i = 0; i < tab.length; i++) {
            val += daj(i) * wektor.daj(i);
        }
        //oba tej samej orientacji
        if (poziomy == wektor.orientacja()) {
            return new Skalar(val);
        }
        //pierwszy poziomy drugi pionowy
        Macierz res = new Macierz(1, 1);
        res.ustaw(val, 0, 0);
        return res;           
    }

    @Override
    public double daj(int... param) throws ZłeArgumentyFunkcji {
        sprawdźDajUstaw(param);
        return tab[param[0]];
    }

    @Override
    public void ustaw(double val, int... param) throws ZłeArgumentyFunkcji {
        sprawdźDajUstaw(param);
        tab[param[0]] = val;
    }

    @Override
    public void ustaw(double val) throws ZłeArgumentyFunkcji {
        throw new ZłaIlośćArgumentów(".wycinek() wywołując" + 
                                " bez parametrów zamiast z [int]");
    }

    @Override
    public void ustaw(double val, int i) throws ZłeArgumentyFunkcji {
        ustaw(val, new int[]{i});
    }

    @Override
    public void ustaw(double val, int i, int j) throws ZłeArgumentyFunkcji {
        throw new ZłaIlośćArgumentów(".wycinek() wywołując z parametrami " + 
                            i + ", " + j + " zamiast z [int]");
    }

    @Override
    public double daj() throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar("dla .daj()" + this);
    }

    @Override
    public double daj(int i) throws ZłeArgumentyFunkcji {
        return daj(new int[]{i});
    }

    @Override
    public double daj(int i, int j) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar("dla .daj()" + this);
    }  

    //metody niepoprawne
    @Override
    public void dodaj(Macierz macierz) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " dodając macierz");
    }

    @Override
    public void przemnóż(Macierz macierz) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " mnożąc przez macierz");
    }

    @Override
    public void przypisz(Macierz macierz) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " przypisując macierz");
    }   

    @Override
    public void przemnóż(Wektor wektor) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " złe działanie wektor*wektor");
    }

    // Klasa wewnętrzna, by konstruktory udostępniać użytkownikowi
    // jedynie przez zabezpieczone metody .wycinek() - 
    //               SAM KONSTRUKTOR NIE MA WSZYSTKICH ZABEZPIECZEŃ!
    public class WektorWycinek extends Wektor {
        // dane
        int lewo, prawo;

        // techniczne
        private WektorWycinek(double[] tab, boolean poziomy, int[] brzeg)
                                                throws ZłeArgumentyFunkcji {
            super(tab, poziomy, false);
            this.lewo = brzeg[0];
            this.prawo = brzeg[1] + 1;
        }

        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append("Wycinek wektora: kształt - '");
            sb.append(Arrays.toString(kształt()));
            sb.append("', orientacja - '");
            sb.append(poziomy ? "pozioma',\n" : "pionowa',\n");
            sb.append(Arrays.toString(Arrays.copyOfRange(tab, lewo, prawo)));
            return sb.toString();
        }

        //metody pomocnicze - kopiujWnętrze() = głęboka kopia wnętrza wycinka
        @Override
        protected int kordX(int i) {
            return i + lewo;
        }

        private double[] kopiujWnętrze() {
            return Arrays.copyOfRange(tab, lewo, prawo);
        }

        // metody dla użytkownika
        @Override
        public int liczbaElementów() {
            return prawo - lewo;
        }
        
        @Override
        public int[] kształt() {
            return new int[]{prawo - lewo};
        }

        @Override
        public Wektor negacja() {
            try {
                Wektor res = new Wektor(kopiujWnętrze(), poziomy, false);
                res.zaneguj();
                return res;
            } catch(Exception e) {
                System.out.println(e);
                return null;
            }
        }

        @Override
        public WektorWycinek kopia() {
            int[] brzegi = new int[]{lewo, prawo - 1};
            try {
                return new WektorWycinek(tab, poziomy, brzegi);
            } catch(Exception e) {
                System.out.println(e);
                return null;
            }
        }

        @Override
        public WektorWycinek wycinek(int... param) throws ZłeArgumentyFunkcji {
            sprawdźWycinek(param);
            param[0] += lewo;
            param[1] += lewo;
            return new WektorWycinek(tab, poziomy, param);
        }

        @Override
        public Wektor suma(Skalar skalar) throws ZłeArgumentyFunkcji {
            nullCheck(skalar, "dla .suma()");
            Wektor res = new Wektor(kopiujWnętrze(), poziomy, false);
            res.dodaj(skalar);
            return res;
        }

        @Override
        public Wektor suma(Wektor wektor) throws ZłeArgumentyFunkcji {
            nullCheck(wektor, " dla .suma()");
            sprawdźKształtRozmiar(wektor);
            Wektor res = new Wektor(kopiujWnętrze(), poziomy, false);
            res.dodaj(wektor);
            return res;           
        }

        @Override
        public Wektor iloczyn(Skalar skalar) throws ZłeArgumentyFunkcji {
            nullCheck(skalar, "dla .iloczyn()");
            Wektor res = new Wektor(kopiujWnętrze(), poziomy, false);
            res.przemnóż(skalar);
            return res;
        }
    
        @Override
        public double daj(int... param) throws ZłeArgumentyFunkcji {
            sprawdźDajUstaw(param);
            return tab[param[0] + lewo];
        }

        @Override
        public void ustaw(double val, int ... param) throws ZłeArgumentyFunkcji {
            sprawdźDajUstaw(param);
            tab[param[0] + lewo] = val;       
        }
    }
}
