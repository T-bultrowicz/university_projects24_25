package bankBajtocji;

public abstract class Konto {
    
    // dane
    private String numer;
    private String posiadacz;

    // techniczne
    protected Konto(String numer, String posiadacz, Bank bank) {
        this.numer = numer;
        this.posiadacz = posiadacz;
        bank.zapiszKonto(this);
    }

    @Override
    public String toString() {
        return "Konto numer " + numer;
    }

    // getters
    public String numer() {
        return numer;
    }

    public String posiadacz() {
        return posiadacz;
    }

    public void funduj(KontoPodpinane k) {
        throw new UnsupportedOperationException("Dude wtf???");
    }
    abstract public void koniecMiesiąca();
    abstract public boolean czyPrzyjmie(String waluta);
    abstract public boolean czyWypłaci(String waluta, long kwota);
    abstract public void wypłać(String waluta, long kwota);
    abstract public void wpłać(String waluta, long kwota);
    abstract protected void podepnijDo(KontoZagregowane k);
}
