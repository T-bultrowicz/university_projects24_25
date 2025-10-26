package wyrażenia;

public abstract class Wyrażenie {

    //dane
    //techniczne
    public int priorytet(){
            return 1000;
    }

    @Override
    abstract public String toString();
    
    // operacje
    public abstract double oblicz(double x);
    public abstract Wyrażenie pochodna();
    public abstract Wyrażenie uprość();
    public abstract String wyczytaj();
    public double całka(double a, double b, int n) {
        if(n <= 0) return 0;
        double h = (b - a) / n;
        double x = a;
        double wynik = 0.0;
        for(int i = 1; i<n; i++){
            //x = a + i*h;  // 31.39999999999985
            x += h;  // inna wersja, inne wady i zalety // 31.39999999999985
            wynik += oblicz(x);
        }
        return (wynik*2+oblicz(a)+oblicz(b))*h/2;
    }
    public Wyrażenie dodaj(Wyrażenie wyrażenie) {
        return wyrażenie.dodajJakoDrugi(this);
    }
    public Wyrażenie dodajJakoDrugi(Wyrażenie wyrażenie) {
        return new Dodaj(wyrażenie, this);
    }
    public  Wyrażenie dodajStałą(Wyrażenie wyrażenie){
        return new Dodaj(wyrażenie, this);
    }
}
