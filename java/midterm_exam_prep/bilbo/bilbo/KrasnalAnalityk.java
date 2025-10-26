package bilbo;
import skarb.*;

public class KrasnalAnalityk extends Krasnal {
    
    //dane
    private float zapBezp;

    //techniczne
    public KrasnalAnalityk(String imię, int worek, int uzyty, float zapBezp) {
        super(imię, worek, uzyty);
        this.zapBezp = zapBezp;
        return;
    }

    public KrasnalAnalityk(String imię, int worek, float zapBezp) {
        super(imię, worek);
        this.zapBezp = zapBezp;
        return;
    }

    @Override
    public String toString() {
        String res = super.toString();
        res += " zapas bezpieczeństa " + zapBezp;
        return res;     
    }

    //metody
    public boolean decyzjaKrasnala() {
        float średnia = Skarb.zwróćŚrednia();
        return ((float) worek - uzyty >= średnia + zapBezp); 
    } 
}
