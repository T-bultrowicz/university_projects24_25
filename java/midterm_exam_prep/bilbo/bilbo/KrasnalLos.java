package bilbo;
import java.util.Random;

public class KrasnalLos extends Krasnal{
    
    //dane
    private float wspRyzyka;

    //techniczne
    public KrasnalLos(String imię, int worek, int uzyty, float wspRyzyka) {
        super(imię, worek, uzyty);
        assert(wspRyzyka >= 0 && wspRyzyka < 1);
        this.wspRyzyka = wspRyzyka;
    }

    public KrasnalLos(String imię, int worek, float wspRyzyka) {
        super(imię, worek);
        assert(wspRyzyka >= 0 && wspRyzyka < 1);
        this.wspRyzyka = wspRyzyka;       
    }

    @Override
    public String toString() {
        String res = super.toString();
        res += " wsp ryzyka" + wspRyzyka;
        return res;
    }

    @Override
    public void rozpatrz(int nowySkarb, boolean decyzja) {
        if(!decyzja) {
            czyGraDalej = false;
            return;
        }
        if(nowySkarb + uzyty > worek) {
            uzyty = 0;
            czyGraDalej = false;
            return;
        }
        uzyty += nowySkarb;
        wspRyzyka -= 0.05;
        return;
    }

    //metody
    public boolean decyzjaKrasnala() {
        Random rng = new Random();
        float random = rng.nextFloat();
        return random <= wspRyzyka;
    }
}
