package wybory;

import niezmiennik.NiezmiennikException;

public class Kandydat implements Comparable<Kandydat> {
    
    //dane
    public final String imię;
    public final String nazwisko;
    public final int ilośćGłosów;
    private boolean czyWygrano;

    //techniczne
    public Kandydat(String imię, String nazwisko, int ilośćGłosów) throws NullPointerException, NiezmiennikException {
        if(imię == null || nazwisko == null) throw new NullPointerException();
        if(ilośćGłosów < 0) throw new NiezmiennikException("Ujemna ilość głosów");
        if(imię == "" || nazwisko == "") throw new NiezmiennikException("Puste imię/nazwisko");
        this.ilośćGłosów = ilośćGłosów;
        this.imię = imię;
        this.nazwisko = nazwisko;
        this.czyWygrano = false;
    }

    @Override
    public int compareTo(Kandydat drugiKandydat) {
        return Integer.compare(drugiKandydat.ilośćGłosów, this.ilośćGłosów);
    }

    public void setczyWygrano(boolean var) {
        czyWygrano = var;
    }

    public boolean getczyWygrano() {
        return czyWygrano;
    }

    
}
