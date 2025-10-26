package sądy;

public class Werdykt {
    
    //dane
    private final Stan stan;
    private final long kwotaZapłata;
    private final Osoba ofensywa;
    private final Osoba defensywa;

    // techniczne
    public Werdykt(Stan stan, long kwotaZapłata, Osoba ofensywa, 
                                        Osoba defensywa) {
        Weryfikuj.nullVal("Werdykt.konstruktor()", stan, ofensywa, defensywa);
        this.stan = stan;
        this.kwotaZapłata = kwotaZapłata;
        this.ofensywa = ofensywa;
        this.defensywa = defensywa;
    }

    // getters
    public boolean pozytywny() {
        return stan == Stan.WINA;
    }

    // metody
    public void wprowadźMoc() {
        if(stan == Stan.UNIEWINNIONY) {
            ofensywa.przyjmijKarę(kwotaZapłata);
            defensywa.przyjmijOdszkodowanie(kwotaZapłata);
        } else if(stan == Stan.WINA) {
            ofensywa.przyjmijOdszkodowanie(kwotaZapłata);
            defensywa.przyjmijKarę(kwotaZapłata);
        }
    }
}
