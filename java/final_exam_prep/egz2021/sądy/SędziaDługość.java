package sądy;

public class SędziaDługość extends Sędzia {

    public SędziaDługość(String imię, String nazwisko, Sąd miejscePracy) {
        super(imię, nazwisko, miejscePracy);
    }
    
    @Override
    public Werdykt wydajWyrok(Osoba defensywa, Osoba ofensywa) {
        String pierwsze = ofensywa.sprawozdanie();
        String drugie = defensywa.sprawozdanie();
        if(pierwsze.length() > drugie.length())
            return new Werdykt(Stan.WINA, ofensywa.ileRząda(), ofensywa, 
                                                        defensywa);
        else if(drugie.length() > pierwsze.length())
            return new Werdykt(Stan.UNIEWINNIONY, ofensywa.ileRząda(), 
                                                        ofensywa, defensywa);
        else return new Werdykt(Stan.UMORZENIE, 0, ofensywa, defensywa);
    }

}
