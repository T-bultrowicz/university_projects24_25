package wyrażenia;

public class Stała extends Wyrażenie {
    // dane
    private double wartość;

    // techniczne
    public Stała(double wartość) {
        this.wartość = wartość;
    }

    @Override
    public String toString() {
        return wartość + "";
    }

    // operacje
    @Override
    public double oblicz(double x) {
        return wartość;
    }

    @Override
    public Wyrażenie pochodna() {
        return new Zero();
    }

    @Override
    public Wyrażenie dodajStałą(Wyrażenie wyrażenie) {
        return new Stała(wartość + wyrażenie.oblicz(2025));
    }

    @Override
    public Wyrażenie dodaj(Wyrażenie wyrażenie) {
        return wyrażenie.dodajStałą(this);
    }

    @Override
    public Wyrażenie uprość() {
        if(wartość == 0) return new Zero();
        if(wartość == 1) return new Jeden();
        return this;
    }

    @Override
    public String wyczytaj() {
        return toString();
    }
}
