package bankBajtocji;
import java.util.HashMap;
import java.util.Collection;

public class KontoZagregowane extends Konto {
    
    // dane
    private HashMap<String, Konto> konta;

    // techniczne
    public KontoZagregowane(String numer, String posiadacz, 
                            Bank bank, Collection<Konto> konta) {
        super(numer, posiadacz, bank);
        this.konta = new HashMap<>();
        for(Konto k : konta) {
            k.podepnijDo(this);
        }
    }

    public KontoZagregowane(String numer, String posiadacz, Bank bank) {
        super(numer, posiadacz, bank);
        this.konta = new HashMap<>();
    }

    // metody

    @Override
    public boolean czyPrzyjmie(String waluta) {
        Konto k = konta.get(waluta);
        if(k == null) return false;
        return k.czyPrzyjmie(waluta);
    }

    @Override
    public boolean czyWypłaci(String waluta, long kwota) {
        Konto k = konta.get(waluta);
        if(k == null) return false;
        return k.czyWypłaci(waluta, kwota);
    }

    @Override
    public void podepnijDo(KontoZagregowane k) {
        throw new ZagregowaneExcep(k);
    }

    @Override
    public void koniecMiesiąca() {}

    @Override
    public void wpłać(String waluta, long kwota) {
        konta.get(waluta).wpłać(waluta, kwota);
    }

    @Override
    public void wypłać(String waluta, long kwota) {
        konta.get(waluta).wypłać(waluta, kwota);
    }

    public void podpięcie(KontoPojedyncze a) {
        if(!a.posiadacz().equals(posiadacz()))
            throw new InniPosiadacze(this, a);
        konta.putIfAbsent(a.waluta(), a);
    }
}
