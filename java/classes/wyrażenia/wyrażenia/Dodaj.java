package wyrażenia;

public class Dodaj extends Operator{
    // dane


    @Override
    public int priorytet() {
        return 100;
    }
    // techniczne

    public Dodaj(Wyrażenie lewy,
                 Wyrażenie prawy) {
        super(lewy, prawy);
    }

    //operacje

    @Override
    protected String nazwa() {
        return "+";
    }

    @Override
    public double oblicz(double x) {
        return lewy.oblicz(x) + prawy.oblicz(x);
    }

    @Override
    public Wyrażenie pochodna() {
        return new Dodaj(
                     lewy.pochodna(),
                     prawy.pochodna()
                   );
    }

    @Override
    public Wyrażenie uprość() {
        Wyrażenie l = lewy.uprość();
        Wyrażenie p = prawy.uprość();
        if(l instanceof Zero) return p;
        if(p instanceof Zero) return l;
        if(l instanceof Stała && p instanceof Stała)
            return new Stała(l.oblicz(0) + p.oblicz(0)).uprość();
        return new Dodaj(l, p); 
    }
}
