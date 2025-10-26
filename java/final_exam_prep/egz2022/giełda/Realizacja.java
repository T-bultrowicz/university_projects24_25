package giełda;

import java.util.ArrayList;

import wyjątki.NieWykonanoOperacji;

public class Realizacja {
    
    // dane
    private Zadanie zadanie;
    private ArrayList<Inwestycja> inwestycje;
    private long fundusz;
    private int ileDniZostało;

    // techniczne
    public Realizacja(Zadanie zadanie) {
        this.zadanie = zadanie;
        inwestycje = new ArrayList<>();
        ileDniZostało = zadanie.ileDni();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(zadanie).append("\nZostało ").append(ileDniZostało);
        sb.append("\nAktualnie trzyma").append(inwestycje.size())
                                                .append(" inwestycji");
        return sb.toString();
    }

    // getters
    public Zadanie zadanie() {
        return zadanie;
    }

    public ArrayList<Inwestycja> inwestycje() {
        return inwestycje;
    }

    public long fundusz() {
        return fundusz;
    }

    // metody
    public void dzieńMinął() {
        ileDniZostało--;
    }

    public void zmianaFundusz(long zmiana) {
        if(fundusz + zmiana < 0)
            throw new NieWykonanoOperacji("Realizacja.zabierzFundusz()");
        fundusz += zmiana;
    }

    public void dodajInwestycję(Inwestycja i) {
        inwestycje.add(i);
    }

    public boolean koniec() {
        return ileDniZostało == 0;
    }
}
