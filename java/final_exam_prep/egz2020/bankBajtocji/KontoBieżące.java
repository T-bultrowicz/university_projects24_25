package bankBajtocji;

public class KontoBieżące extends KontoPojedyncze {

    public KontoBieżące(String numer, String posiadacz, Bank bank, 
                                 String waluta, long stanKonta) {
        super(numer, posiadacz, bank, waluta, stanKonta);
    }

    @Override
    public void koniecMiesiąca() {}

    @Override
    public boolean czyPrzyjmie(String waluta) {
        return waluta().equals(waluta);
    }

    @Override
    public boolean czyWypłaci(String waluta, long kwota) {
        return waluta().equals(waluta) && stanKonta >= kwota;
    }

    @Override
    public void funduj(KontoPodpinane k) {
        if(!k.posiadacz().equals(this.posiadacz()))
            throw new InniPosiadacze(this, k);
        if(!k.waluta().equals(waluta()))
            throw new InneWaluty(this, k);
        k.podczep(this);
    }
}
