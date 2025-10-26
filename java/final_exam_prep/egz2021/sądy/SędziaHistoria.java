package sądy;

public class SędziaHistoria extends Sędzia {

    public SędziaHistoria(String imię, String nazwisko, Sąd miejscePracy) {
        super(imię, nazwisko, miejscePracy);
    }
    
    @Override
    public Werdykt wydajWyrok(Osoba defensywa, Osoba ofensywa) {
        if(defensywa.suma)
    }
    
}
