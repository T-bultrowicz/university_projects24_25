package wyrażenia;

public abstract class Funkcja extends Wyrażenie{
    // dane
    protected Wyrażenie arg;


    // techniczne
    public Funkcja(Wyrażenie arg) {
        this.arg = arg;
    }

    @Override
    public String wyczytaj() {
        return nazwa() + "(" + arg.toString() + ")";
    }

    @Override
    public String toString() {
        Wyrażenie prostyArg = arg.uprość();
        return prostyArg.wyczytaj();
    }

    @Override
    public Wyrażenie uprość() {
        this.arg = arg.uprość();
        return this;
    }

    // operacje
    public abstract String nazwa();
}
