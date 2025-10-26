package lotto;

import java.util.ArrayList;

import wyjątki.NullWartość;
import wyjątki.SpozaZasięgu;

public class HistoriaLosowań implements Lotto {
    
    // dane
    private ArrayList<Losowanie> losowania;

    //techniczne
    public HistoriaLosowań() {
        this.losowania = new ArrayList<>();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Historia losowań - przechowuje ");
        sb.append(losowania.size() + " losowań:\n");
        return sb.toString();
    }

    // metody
    public void dodajLosowanie(Losowanie losowanie) {
        if (losowanie == null) {
            throw new NullWartość("HistoriaLosowań.dodajLosowanie()");
        }
        losowania.add(losowanie);
    }

    public Losowanie pobierzLosowanie(int indeks) {
        if (indeks < 0 || indeks >= losowania.size()) {
            throw new SpozaZasięgu(indeks, losowania.size() - 1, 
                    "HistoriaLosowań.pobierzLosowanie()");
        }
        return losowania.get(indeks);
    }

    // Zwraca numer porządkowy ostatniego losowania.
    public int nrAktLosowania() {
        return losowania.size() + 1;
    }

    // Zwraca szczegóły losowania o podanym indeksie.
    public String oLosowaniu(int indeks) {
        if (indeks < 1 || indeks > losowania.size()) {
            throw new SpozaZasięgu(indeks, losowania.size(), 
                    "HistoriaLosowań.oLosowaniu()");
        }
        StringBuilder sb = new StringBuilder();
        Losowanie losowanie = losowania.get(indeks - 1);
        long[] wartNagród = losowanie.wartNagród();
        long[] ilZwycięzców = losowanie.ilZwycięzców();
        sb.append(losowanie.toString());
        sb.append("\n---  Kwoty wygranych stopnia:\n");
        for(int i = 0; i < ILOŚĆ_NAGRÓD; i++) {
            sb.append(ILOŚĆ_NAGRÓD - i).append(" - ");
            sb.append(Kwota.kwota(wartNagród[i])).append(" ");
        }
        sb.append("\n---  Ilość zwycięzców stopnia:\n");
        for(int i = 0; i < ILOŚĆ_NAGRÓD; i++) {
            sb.append(ILOŚĆ_NAGRÓD - i).append(" - ");
            sb.append(ilZwycięzców[i]).append(" ");
        }
        sb.append("\n---  Łączne pule nagród:\n");
        for(int i = 0; i < ILOŚĆ_NAGRÓD; i++) {
            sb.append(ILOŚĆ_NAGRÓD - i).append(" - ");
            sb.append(Kwota.kwota(ilZwycięzców[i] * wartNagród[i]));
            sb.append(" ");
        }
        return sb.toString();         
    }
}
