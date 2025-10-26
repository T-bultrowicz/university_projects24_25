package lotto;
import java.util.ArrayList;

import wyjątki.NullWartość;
import wyjątki.SpozaZasięgu;

public class CentralaTotolotka implements Lotto {

    // dane
    private static final long MILION = 100000000L;
    private ArrayList<Kolektura> spisKolektur;
    private HistoriaLosowań historia;
    private BudżetPaństwa państwo;
    private long fundusz;
    private long kumulacja;
    private long pobraneSubwencje;

    // techniczne
    public CentralaTotolotka(BudżetPaństwa państwo) {
        if(państwo == null) {
            throw new IllegalArgumentException("Państwo nie może być null");
        }
        this.państwo = państwo;
        this.spisKolektur = new ArrayList<>();
        this.historia = new HistoriaLosowań();
        this.fundusz = 0;
        this.kumulacja = 0;
        this.pobraneSubwencje = 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Centrala Totolotka\n");
        sb.append("Ilość kolektur: ").append(spisKolektur.size()).append("\n");
        sb.append("Środki finansowe: ").append(Kwota.kwota(fundusz)).append("\n");
        return sb.toString();
    }

    // metody wewnętrzne

    // jeśli nie wystarcza środków pobieramy subwencję od państwa, na tyle dużą,
    // aby mieć dalej 10e6 zł w funduszu (10e8 groszy) 
    private void rozlicz(long kwota) {
        if(fundusz < kwota) {
            państwo.przekażSubwencję(kwota - fundusz + MILION);
            pobraneSubwencje += kwota - fundusz + MILION;
            fundusz = MILION;
        } else {
            fundusz -= kwota;
        }
    }

    // wyliczam pule nagród na podstawie kwoty, zmiany nie psują logiki gry,
    // jeśli uaktualniamy odpowiednio ILOŚĆ_NAGRÓD, ILOŚĆ_TRAFIEŃ w Lotto
    public long[] wyliczPula(long kwota, long[] ilZwycięzców) {
        // Aby jeśli nikt nie wygra, wyświetlić hipotetyczną kwotę poj wygranej
        kwota = kwota * 49 / 100;
        long[] pula = new long[ILOŚĆ_NAGRÓD];
        long[] kopiaBezZer = ilZwycięzców.clone();
        for(int i = 0; i < ILOŚĆ_NAGRÓD; i++) {
            kopiaBezZer[i] = Math.max(1, kopiaBezZer[i]);
        }
        long naGłówne = kwota * 11 / 25;
        long naDrugie = kwota * 2 / 25;
        pula[0] = NAJM_NAGRODA;
        pula[3] = Math.max(MILION * 2 + kumulacja, + (naGłówne + kumulacja / 
                                                kopiaBezZer[3]));
        pula[2] = naDrugie / kopiaBezZer[2];
        pula[1] = kwota - naGłówne - naDrugie - (pula[0] * ilZwycięzców[0]);
        pula[1] /= kopiaBezZer[1];
        pula[1] = Math.max(pula[1], 3600);
        if(ilZwycięzców[3] == 0) {
            kumulacja += naGłówne;
        }
        else kumulacja = 0;
        return pula;
    }

    // metody

    public long opodatkujWygraną(ArrayList<Long> al) {
        long trafiDoZwycięzcy = 0, trafiDoPaństwa = 0, podatek = 0;
        for(Long kwota : al) {
            if(kwota >= 228000) {
                podatek = kwota * państwo.podatekNagrody() / 100;
                trafiDoZwycięzcy += kwota - podatek;
                trafiDoPaństwa += podatek;
            } else {
                trafiDoZwycięzcy += kwota;
            }
        }
        państwo.pobierzPodatek(trafiDoPaństwa);
        rozlicz(trafiDoZwycięzcy);
        return trafiDoZwycięzcy;
    }

    public long[] wyliczZwycięzców(Losowanie los) {
        long[] res = new long[ILOŚĆ_NAGRÓD];
        for(Kolektura a : spisKolektur) {
            int[] temp = a.noweLosowanie(los);
            for(int i = 0; i < ILOŚĆ_NAGRÓD; i++) {
                res[i] += temp[i];
            }
        }
        return res;
    }

    public void noweLosowanie() {
        Losowanie los = new Losowanie();
        historia.dodajLosowanie(los);
        long[] ilZwycięzców = new long[ILOŚĆ_NAGRÓD];
        long noweFundusze = 0;

        // zbieramy dane od kolektur o zwycięzcach i funduszach
        for(Kolektura a : spisKolektur) {
            int[] temp = a.noweLosowanie(los);
            noweFundusze += temp[ILOŚĆ_NAGRÓD] * CENA_ZAKŁADU;
            for(int i = 0; i < ILOŚĆ_NAGRÓD; i++) {
                ilZwycięzców[i] += temp[i];
            }
        }

        // wyliczamy finanse i uaktualniamy informacje o losowaniu
        long podatek = noweFundusze * państwo.podatekZakład() / 100;
        państwo.pobierzPodatek(podatek);
        noweFundusze -= podatek;
        los.przeprowadź(wyliczPula(noweFundusze, ilZwycięzców), 
                                                ilZwycięzców);
        fundusz += noweFundusze;
    }

    public HistoriaLosowań historia() {
        return historia;
    }

    public Kolektura znajdźKolekturę(int nrKolektury) {
        if(nrKolektury < 1 || nrKolektury > spisKolektur.size()) {
            throw new SpozaZasięgu(nrKolektury, spisKolektur.size(), 
                    " CentralaTotolotka.znajdźKolekturę()");
        }
        return spisKolektur.get(nrKolektury - 1);
    }

    public int ilośćKolektur() {
        return spisKolektur.size();
    }

    public String oLosowaniu(int idLosowania) {
        if(idLosowania < 1 || idLosowania >= historia.nrAktLosowania()) {
            throw new SpozaZasięgu(idLosowania, historia.nrAktLosowania() - 1, 
                    " CentralaTotolotka.oLosowaniu()");
        }
        return historia.oLosowaniu(idLosowania);
    }

    public void przedawnienieKuponów() {
        for(Kolektura kolektura : spisKolektur) {
            kolektura.czyszczenie();
        }
    }

    public long fundusz() {
        return fundusz;
    }

    public long pobraneSubwencje() {
        return pobraneSubwencje;
    }

    public void dodajKolekturę(Kolektura kolektura) {
        if(kolektura == null)
            throw new NullWartość("CentralaTotolotka.dodajKolekturę()");
        spisKolektur.add(kolektura);
    }
}
