package osoby;
import instytucje.*;

public abstract class Osoba {
    
    //dane
    private String imię;
    private Bilet bilet;

    //techniczne
    public Osoba(String imię) {
        this.imię = imię;
    }

    @Override
    public String toString() {
        return "Osoba{imię=" + imię + ", bilet =" + bilet + "}";
    }

    //operacje
    public void weźBilet(Bilet bilet) {
        this.bilet = bilet;
    }

    public void oddajBilet() {
        bilet = null;
    }

    public String imię() {
        return imię;
    }

    public abstract boolean czyAkceptujeszMiejsce(int miejsce, Wydarzenie wydarzenie);
}
