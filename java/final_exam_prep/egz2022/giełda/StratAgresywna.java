package giełda;

import java.util.ArrayList;

public class StratAgresywna implements Strategia {
    
    // dane
    private int parametrSpadku;

    // techniczne
    public StratAgresywna(int parametrSpadku) {
        this.parametrSpadku = parametrSpadku;
    }

    @Override
    public String toString() {
        return "Strategia agresywna o parametrze p=" + parametrSpadku;
    }

    // metody
    @Override
    public int ileKupić(Zasób z, Giełda g, ArrayList<Program> p) {
        if(g.cena(z, 1) * (100 - parametrSpadku) / 100 <= g.cena(z)) {
            return Math.min();
        }
        return 0;
    }

    @Override
    public boolean czySprzedać(Inwestycja i, Giełda g, ArrayList<Program> p) {
        for(Program dildo : p) {
            if(dildo.zmaleje(i, g))
                return true;
        }
        return false;
    }

    @Override
    public void dodaj(Broker b, Program p) {
        b.dodajBezpiecznieProgram(p);
    }


}
