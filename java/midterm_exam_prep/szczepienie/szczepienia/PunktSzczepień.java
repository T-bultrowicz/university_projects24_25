package szczepienia;
import narzędzia.*;
import wyjątki.*;

public class PunktSzczepień implements Comparable<PunktSzczepień>{
    
    //dane
    private class Rekord {
        public Pacjent pacjent;
        public Data data;

        public Rekord(Pacjent pacjent, Data data) throws NullPointerException {
            if(data == null || pacjent == null) throw new NullPointerException();
            this.data = data;
            this.pacjent = pacjent;
        }
        
        @Override
        public String toString() {
            return "Pacjent " + pacjent + " obsłużony w dniu " + data + "\n";
        }
    }

    public final Szczepionka typ;
    public final Adres adres;
    public final int przepustowość;
    private DynTablica<Rekord> obsłużeni;
    private Data nwTermin;
    private int ileWNWTermin;

    //techniczne
    public PunktSzczepień(Szczepionka typ, Adres adres, int przepustowość) throws NullPointerException, NiezmiennikException {
        if(typ == null || adres == null) throw new NullPointerException();
        if(przepustowość < 0) throw new NiezmiennikException("Ujemna przepustowść punktu szczepień");

        this.typ = typ;
        this.adres = adres;
        this.przepustowość = przepustowość;
        this.obsłużeni = new DynTablica<Rekord>();
        this.nwTermin = new Data();
        this.ileWNWTermin = 0;
    }

    @Override
    public int compareTo(PunktSzczepień drugi) {
        return Integer.compare(this.adres.adres, drugi.adres.adres);
    }

    //metody
    public Data zwróćTermin() {
        return nwTermin;
    }

    public void wydrukujPacjentów() {
        obsłużeni.wyczytajElementy();
    }

    public void dodajPacjenta(Pacjent a) {
        if(ileWNWTermin == przepustowość) {
            ileWNWTermin = 1;
            nwTermin.next();
        } else {
            ileWNWTermin++;
        }
        obsłużeni.dodajElement(new Rekord(a, nwTermin));
    }
}
