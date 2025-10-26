package bilbo;

public class KrasnalProcent extends Krasnal{
    
    //dane
    private float pasProcent;

    //techniczne
    public KrasnalProcent(String imię, int worek, int uzyty, float pasProcent) {
        super(imię, worek, uzyty);
        assert(pasProcent > 0 && pasProcent <= 1);
        this.pasProcent = pasProcent;
    }

    public KrasnalProcent(String imię, int worek, float pasProcent) {
        super(imię, worek);
        assert(pasProcent > 0 && pasProcent <= 1);
        this.pasProcent = pasProcent;       
    }

    @Override
    public String toString() {
        String res = super.toString();
        res += " pas procent" + pasProcent;
        return res;
    }

    //metody
    public boolean decyzjaKrasnala() {
        return ((float) uzyty / worek < pasProcent);
    }
}