package bankBajtocji;

public class KontoKartowe extends KontoPodpinane {

    // dane
    private long limit;

    // techniczne
    public KontoKartowe(String numer, String posiadacz, Bank bank, 
    String waluta, Konto podpięte, long limit) {
        super(numer, posiadacz, bank, waluta, 0, podpięte);
        this.limit = limit;
    }
    
    // getters
    public long limit() {
        return limit;
    }

    public void setLimit(long nowy) {
        limit = nowy;
    }

    // metody
    @Override
    public void koniecMiesiąca() {
        String mes = "Konto kartowe wytowrzyło za duży dług";
        if(!podpięte.czyWypłaci(waluta(), stanKonta))
            throw new OperacjaKońcaMiesiąca(mes);
        podpięte.wypłać(waluta(), -stanKonta);
        stanKonta = 0;
    }

    @Override
    public boolean czyWypłaci(String waluta, long kwota) {
        return waluta().equals(waluta) && kwota <= limit();
    }
}
