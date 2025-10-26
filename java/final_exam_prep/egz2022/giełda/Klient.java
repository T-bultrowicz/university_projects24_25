package giełda;

import wyjątki.NieWykonanoOperacji;

public class Klient {

    // dane
    private final String PESEL;
    private long fundusz;

    //techniczne
    public Klient(String PESEL, long fundusz) {
        this.PESEL = PESEL;
        this.fundusz = fundusz;
    }

    @Override
    public String toString() {
        return "Klient " + PESEL + " majątek " + Kwota.kwota(fundusz);
    }

    // metody
    public void zmianaFundusz(long zmiana) {
        if(fundusz + zmiana < 0)
            throw new NieWykonanoOperacji("Klient.zmianaFundusz()");
        fundusz += zmiana;
    }

    public Zadanie dajZadanie(int maxSpadek, int minWzrost, 
                 Kategoria[] kategorie, int ileDni) {
        int rng = ML.przedział(1, (int) fundusz);
        zmianaFundusz(-rng);
        return new Zadanie(this, maxSpadek, minWzrost, kategorie, 
                        rng,  ileDni);
    }
}
