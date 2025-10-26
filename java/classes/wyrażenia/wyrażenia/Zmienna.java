package wyrażenia;

public class Zmienna extends Wyrażenie {

    @Override 
    public String wyczytaj() {
        return toString();
    }

    @Override
    public String toString() {
        return "x";
    }

    @Override
    public double oblicz(double x) {
        return x;
    }

    @Override
    public Wyrażenie pochodna() {
        return new Stała(1.0);
    }
    @Override
    public Wyrażenie uprość() {
        return this;
    }
 }
