package bilbo;

public abstract class Krasnal {
    
    //dane
    protected String imię;
    protected int worek;
    protected int uzyty;
    protected boolean czyGraDalej;

    //techniczne
    public Krasnal(String imię, int worek) {
        assert(imię != null && worek > 0);
        this.imię = imię;
        this.worek = worek;
        this.uzyty = 0;
        this.czyGraDalej = true;
    }

    public Krasnal(String imię, int worek, int uzyty) {
        assert(imię != null && worek > 0 && uzyty > 0 && uzyty <= worek);
        this.imię = imię;
        this.worek = worek;
        this.uzyty = uzyty;
        this.czyGraDalej = true;
    }

    @Override
    public String toString() {
        String res = "Imię: " + imię + " roz. worka " + worek + " uzywa " + uzyty + "\n";
        res += (czyGraDalej) ? "| gra dalej |" : "| nie gra dalej \n";
        return res;
    }

    public boolean getCzyGraDalej() {
        return czyGraDalej;
    }

    public int getUzyty() {
        return uzyty;
    }

    //metody
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
        return;
    }

    public abstract boolean decyzjaKrasnala();
}
