package lotto;

import wyjątki.UjemnaWartość;

public class BudżetPaństwa {

    //dane
    private static final long PODATEK_NAGRODY = 10; // w p. procentowych
    private static final long PODATEK_ZAKŁAD = 20;
    private long przekazaneSubwencje;
    private long pobranePodatki;

    public BudżetPaństwa() {
        this.przekazaneSubwencje = 0;
        this.pobranePodatki = 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Budżet Państwa:\n");
        sb.append("zyski z gry w lotto - ").append(Kwota.kwota(bilans()));
        return sb.toString();
    }

    public void przekażSubwencję(long kwota) {
        if(kwota < 0) {
            throw new UjemnaWartość("BudżetPaństwa.przekażSubwencję()");
        }
        przekazaneSubwencje += kwota;
    }   

    public void pobierzPodatek(long kwota) {
        if(kwota < 0) {
            throw new UjemnaWartość("BudżetPaństwa.pobierzPodatek()");
        }
        pobranePodatki += kwota;
    }

    public long podatekNagrody() {
        return PODATEK_NAGRODY;
    }

    public long podatekZakład() {
        return PODATEK_ZAKŁAD;
    }

    public long bilans() {
        return pobranePodatki - przekazaneSubwencje;
    }
}
