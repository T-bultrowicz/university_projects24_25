package giełda;

import java.util.ArrayList;

public abstract class Broker extends Gracz {
     
    // dane
    protected ArrayList<Program> programy;
    protected Strategia strategia;
    protected ArrayList<Realizacja> realizacje;
    protected int pobór; // w p.proc.
    private long zysk;

    // techniczne
    public Broker(int pobór, Strategia strategia) {
        this.pobór = pobór;
        this.zysk = 0;
        this.realizacje = new ArrayList<>();
        this.strategia = strategia;
        this.programy = new ArrayList<>();
    }

    public Broker(Giełda giełda, int pobór, Strategia strategia) {
        super(giełda);
        this.pobór = pobór;
        this.zysk = 0;
        this.realizacje = new ArrayList<>();
        this.strategia = strategia;
        this.programy = new ArrayList<>();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
        sb.append(" Broker o zysku ").append(Kwota.kwota(zysk));
        sb.append(" pobiera ").append(pobór).append("% za usługi");
        for(Realizacja a : realizacje)
            sb.append(a);
        return sb.toString();
    }

    // metody
    abstract protected boolean filter(Zasób z, Realizacja r);
    abstract protected void obsługaSprzedażyKlienta(Realizacja r);
    abstract protected void zakończenie(Realizacja r);

    public void dodajBezpiecznieProgram(Program p) {
        programy.add(p);
    }

    public void dodajProgram(Program p) {
        strategia.dodaj(this, p);
    }

    public void przyjmijZadanie(Zadanie z) {
        realizacje.add(new Realizacja(z));
    }

    protected void sprzedajInwestycję(Inwestycja i, Realizacja r) {
        r.inwestycje().remove(i);
        long zyss = giełda.cena(i.zasób()) * i.ilośćKupionych();
        long zyskBrokera = zyss * pobór / 100;
        zysk += zyskBrokera;
        r.zmianaFundusz(zyss - zyskBrokera);
    }

    protected void obsługaZakupuKlienta(Realizacja r) {
        for(Zasób z : giełda.zasoby()) {
            if(filter(z, r)) {
                int t = strategia.ileKupić(z, giełda, programy);
                if(t > 0) {
                    Inwestycja i = new Inwestycja(z, giełda.cena(z), t);
                    giełda.zrealizuj(i);
                    r.zmianaFundusz(-giełda.cena(z) * t);
                    r.dodajInwestycję(i);
                }
            }
        }
    }


    @Override
    protected void wrapFazaZakupu() {
        for(Realizacja r : realizacje) {
            obsługaZakupuKlienta(r);
        }
    }

    @Override
    protected void wrapFazaSprzedaży() {
        for(Realizacja r : realizacje.toArray(new Realizacja[1])) {
            obsługaSprzedażyKlienta(r);
            r.dzieńMinął();
            if(r.koniec()) zakończenie(r);
        }
    }
}
