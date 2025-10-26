package lotto;

public class Kupon implements Lotto {
    
    // dane 
    private static int ID_GENERATOR = 1;
    private final Typowanie[] zakłady;
    private final String id;
    private final int nrLosowania;
    private final int nrKolektury;
    private final int ileLosowań;
    private final long cena;
    private boolean ważny;

    // techniczne
    private String stwórzID() {
        StringBuilder sb = new StringBuilder();
        int liczba;
        long sumaCyfr = Weryfikacje.sumaCyfr(ID_GENERATOR)
                             + Weryfikacje.sumaCyfr(nrKolektury);
        sb.append(ID_GENERATOR++).append("-").append(nrKolektury).append("-");
        for(int i = 0; i < 9; i++) {
            liczba = MaszynaLosująca.losowaCyfra();
            sb.append(Integer.toString(liczba));
            sumaCyfr += liczba;
        }
        sumaCyfr %= 100;
        sb.append("-").append(sumaCyfr < 10 ? "0" : "").append(sumaCyfr);
        return sb.toString();
    }

    // konstruktor do wypełnienia z ustalonymi liczbami
    Kupon(int nrKolektury, int nrLosowania, int ileLosowań, 
                                                        Typowanie[] zakłady) {
        this.zakłady = zakłady;
        this.nrLosowania = nrLosowania;
        this.nrKolektury = nrKolektury;
        this.ileLosowań = ileLosowań;
        this.id = stwórzID();
        this.cena = ileLosowań * zakłady.length * CENA_ZAKŁADU;
        ważny = true;
    }

    // konstruktor do wypełnienia na chybił trafił
    Kupon(int nrKolektury, int nrLosowania, 
                int ileLosowań, int ileTypowań) {
        this.zakłady = new Typowanie[ileTypowań];
        for (int i = 0; i < ileTypowań; i++) {
            this.zakłady[i] = new Typowanie();
        }
        this.nrLosowania = nrLosowania;
        this.nrKolektury = nrKolektury;
        this.ileLosowań = ileLosowań;
        this.id = stwórzID();
        this.cena = ileLosowań * ileTypowań * CENA_ZAKŁADU;
        ważny = true;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("KUPON NR ").append(id).append("\n");
        for(int i = 0; i < zakłady.length; i++) {
            sb.append(i + 1).append(": ").append(zakłady[i]).append("\n");
        }
        sb.append("LICZBA LOSOWAŃ: ").append(ileLosowań).append("\n");
        sb.append("NUMERY LOSOWAŃ:\n");
        for(int i = 0; i < ileLosowań; i++) {
            sb.append(nrLosowania + i).append(" ");
        }
        sb.append("\nCENA: ").append(Kwota.kwota(cena));
        return sb.toString();
    }

    // hashowanie do przechowywania dużych zbiorów kuponów
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Kupon kupon = (Kupon) obj;
        return id.equals(kupon.id);
    }

    @Override
    public int hashCode() {
        return id.hashCode();
    }

    // metody
    public String id() {
        return id;
    }

    public Typowanie[] zakłady() {
        return zakłady;
    }
    
    public int nrLosowania() {
        return nrLosowania;
    }

    public int nrKolektury() {
        return nrKolektury;
    }

    public long cena() {
        return cena;
    }

    public int ileLosowań() {
        return ileLosowań;
    }

    public boolean ważny() {
        return ważny;
    }

    public void unieważnij() {
        ważny = false;
    }
}
