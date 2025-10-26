package bankBajtocji;

public abstract class KontoPodpinane extends KontoPojedyncze {

    // dane
    protected Konto podpięte;

    // techniczne
    protected KontoPodpinane(String numer, String posiadacz, Bank bank, 
                    String waluta, long stanKonta, Konto podpięte) {
        super(numer, posiadacz, bank, waluta, stanKonta);
        if(!bank.zawiera(podpięte))
            throw new WInnymBanku(podpięte, this);
        podpięte.funduj(this);
    }

    // metody
    public void podczep(Konto podpięte) {
        this.podpięte = podpięte;
    }

    @Override
    public boolean czyPrzyjmie(String waluta) {
        return false;
    }
}
