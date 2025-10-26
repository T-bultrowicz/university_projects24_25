package wyrażenia;

public class Sin extends Funkcja {

    // dane

    // techniczne
    public Sin(Wyrażenie arg){
        super(arg);
    }

    // operacje
    @Override
    public String nazwa() {
        return "sin";
    }

    @Override
    public double oblicz(double x) {
        return Math.sin(arg.oblicz(x));
    }

    @Override
    public Wyrażenie pochodna() {
        return new Pomnóż(
            new Cos(arg), arg.pochodna());
    }

}
