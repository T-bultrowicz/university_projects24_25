package przydzial;

import niezmiennik.NiezmiennikException;

public class Klasa {
    
    //dane
    public final String nazwa;
    private int liczbaPrzyjętych;
    public final int maksymalnaLiczba;
    private Uczeń[] listaPrzyjętych;

    //techniczne
    public Klasa(String nazwa, int maksymalnaLiczba) throws NullPointerException, NiezmiennikException {
        if(nazwa == null) throw new NullPointerException();
        if(maksymalnaLiczba <= 10) throw new NiezmiennikException("Za mała pojemność klasy");
        if(maksymalnaLiczba >= 69) throw new NiezmiennikException("Za duża pojemność klasy");
        if(nazwa == "") throw new NiezmiennikException("Pusta nazwa klasy");
        this.nazwa = nazwa;
        this.maksymalnaLiczba = maksymalnaLiczba;
        this.liczbaPrzyjętych = 0;
    }

    public void ustawListęPrzyjętych(Uczeń[] nowaLista) throws NullPointerException {
        if(nowaLista == null) throw new NullPointerException();
        for(Uczeń a : nowaLista) 
            if(a == null) throw new NullPointerException();

        listaPrzyjętych = nowaLista;
    }

    public Uczeń[] getListęPrzyjętych() {
        return listaPrzyjętych;
    }

    //metody
    public boolean czyMiejsce() {
        return liczbaPrzyjętych < maksymalnaLiczba;
    }

    public void zajmijMiejsce() {
        liczbaPrzyjętych++;
    }
}
