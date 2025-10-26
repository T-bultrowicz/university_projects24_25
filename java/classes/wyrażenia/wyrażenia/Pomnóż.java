package wyrażenia;

public class Pomnóż extends Operator{
    // dane

    // techniczne
    public Pomnóż(Wyrażenie lewy,
                  Wyrażenie prawy) {
        super(lewy, prawy);
    }

    @Override
    public int priorytet() {
        return 500;
    }

    // operacje

    @Override
    protected String nazwa() {
        return "*";
    }

    @Override
    public double oblicz(double x) {
        return lewy.oblicz(x) * prawy.oblicz(x);
    }

    @Override
    public Wyrażenie pochodna() {
        return new Dodaj(
                     new Pomnóż(
                         lewy.pochodna(),
                         prawy
                     ),
                     new Pomnóż(
                         lewy,
                         prawy.pochodna()
                     )
                   );
    }

    @Override
    public Wyrażenie uprość() {
        Wyrażenie l = lewy.uprość();
        Wyrażenie p = prawy.uprość();
        if(l instanceof Zero) return new Zero();
        if(p instanceof Zero) return new Zero();
        if(l instanceof Jeden) return p;
        if(p instanceof Jeden) return l;
        return new Pomnóż(l, p);
    }
}
