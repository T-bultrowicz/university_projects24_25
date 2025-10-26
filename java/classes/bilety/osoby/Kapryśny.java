package osoby;
import instytucje.*;

public class Kapryśny extends Osoba {

    public Kapryśny(String imię) {
        super(imię);
    }

    @Override
    public boolean czyAkceptujeszMiejsce(int miejsce, Wydarzenie wydarzenie) {
        return RNG.nextBoolean();
    }
    
}
