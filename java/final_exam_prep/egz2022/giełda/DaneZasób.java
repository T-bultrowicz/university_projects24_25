package giełda;

import wyjątki.NieWykonanoOperacji;

public class DaneZasób {
    
    // dane
    private int ileDost;
    private long cena;

    // techniczne
    public DaneZasób(int ileDost, long cena) {
        this.ileDost = ileDost;
        this.cena =  cena;
    }

    // metody
    public int ileDost() {return ileDost;}
    public long cena() {return cena;}
    public void zmieńCena(long val) {
        if(cena + val < 0)
            throw new NieWykonanoOperacji("DaneZasób.zmieńCena()");
        cena += val;
    }
    public void zmieńIleDost(int val) {
        if(ileDost + val < 0)
            throw new NieWykonanoOperacji("DaneZasób.zmieńIleDost()");
        ileDost += val;
    }
}
