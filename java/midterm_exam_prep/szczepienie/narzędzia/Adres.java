package narzędzia;

import wyjątki.NiezmiennikException;

public class Adres {

    //dane
    public final int adres;

    //techniczne
    public Adres(int adres) throws NiezmiennikException {
        if(adres < 10000 || adres > 99999) throw new NiezmiennikException("Nie 5-cyfrowy adres");
        this.adres = adres;
    } 

    @Override
    public String toString() {
        return ""+adres;
    }

    public int absVAL(Adres a) {
        return (this.adres > a.adres) ? this.adres - a.adres : a.adres - this.adres;
    }
}
