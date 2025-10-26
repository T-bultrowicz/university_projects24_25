package tablice;

import wyjątki.*;

public abstract class Tablica {
    
    //dane
    private int wymiar;

    //techniczne
    protected Tablica(int wymiar) {
        this.wymiar = wymiar;
    }
    
    public Tablica() {
        this.wymiar = -1;
    }


    protected void nullCheck(Object o, String mes) throws ZłeArgumentyFunkcji {
        if(o == null) throw new ArgumentNull(this + mes);
    }

    protected static boolean doubleRowne(double a, double b, double epsilon) {
        return Math.abs(a - b) < epsilon || (Double.isNaN(a) && Double.isNaN(b));
    }
    
    //metody
    public int wymiar() {
        return this.wymiar;
    }

    public abstract int liczbaElementów();
    public abstract int[] kształt();

    public abstract void transponuj();
    public abstract void zaneguj();
    public abstract void dodaj(Skalar skalar)      throws ZłeArgumentyFunkcji;
    public abstract void dodaj(Macierz macierz)    throws ZłeArgumentyFunkcji;
    public abstract void dodaj(Wektor wektor)      throws ZłeArgumentyFunkcji;
    public abstract void przemnóż(Skalar skalar)   throws ZłeArgumentyFunkcji;
    public abstract void przemnóż(Macierz macierz) throws ZłeArgumentyFunkcji;
    public abstract void przemnóż(Wektor wektor)   throws ZłeArgumentyFunkcji;
    public abstract void przypisz(Skalar skalar)   throws ZłeArgumentyFunkcji;
    public abstract void przypisz(Macierz macierz) throws ZłeArgumentyFunkcji;
    public abstract void przypisz(Wektor wektor)   throws ZłeArgumentyFunkcji;

    public abstract Tablica negacja();
    public abstract Tablica kopia();
    public abstract Tablica wycinek(int... param)   throws ZłeArgumentyFunkcji;
    public abstract Tablica suma(Skalar skalar)     throws ZłeArgumentyFunkcji;
    public abstract Tablica suma(Macierz macierz)   throws ZłeArgumentyFunkcji;
    public abstract Tablica suma(Wektor wektor)     throws ZłeArgumentyFunkcji;
    public abstract Tablica iloczyn(Skalar skalar)  throws ZłeArgumentyFunkcji;
    public abstract Tablica iloczyn(Macierz macierz)throws ZłeArgumentyFunkcji;
    public abstract Tablica iloczyn(Wektor wektor)  throws ZłeArgumentyFunkcji;

    public abstract double daj(int... param) throws ZłeArgumentyFunkcji;
    public abstract double daj() throws ZłeArgumentyFunkcji;
    public abstract double daj(int i) throws ZłeArgumentyFunkcji;
    public abstract double daj(int i, int j) throws ZłeArgumentyFunkcji;
    public abstract void ustaw(double val, int ... param) 
                                             throws ZłeArgumentyFunkcji;
    public abstract void ustaw(double val) throws ZłeArgumentyFunkcji;
    public abstract void ustaw(double val, int i) throws ZłeArgumentyFunkcji;
    public abstract void ustaw(double val, int i, int j) throws ZłeArgumentyFunkcji;
    

    // Przepraszam, za nieeleganckie rozwiązanie poniżej - 
    //                  późno dodawane ogólne operacje

    public Tablica suma(Tablica tablica) throws ZłeArgumentyFunkcji {
        nullCheck(tablica, "dla .suma()");
        if(tablica instanceof Skalar)
            return suma((Skalar) tablica);
        else if(tablica instanceof Wektor)
            return suma((Wektor) tablica);
        else if(tablica instanceof Macierz)
            return suma((Macierz) tablica);
            
        // Na wypadek rozszerzenia projektu - 
        // błąd dla niezaimplementowanego zachowania.
        else
            throw new BrakImplementacji("suma obiekt: " + this);
    }

    public Tablica iloczyn(Tablica tablica) throws ZłeArgumentyFunkcji {
        nullCheck(tablica, "dla .iloczyn()");
        if(tablica instanceof Skalar)
            return iloczyn((Skalar) tablica);
        else if(tablica instanceof Wektor)
            return iloczyn((Wektor) tablica);
        else if(tablica instanceof Macierz)
            return iloczyn((Macierz) tablica);
            
        // Na wypadek rozszerzenia projektu - 
        // błąd dla niezaimplementowanego zachowania.
        else
            throw new BrakImplementacji("iloczyn obiekt: " + this);
    }


    public void dodaj(Tablica tablica) throws ZłeArgumentyFunkcji {
        nullCheck(tablica, "dla .dodaj()");
        if(tablica instanceof Skalar)
            dodaj((Skalar) tablica);
        else if(tablica instanceof Wektor)
            dodaj((Wektor) tablica);
        else if(tablica instanceof Macierz)
            dodaj((Macierz) tablica);
            
        // Na wypadek rozszerzenia projektu - 
        // błąd dla niezaimplementowanego zachowania.
        else
            throw new BrakImplementacji("dodaj obiekt: " + this);
    }

    public void przemnóż(Tablica tablica) throws ZłeArgumentyFunkcji {
        nullCheck(tablica, "dla .przemnóż()");
        if(tablica instanceof Skalar)
            przemnóż((Skalar) tablica);
        else if(tablica instanceof Wektor)
            przemnóż((Wektor) tablica);
        else if(tablica instanceof Macierz)
            przemnóż((Macierz) tablica);
            
        // Na wypadek rozszerzenia projektu - 
        // błąd dla niezaimplementowanego zachowania.
        else
            throw new BrakImplementacji("przemnóż obiekt: " + this);        
    }

    public void przypisz(Tablica tablica) throws ZłeArgumentyFunkcji {
        nullCheck(tablica, "dla .przypisz()");
        if(tablica instanceof Skalar)
            przypisz((Skalar) tablica);
        else if(tablica instanceof Wektor)
            przypisz((Wektor) tablica);
        else if(tablica instanceof Macierz)
            przypisz((Macierz) tablica);
            
        // Na wypadek rozszerzenia projektu - 
        // błąd dla niezaimplementowanego zachowania.
        else
            throw new BrakImplementacji("przypisz obiekt: " + this);        
    }   
}