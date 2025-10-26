package osoby;

import instytucje.Wydarzenie;

public class MiłośnikTeatru extends Osoba {

    public MiłośnikTeatru(String imię) {
        super(imię);
    }

    @Override
    public boolean czyAkceptujeszMiejsce(int miejsce, Wydarzenie wydarzenie) {
        return true;
    }
    
}
