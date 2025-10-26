package przydzial;

import niezmiennik.NiezmiennikException;

public class Szkoła {
    
    //dane
    public final String nazwa;
    public final Klasa[] klasy;

    //techniczne
    public Szkoła(String nazwa, Klasa[] klasy) throws NullPointerException, NiezmiennikException {
        if(nazwa == null || klasy == null) throw new NullPointerException();
        for(Klasa a : klasy)
            if(a == null) throw new NullPointerException();
        
        if(nazwa == "") throw new NiezmiennikException("Pusta nazwa szkoły!");
        if(klasy.length == 0) throw new NiezmiennikException("Szkoła bez klas!");
        this.nazwa = nazwa;
        this.klasy = klasy;
    }
}
