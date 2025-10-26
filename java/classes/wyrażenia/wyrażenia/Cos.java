package wyrażenia;

public class Cos extends Funkcja{
    public Cos(Wyrażenie arg) {
        super(arg);
    }

    @Override
    public String nazwa() {
        return "cos";
    }

    @Override
    public double oblicz(double x) {
        return Math.cos(arg.oblicz(x));
    }

    @Override
    public Wyrażenie pochodna() {
        return new Pomnóż(
            new Odejmij(new Stała(0),
                           new Sin(arg)),
            arg.pochodna()
        );
    }
}
