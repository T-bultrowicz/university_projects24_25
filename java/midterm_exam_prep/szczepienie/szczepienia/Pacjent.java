package szczepienia;
import wyjątki.*;
import narzędzia.*;

public class Pacjent {
    
    //dane
    public final String imię;
    public final String nazwisko;
    public final Szczepionka typ;
    public final Adres adres;
    public final Województwo województwo;
    public final int mxDyst;
    private Data dataSzczepienia;

    //techniczne
    public Pacjent(String imię, String nazwisko, Szczepionka typ, Adres adres, 
            Województwo województwo, int mxDyst) throws NullPointerException, NiezmiennikException {
        if(imię == null || nazwisko == null || typ == null || adres == null || województwo == null)
            throw new NullPointerException();
        if(mxDyst < 0) throw new NiezmiennikException("Pacjent nie może mieć ujemnego dystansu");
        if(imię == "" || nazwisko == "") throw new NiezmiennikException("Imię/nazwisko, nie może być pustym polem");

        this.imię = imię;
        this.nazwisko = nazwisko;
        this.typ = typ;
        this.adres = adres;
        this.województwo = województwo;
        this.mxDyst = mxDyst;
        this.dataSzczepienia = null;
    }

    //metody
    public boolean czyZaszczepiony() {
        return dataSzczepienia != null;
    }

    public Data dataSzczepienia() {
        return dataSzczepienia;
    }

    @Override
    public String toString() {
        return imię + " " + nazwisko + "zamieszkały" + adres + "\n";
    }

    public void zapiszDoPunktu(PunktSzczepień punkt) {
        if(czyZaszczepiony()) return;
        punkt.dodajPacjenta(this);
        dataSzczepienia = punkt.zwróćTermin();
    }

    public void znajdźZapiszPunkt() throws NiezmiennikException, BrakPasującegoException{
        PunktSzczepień a = CentralnaPoradaSzczepień.znajdźNajlepszy(this);
        if(a != null) this.zapiszDoPunktu(a);
    }
}
