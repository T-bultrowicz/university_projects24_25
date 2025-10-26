package wyrażenia;

public abstract class Operator extends Wyrażenie{
    // dane
    protected Wyrażenie lewy;
    protected Wyrażenie prawy;

    // techniczne


    public Operator(Wyrażenie lewy,
                    Wyrażenie prawy) {
        this.lewy = lewy;
        this.prawy = prawy;
    }

    @Override
    public String wyczytaj() {
        String res = "";
        if(lewy.priorytet() < priorytet()) {
            res += "(" + lewy.wyczytaj() + ")";
        } else {
            res += lewy.wyczytaj();
        }
        res += nazwa();
        if(prawy.priorytet() < priorytet()) {
            res += "(" + prawy.wyczytaj() + ")";
        } else {
            res += prawy.wyczytaj();
        }
        return res;
    }

    @Override
    public String toString() {
        Wyrażenie proste = uprość();
        return proste.wyczytaj();
    }

    protected abstract String nazwa();

}
