package sądy;

public abstract class Sędzia extends OsobaImmunitet implements Comparable<Sędzia> {
    
    // dane
    private Sąd miejscePracy;
    private int ilSpraw;

    // techniczne
    protected Sędzia(String imię, String nazwisko, Sąd miejscePracy) {
        super(imię, nazwisko);
        Weryfikuj.nullVal("Sędzia.konstruktor()", miejscePracy);
        this.miejscePracy = miejscePracy;
        this.ilSpraw = 0;
    }

    @Override
    public int compareTo(Sędzia drugi) {
        return Integer.compare(drugi.ilSpraw(), this.ilSpraw);
    }

    // getters
    public Sąd miejscePracy() {
        return miejscePracy;
    }

    public int ilSpraw() {
        return ilSpraw;
    }

    public void zasługa() {
        ilSpraw = ilSpraw == Integer.MAX_VALUE ? Integer.MAX_VALUE : ilSpraw++;
    }

    // metody
    public abstract Werdykt wydajWyrok(Osoba defensywa, Osoba ofensywa);
}
