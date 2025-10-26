package biuropodróży;
import java.util.ArrayList;

public class KlientHarmonia extends Klient implements ParametrM {

    // dane
    private final int __K;
    private ArrayList<Wycieczka> wycieczki;
    private int ostKalk;
    private int ostKalkDlaRozmiaru;

    // techniczne
    public KlientHarmonia(String nazwa, int środki, int parametrK) {
        super(nazwa, środki, new Osczędność());
        this.__K = parametrK;
        assert __K <= __M;
        wycieczki = new ArrayList<>();
        ostKalk = 0;
        ostKalkDlaRozmiaru = 0;
    }

    // metody
    private int wyliczDysp(Wycieczka a) {
        int res = 0;
        int rok = a.rozpRok(), dzień = a.rozpDzień();
        for(Miejsce[] mTab : a.miejsca()) {
            for(Miejsce m : mTab) {
                int[] tab = m.bazaAtrakcyjna(rok, dzień);
                for(int i = 0; i < tab.length; i++) {
                    if(i % __K == 0) res += tab[i];
                    else res -= tab[i];
                }
            }
            dzień ++;
            if(dzień == 365) {
                dzień = 0;
                rok++;
            }
        }
        return res;
    }

    @Override
    public void zapisanie(Wycieczka w) {
        środki -= w.cena();
        wycieczki.add(w);
    }
    
    @Override
    public boolean porównaj(Wycieczka a, Wycieczka b) {
        if(ostKalkDlaRozmiaru != wycieczki.size()) {
            ostKalk = 0;
            int i = Math.max(0, wycieczki.size() - __K);
            for(; i < wycieczki.size(); i++) {
                ostKalk += wyliczDysp(wycieczki.get(i));
            }
        }
        return ostKalk + wyliczDysp(a) <= ostKalk + wyliczDysp(b);
    }
}
