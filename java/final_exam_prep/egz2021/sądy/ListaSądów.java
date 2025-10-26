package sądy;
import wyjątki.BrakSądów;
import java.util.ArrayList;

public class ListaSądów {

    // dane
    private ArrayList<Sąd> najniższa;
    private ArrayList<Sąd> wszystkie;
    private int iteracja;

    // techniczne
    public ListaSądów() {
        najniższa = new ArrayList<>();
        wszystkie = new ArrayList<>();
        iteracja = 0;
    }

    // metody
    public Sąd przydzielSąd() {
        if(najniższa.isEmpty()) throw new BrakSądów();
        if(iteracja >= najniższa.size()) {
            iteracja %= najniższa.size();
        }
        return najniższa.get(iteracja++);
    }

    public void dodaj(Sąd s) {
        Weryfikuj.nullVal("ListaSądów.dodaj()", s);
        if(s.najniższa()) {
            najniższa.add(s);
        }
        wszystkie.add(s);
    }
}
