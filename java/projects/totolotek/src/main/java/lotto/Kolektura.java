package lotto;

import java.util.ArrayList;
import java.util.HashSet;
import wyjątki.*;

public class Kolektura implements Lotto {

    private class ZebraneTypowania {

        // dane
        private ArrayList<Typowanie>[] typowania;
        private int nrLosowania;
        private int aktIndeks;

        // techniczne
        @SuppressWarnings("unchecked")
        public ZebraneTypowania(int nrLosowania) {
            this.nrLosowania = nrLosowania;
            this.typowania = new ArrayList[ILOŚĆ_ZAKŁADÓW];
            for (int i = 0; i < ILOŚĆ_ZAKŁADÓW; i++) {
                this.typowania[i] = new ArrayList<>();
            }
            this.aktIndeks = 0;
        }

        //metody
        public void dodajTypowanie(Typowanie typowanie, int podany) {
            if (typowanie == null) throw new NullWartość
                ("Kolektura.ZebraneTypowania.dodajTypowanie()");
            if (podany < nrLosowania || podany >= nrLosowania + ILOŚĆ_ZAKŁADÓW)
                throw new SpozaZasięgu
                ("w Kolektura.ZebraneTypowania.dodajTypowanie()", podany);
            this.typowania[(podany - nrLosowania + aktIndeks) % ILOŚĆ_ZAKŁADÓW]
                                                            .add(typowanie);
        }

        public int[] przeprowadźLosowanie(Losowanie losowanie) {
            int[] wyniki = new int[ILOŚĆ_NAGRÓD + 1];
            int trafienia;
            for (int i = 0; i < typowania[aktIndeks].size(); i++) {
                trafienia = Weryfikacje.policzTrafienia(typowania[aktIndeks].get(i), losowanie);
                for(int j = 0; j < ILOŚĆ_NAGRÓD; j++) {
                    if (trafienia == ILOŚĆ_TRAFIEŃ[j]) {
                        wyniki[j]++;
                        break;
                    }
                }
            }
            // resetujemy typowania i przesuwamy na kolejne losowanie
            nrLosowania++;
            wyniki[ILOŚĆ_NAGRÓD] = typowania[aktIndeks].size();
            typowania[aktIndeks].clear();
            aktIndeks = (aktIndeks + 1) % ILOŚĆ_ZAKŁADÓW;
            return wyniki;
        }
    }

    // dane
    private static int NR_GENERATOR = 1;
    private int nrKolektury;
    private CentralaTotolotka centrala;
    private HashSet<Kupon> kupony;
    private ZebraneTypowania zebrane;

    // techniczne
    public Kolektura(CentralaTotolotka centrala) {
        if (centrala == null) {
            throw new NullWartość("Kolektura.konstruktor()");
            
        }
        this.nrKolektury = NR_GENERATOR++;
        this.centrala = centrala;
        this.kupony = new HashSet<>();
        this.zebrane = new ZebraneTypowania
                (centrala.historia().nrAktLosowania());
        centrala.dodajKolekturę(this);
    }

    @Override
    public String toString() {
        return "Kolektura nr " + nrKolektury + "\n";
    }

    // metody wewnętrzne
    private void formalnościKupon(Gracz gracz, Kupon kupon) 
                                                    throws BrakFunduszy {
        gracz.przekażFundusze(kupon.cena());
        kupony.add(kupon);
        for(Typowanie typowanie : kupon.zakłady()) {
            for(int i = 0; i < kupon.ileLosowań(); i++) {
                zebrane.dodajTypowanie(typowanie, kupon.nrLosowania() + i);
            }
        }
    }

    // metody
    public int[] noweLosowanie(Losowanie losowanie) {
        if(nrKolektury == 1) {
            nrKolektury = 1;
        }
        if (losowanie == null) {
            throw new NullWartość("Kolektura.noweLosowanie()");
        }
        return zebrane.przeprowadźLosowanie(losowanie);
    }

    // zakup Kuponu przez Blankiet
    public Kupon zakupKupon(Blankiet blankiet, Gracz gracz) 
                                            throws BrakFunduszy, ZłyBlankiet {
        if (blankiet == null || gracz == null) {
            throw new NullWartość("Kolektura.zakupKupon()");
        }
        Kupon kupon;
        int aktnr = centrala.historia().nrAktLosowania();
        kupon = Weryfikacje.przekształćBlankiet(blankiet, this, aktnr);
        formalnościKupon(gracz, kupon);
        return kupon;
    }

    // zakup Kuponu przez chybił-trafił
    public Kupon zakupKupon(int ileLosowań, int ileTypowań, Gracz gracz)
                                                         throws BrakFunduszy {
        if (gracz == null) {
            throw new NullWartość("Kolektura.zakupKupon()");
        }
        if(ileLosowań <= 0 || ileLosowań > ILOŚĆ_ZAKŁADÓW) {
            throw new SpozaZasięgu(ileLosowań, ILOŚĆ_ZAKŁADÓW, 
                    "Kolektura.zakupKupon()");
        }
        if(ileTypowań <= 0 || ileTypowań > ILOŚĆ_TYPÓW) {
            throw new SpozaZasięgu(ileTypowań, ILOŚĆ_TYPÓW, 
                    "Kolektura.zakupKupon()");
        }
        Kupon kupon = new Kupon(nrKolektury, 
            centrala.historia().nrAktLosowania(), ileLosowań, ileTypowań);
        formalnościKupon(gracz, kupon);
        return kupon;
    }

    public void odbierzNagrodę(Kupon kupon, Gracz gracz) throws BrakKuponuBaza {
        if (kupon == null || gracz == null) {
            throw new NullWartość("Kolektura.odbierzNagrodę()");
        }
        if(!kupony.contains(kupon)) {
            throw new BrakKuponuBaza(nrKolektury, kupon.id());
        }
        if(!kupon.ważny()) {
            System.out.println("Kupon jest nieważny!\n");
            return;
        }
        HistoriaLosowań hist = centrala.historia();
        Typowanie[] zakłady = kupon.zakłady();
        ArrayList<Long> nagrody = new ArrayList<>();
        Losowanie sprawdzane;
        for(int i = 0; i < kupon.ileLosowań(); i++) {
            if(kupon.nrLosowania() + i >= hist.nrAktLosowania()) {
                break;
            }
            sprawdzane = hist.pobierzLosowanie(kupon.nrLosowania() + i - 1);
            for(int j = 0; j < zakłady.length; j++) {
                int trafienia = Weryfikacje.policzTrafienia
                                                (zakłady[j], sprawdzane);
                for(int k = 0; k < ILOŚĆ_NAGRÓD; k++) {
                    if (trafienia == ILOŚĆ_TRAFIEŃ[k]) {
                        nagrody.add(sprawdzane.wartNagród()[k]);
                        break;
                    }
                }   
            }        
        }
        kupony.remove(kupon);
        kupon.unieważnij();
        gracz.pobierzFundusze(centrala.opodatkujWygraną(nagrody));
    }

    public int nrKolektury() {
        return nrKolektury;
    }

    // usuwa wszystkie kupony których ostatnie losowanie jest starsze niż
    // aktualne losowanie minus przedawnienie
    public void czyszczenie() {
        for(Kupon kupon : kupony) {
            if(kupon.nrLosowania() + kupon.ileLosowań() + PRZEDAWNIENIE <
                    centrala.historia().nrAktLosowania()) {
                kupony.remove(kupon);
            }
        }
    }
}
