package sądy;

import wyjątki.Immunitet;
import wyjątki.Najwyższa;

public abstract class OsobaZwykła extends Osoba {

    // dane
    private int ilSkazań;
    private long ileRząda;
    private long sumaRządań;
    private long bilans;
    private ListaSądów sądy;

    // techniczne
    protected OsobaZwykła(String imię, String nazwisko, ListaSądów sądy) {
        super(imię, nazwisko, false);
        Weryfikuj.nullVal("OsobaZwykła.konstruktor()", sądy);
        this.sądy = sądy;
        this.ileRząda = 500;
        this.ilSkazań = 0;
        this.sumaRządań = 0;
        this.bilans = 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(super.toString()).append("\nbilans - ");
        sb.append(Kwota.kwota(bilans));
        return sb.toString();
    }

    //getters
    public int ilSkazań() {
        return ilSkazań;
    }

    public long sumaRządań() {
        return sumaRządań;
    }

    public long bilans() {
        return bilans;
    }

    @Override
    public long ileRząda() {
        return ileRząda;
    }

    public void ustawIleRząda(long kwota) {
        Weryfikuj.belowVal("OsobaZwykła.ustawIleRząda()", kwota);
        this.ileRząda = kwota;
    }

    // metody
    @Override
    public void inicjujSpór(Osoba oskarżana) {
        if(oskarżana.immunitet()) {
            throw new Immunitet(oskarżana);
        }
        Sąd sąd = sądy.przydzielSąd();
        Werdykt werdykt = null;
        do {
            try {
                werdykt = sąd.rozpatrzSprawę(this, oskarżana);
                sąd = sąd.wyższaInstancja();
            } catch(Najwyższa e) {System.out.println(e); break;}
        } while(!werdykt.pozytywny());
        werdykt.wprowadźMoc();
        sumaRządań += ileRząda;
    }

    @Override
    public void przyjmijKarę(long kwota) {
        Weryfikuj.belowVal("OsobaZwykła.przyjmijKarę()", kwota);
        ilSkazań++;
        bilans -= kwota;
    }

    @Override
    public void przyjmijOdszkodowanie(long kwota) {
        Weryfikuj.belowVal("OsobaZwykła.przyjmijOdszkodowanie()", kwota);
        bilans += kwota;
    }
}
