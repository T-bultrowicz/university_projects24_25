package sądy;
import java.util.PriorityQueue;
import wyjątki.Najwyższa;

public abstract class Sąd {

    // dane
    private String nazwa;
    private Sąd wyższy;
    private PriorityQueue<Sędzia> sędziowie;
    private boolean najniższa;

    // techniczne
    protected Sąd(String nazwa, Sąd wyższy, ListaSądów lista, boolean ins) {
        Weryfikuj.nullVal("Sąd.konstruktor()", nazwa, lista);
        if(ins) Weryfikuj.nullVal("Sąd.kontruktor()", wyższy);
        this.nazwa = nazwa;
        this.wyższy = wyższy;
        this.sędziowie = new PriorityQueue<>();
        najniższa = ins;
        lista.dodaj(this);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Sąd ").append(nazwa);
        return sb.toString();
    }

    // getters
    public Sąd wyższaInstancja() throws Najwyższa {
        if(wyższy == null) throw new Najwyższa();
        return wyższy;
    }

    public boolean najniższa() {
        return najniższa;
    }

    // metody
    public void zatrudnij(Sędzia s) {
        Weryfikuj.nullVal("Sąd.zatrudnij()", s);
        sędziowie.add(s);
    }

    public Werdykt rozpatrzSprawę(Osoba defensywa, Osoba ofensywa) {
        Sędzia sędzia = sędziowie.poll();
        Werdykt res = sędzia.wydajWyrok(defensywa, ofensywa);
        sędzia.zasługa();
        sędziowie.add(sędzia);
        return res;
    } 
}
