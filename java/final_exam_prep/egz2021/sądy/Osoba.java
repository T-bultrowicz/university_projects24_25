package sądy;

public abstract class Osoba {
    
    // dane
    private boolean immunitet;
    private String imię, nazwisko;

    // techniczne
    protected Osoba(String imię, String nazwisko, boolean immunitet) {
        Weryfikuj.nullVal("Osoba.konstruktor()", imię, nazwisko);
        this.imię = imię;
        this.nazwisko = nazwisko;
        this.immunitet = immunitet;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(imię).append(" ").append(nazwisko).append(" ");
        sb.append(immunitet ? " posiada immunitet" : " nie posiada immunitetu");
        return sb.toString();
    }

    // getters
    public String imię() {
        return imię;
    }

    public String nazwisko() {
        return nazwisko;
    }

    public boolean immunitet() {
        return immunitet;
    }

    // metody
    abstract public long ileRząda();
    abstract public String sprawozdanie();
    abstract public void przyjmijKarę(long kwota);
    abstract public void przyjmijOdszkodowanie(long kwota);
    abstract public void inicjujSpór(Osoba oskarżana);
}
