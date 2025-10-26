package bankBajtocji;

public abstract class KontoPojedyncze extends Konto {
    
    // dane
    private String waluta;
    protected long stanKonta;

    // techniczne
    protected KontoPojedyncze(String numer, String posiadacz, Bank bank, 
                                    String waluta, long stanKonta) {
        super(numer, posiadacz, bank);
        this.waluta = waluta;
        this.stanKonta = stanKonta;
    }

    // getters
    public String waluta() {
        return waluta;
    }

    public long stanKonta() {
        return stanKonta;
    }

    // metody
    @Override
    public void podepnijDo(KontoZagregowane k) {
        k.podpięcie(this);
    }

    @Override
    public void wpłać(String waluta, long kwota) {
        this.stanKonta += kwota;
    }

    @Override
    public void wypłać(String waluta, long kwota) {
        this.stanKonta -= kwota;
    }
}
