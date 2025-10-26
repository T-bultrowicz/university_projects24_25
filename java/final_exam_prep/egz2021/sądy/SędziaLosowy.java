package sądy;

public class SędziaLosowy extends Sędzia {

    // dane 
    private int procentRemis;
    private int procentOfensywaWygra;


    public SędziaLosowy(String imię, String nazwisko, Sąd miejscePracy) {
        super(imię, nazwisko, miejscePracy);
        procentRemis = ML.getInt(1, 98);
        procentOfensywaWygra = ML.getInt(1, 100 - procentRemis);
    }
    
    @Override
    public Werdykt wydajWyrok(Osoba defensywa, Osoba ofensywa) {
        int los = ML.getInt(1, 100);
        if(los <= procentRemis)
            return new Werdykt(Stan.UMORZENIE, 0, ofensywa, defensywa);
        else if(los > procentRemis && los <= procentOfensywaWygra + procentRemis)
            return new Werdykt(Stan.WINA, ofensywa.ileRząda(), 
                                                    ofensywa, defensywa);
        else return new Werdykt(Stan.UNIEWINNIONY, ofensywa.ileRząda(), 
                                                    ofensywa, defensywa);
    }
    
}
