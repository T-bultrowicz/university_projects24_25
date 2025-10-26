package tablice;

import java.util.Arrays;
import wyjątki.*;

public class Skalar extends Tablica {

    // Klasa pozwalająca przekazywać double przez referencję,
    // wykorzystywana w wycinkach skalarów
    protected class WrappedDouble {
        private double val;

        //techniczne
        public WrappedDouble(double val) {this.val = val;}
        @Override
        public String toString() {return Double.toString(val);}

        public void ustaw(double val) { this.val = val;}
        public double daj() { return val;}
    }

    //dane
    protected WrappedDouble wartość;

    //techniczne
    public Skalar(double wartość) {
        super(0);
        this.wartość = new WrappedDouble(wartość);
    }

    protected Skalar(WrappedDouble wartość) {
        super(0);
        this.wartość = wartość;
    }

    @Override
    public String toString() {
        return "Skalar: kształt - '[]', wartość - '" + wartość + "'";  
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Skalar)) return false;
        Skalar drugi = (Skalar) obj;
        return doubleRowne(daj(), drugi.daj(), 1e-9);
    }

    // Metody pomocnicze - sprawdzające i zgłaszające wyjątki.
    protected void sprawdźParam(int[] param) throws ZłeArgumentyFunkcji {
        if(param.length != 0) throw new ZłaIlośćArgumentów
            (".wycinek() wywołując dla" + this + " z parametrami " +
                    Arrays.toString(param) + " zamiast []");
    }

    //metody
    @Override
    public int liczbaElementów() {
        return 1;
    }

    @Override
    public int[] kształt() {
        return new int[]{};
    }

    @Override
    public void transponuj() {
        return;
    }

    @Override
    public void zaneguj() {
        wartość.ustaw(wartość.daj() * -1);
    }

    @Override
    public void dodaj(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .dodaj()");
        wartość.ustaw(wartość.daj() + skalar.daj());
    }

    @Override
    public void przemnóż(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .przemnóż()");
        wartość.ustaw(wartość.daj() * skalar.daj());
    }

    @Override
    public void przypisz(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .przypisz()");
        wartość.ustaw(skalar.daj());
    }

    @Override
    public Skalar negacja() {
        return new Skalar(wartość.daj() * -1);
    }

    @Override
    public Skalar kopia() {
        return new Skalar(wartość.daj());
    }

    @Override
    public SkalarWycinek wycinek(int... param) throws ZłeArgumentyFunkcji {
        sprawdźParam(param);
        return new SkalarWycinek(wartość);
    }

    @Override
    public Skalar suma(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .suma()");
        return new Skalar(this.daj() + skalar.daj());
    }

    @Override
    public Macierz suma(Macierz macierz) throws ZłeArgumentyFunkcji {
        nullCheck(macierz, " dla .suma()");
        return macierz.suma(this);
    }

    @Override
    public Wektor suma(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, " dla .suma()");
        return wektor.suma(this);
    }

    @Override
    public Skalar iloczyn(Skalar skalar) throws ZłeArgumentyFunkcji {
        nullCheck(skalar, " dla .iloczyn()");
        return new Skalar(this.daj() * skalar.daj());
    }

    @Override
    public Macierz iloczyn(Macierz macierz) throws ZłeArgumentyFunkcji {
        nullCheck(macierz, " dla .iloczyn()");
        return macierz.iloczyn(this);
    }

    @Override
    public Wektor iloczyn(Wektor wektor) throws ZłeArgumentyFunkcji {
        nullCheck(wektor, " dla .iloczyn()");
        return wektor.iloczyn(this);
    }

    @Override
    public double daj(int... param) throws ZłeArgumentyFunkcji {
        sprawdźParam(param);
        return wartość.daj();
    }

    @Override
    public void ustaw(double val, int... param) throws ZłeArgumentyFunkcji {
        sprawdźParam(param);
        wartość.ustaw(val);
    }

    @Override
    public double daj() {
        return wartość.daj();
    }

    @Override
    public double daj(int i) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar("dla .daj()" + this);
    }

    @Override
    public double daj(int i, int j) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar("dla .daj()" + this);
    }

    @Override
    public void ustaw(double val) {
        wartość.ustaw(val);
    }

    @Override
    public void ustaw(double val, int i) throws ZłeArgumentyFunkcji {
        throw new ZłaIlośćArgumentów(".wycinek() wywołując dla" 
        + this + " z parametrem " + i + " zamiast []");
    }

    @Override
    public void ustaw(double val, int i, int j) throws ZłeArgumentyFunkcji {
        throw new ZłaIlośćArgumentów(".wycinek() wywołując dla" 
        + this + " z parametrami " + i + ", " + j + " zamiast []");
    }
    
    //Metody niepoprawne
    @Override
    public void dodaj(Macierz macierz) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " dodając macierz");
    }

    @Override
    public void dodaj(Wektor wektor) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " dodając wektor");        
    }

    @Override
    public void przemnóż(Macierz macierz) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " mnożąc przez macierz"); 
    }

    @Override
    public void przemnóż(Wektor wektor) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " mnożąc przez wektor");          
    } 

    @Override
    public void przypisz(Macierz macierz) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " przypisując macierz");        
    }

    @Override
    public void przypisz(Wektor wektor) throws ZłeArgumentyFunkcji {
        throw new NiezgodnyWymiar(toString() + " przypisując wektor");  
    }

    // Bez zmian do działania zwykłego skalara 
    //                      - po prostu double przekazany przez referencję
    private class SkalarWycinek extends Skalar {
        private SkalarWycinek(WrappedDouble wartość) {
            super(wartość);
        }

        @Override
        public String toString() {
            return "Wycinek skalara: kształt - '[]', wartość - '" 
                                                        + wartość + "'";             
        }
        
        @Override
        public SkalarWycinek kopia() {
            return new SkalarWycinek(wartość);
        }

    }
}
