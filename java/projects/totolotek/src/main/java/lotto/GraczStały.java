package lotto;
import java.util.ArrayList;
import java.util.Collection;

import wyjątki.*;

public abstract class GraczStały extends Gracz {
    
    // dane
    protected ArrayList<Kolektura> ulubione;
    protected final int coIleLosowań;
    protected int ostatniZakup;

    // techniczne
    public GraczStały(String imię, String nazwisko, String PESEL, 
            long stanKonta, CentralaTotolotka centrala,
            Collection<Kolektura> ulubione, int coIleLosowań) {
        super(imię, nazwisko, PESEL, stanKonta, centrala);
        if(ulubione == null) throw new NullWartość("GraczStały.konstruktor()");
        if(coIleLosowań <= 0) 
                    throw new UjemnaWartość("GraczStały.konstruktor()");
        this.ulubione = new ArrayList<>(ulubione);
        this.coIleLosowań = coIleLosowań;
        this.ostatniZakup = 0;
    }

    // Zdegenerowany konstruktor, losuje ulubione oraz coIleLosowań.
    // Domyślnie max 5 kolektur ze zbioru wszystkich kolektur centrali, 
    // oraz coIleLosowań z przedziału 1-15.
    public GraczStały(String imię, String nazwisko, String PESEL, 
            long stanKonta, CentralaTotolotka centrala) {
        super(imię, nazwisko, PESEL, stanKonta, centrala);
        this.ostatniZakup = 0;
        this.coIleLosowań = MaszynaLosująca.przedział(1, 15);
        this.ulubione = new ArrayList<>();
        int ile = MaszynaLosująca.przedział(1, 5);
        if(ile > centrala.ilośćKolektur()) {
            for(int i = 0; i < centrala.ilośćKolektur(); i++) {
                ulubione.add(centrala.znajdźKolekturę(i + 1));
            }
        } else {
            int[] temp = MaszynaLosująca.losujLiczby(ile, 1, 
                                                centrala.ilośćKolektur());
            for(int i = 0; i < ile; i++) {
                ulubione.add(centrala.znajdźKolekturę(temp[i]));
            }
        }
    }    

    // metody
    protected abstract Blankiet twórzBlankiet();

    @Override
    public void odbierzNagrodę(String id) {
        Kupon kupon = kupony.get(id);
        if(kupon == null) {
            throw new NieMaKuponu("GraczStały.odbierzNagrodę()");
        }
        odbierzNagrodę(id, centrala.znajdźKolekturę(kupon.nrKolektury()));
    }

    @Override
    public void zakupLosowania() {
        HistoriaLosowań hist = centrala.historia();
        if(ostatniZakup != 0 && hist.nrAktLosowania() - 
                                    ostatniZakup < coIleLosowań) {
            System.out.println("Gracz " + imię() + " " + nazwisko() + 
                                " nie kupuje teraz kuponu!\n");
            return;
        }
        Kolektura zakup = ulubione.get(MaszynaLosująca.przedział
                                            (0, ulubione.size() - 1));
        try {
            Kupon k = zakup.zakupKupon(twórzBlankiet(), this);
            kupony.put(k.id(), k);
        } catch (BrakFunduszy | ZłyBlankiet e) {
            System.out.println(e);
            return;
        }
        ostatniZakup = hist.nrAktLosowania();
    }

    public void dodajDoUlubionych(Kolektura k) {
        if(k == null) throw new NullWartość
            ("GraczStały.dodajDoUlubionych()");
        ulubione.add(k);
    }
}
