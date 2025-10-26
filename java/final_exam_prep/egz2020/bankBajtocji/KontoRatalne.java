package bankBajtocji;

public class KontoRatalne extends KontoPodpinane {

    // dane
    private final long rataKapitałowa;
    private int ileRat;
    private final int stopaRatalna;

    // techniczne
    public KontoRatalne(String numer, String posiadacz, Bank bank, String 
    waluta, long stanKonta, Konto podpięte, int ileRat, int stopaRatalna) {
        super(numer, posiadacz, bank, waluta, stanKonta, podpięte);
        this.ileRat = ileRat;
        this.stopaRatalna = stopaRatalna;
        this.rataKapitałowa = stanKonta / ileRat;
    }


    @Override
    public void koniecMiesiąca() {
        if(ileRat == 0) {}
            //TODO
        long kwota = rataKapitałowa + 
                (stanKonta * stopaRatalna / 100);
        if(!podpięte.czyWypłaci(waluta(), kwota))
            throw new OperacjaKońcaMiesiąca("kontoRatalne");
        podpięte.wypłać(waluta(), kwota);
        stanKonta -= kwota;
        ileRat--;
    }

    @Override
    public boolean czyWypłaci(String waluta, long kwota) {
        return false;
    }
}