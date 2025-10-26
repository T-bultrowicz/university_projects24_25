package narzędzia;
import wyjątki.*;

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

    public boolean wczDzielnicaOd(Adres a) {
        return (this.adres / 100 < a.adres / 100);
    }
}
