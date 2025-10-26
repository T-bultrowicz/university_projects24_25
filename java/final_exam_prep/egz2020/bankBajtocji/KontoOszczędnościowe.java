package bankBajtocji;

public class KontoOszczędnościowe extends KontoPojedyncze {

    // dane
    private int odsetki;  // W P.PROCENTOWYCH

    // techniczne
    public KontoOszczędnościowe(String numer, String posiadacz, Bank bank, 
                        String waluta, long stanKonta, int odsetki) {
        super(numer, posiadacz, bank, waluta, stanKonta);
        this.odsetki = odsetki;
    }
    
    // metody
    @Override
    public void koniecMiesiąca() {
        stanKonta += stanKonta * odsetki / 1200; // /(12 * 100)
    }

    @Override
    public boolean czyPrzyjmie(String waluta) {
        return waluta().equals(waluta);
    }

    @Override
    public boolean czyWypłaci(String waluta, long kwota) {
        return false;
    }
}
