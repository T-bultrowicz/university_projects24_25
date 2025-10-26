package wyrażenia;

public class Odejmij extends Operator{
    // dane

    // techniczne

    public Odejmij(Wyrażenie lewy,
                   Wyrażenie prawy) {
        super(lewy, prawy);
    }

    @Override
    protected String nazwa() {
        return "-";
    }

    @Override
    public double oblicz(double x) {
        return lewy.oblicz(x) - prawy.oblicz(x);
    }

    @Override
    public Wyrażenie pochodna() {
        return new Odejmij(
                     lewy.pochodna(),
                     prawy.pochodna()
                   );
    }

    @Override
    public int priorytet() {
        return 100;
    }

    @Override
    public Wyrażenie uprość() {
        Wyrażenie l = lewy.uprość();
        Wyrażenie p = prawy.uprość();
        if(p instanceof Zero) return l;
        return new Odejmij(l, p);         
    }

}
