package lotto;

import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayList;
import wyjątki.*;

public abstract class Gracz implements Lotto {
    
    // dane
    private final String imię, nazwisko, PESEL;
    private long stanKonta;
    protected HashMap<String, Kupon> kupony;
    protected CentralaTotolotka centrala;

    // techniczne
    public Gracz(String imię, String nazwisko, String PESEL,
                long stanKonta, CentralaTotolotka centrala) {
        if (imię == null || nazwisko == null || PESEL == null 
                                                || centrala == null) {
            throw new NullWartość("Gracz.konstruktor()");
        }
        if (stanKonta < 0) throw new UjemnaWartość("Gracz.konstruktor()");
        this.imię = imię;
        this.nazwisko = nazwisko;
        this.PESEL = PESEL;
        this.stanKonta = stanKonta;
        this.kupony = new HashMap<>();
        this.centrala = centrala;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(imię).append(" ").append(nazwisko).append("\n");
        sb.append("PESEL: ").append(PESEL).append("\n");
        sb.append("Stan konta: ").append(Kwota.kwota(stanKonta)).append("\n");
        sb.append("Ilość kuponów: ").append(kupony.size()).append("\n");
        for(String k : kupony.keySet())
            sb.append(k).append("\n");
        return sb.toString();
    }

    // metody

    public void pobierzFundusze(long kwota) {
        if (kwota < 0) {
            throw new UjemnaWartość("Gracz.pobierzFundusze()");
        }
        this.stanKonta += kwota;
    }

    public void przekażFundusze(long kwota) throws BrakFunduszy {
        if (kwota <= 0) {
            throw new UjemnaWartość("Gracz.przekażFundusze()");
        }
        if (kwota > stanKonta) {
            throw new BrakFunduszy(kwota - stanKonta, "\n" + 
                                    this.imię + " " + this.nazwisko);
        }
        this.stanKonta -= kwota;
    }

    public abstract void zakupLosowania();
    public abstract void odbierzNagrodę(String id);
    public void odbierzNagrodę(String id, Kolektura kolektura) throws BrakKuponuBaza {
        if(id == null) throw new NullWartość("Gracz.odbierzNagrodę()");
        Kupon k = kupony.get(id);
        if(k == null) {
            throw new NieMaKuponu("Gracz.odbierzNagrodę()");
        }
        kolektura.odbierzNagrodę(k, this);
        kupony.remove(id);
    }

    public void sprawdźKupon(String id) {
        Kupon kupon = kupony.get(id);
        if(kupon == null) {
            throw new NieMaKuponu("Gracz.sprawdźKupon()");
        }
        HistoriaLosowań h = centrala.historia();
        //Sprawdzamy, czy kupon nie może jeszcze wygrać więcej
        if (kupon.nrLosowania() + kupon.ileLosowań() >= h.nrAktLosowania()) {
            return;
        }
        // Zakładamy, że klienci są leniwi - nie chcą chodzić do kolektury tam sprawdzić Kupon,
        // dopóki sami nie sprawdzą, że mają szansę na wygraną.
        Typowanie[] typowania = kupon.zakłady();
        for(int i = 0; i < typowania.length; i++) {
            for(int j = 0; j < kupon.ileLosowań(); j++) {
                Losowanie los = h.pobierzLosowanie(kupon.nrLosowania() + j);
                if (Weryfikacje.policzTrafienia(typowania[i], los) >= 
                                                            ILOŚĆ_TRAFIEŃ[0]) {
                    odbierzNagrodę(id);
                    return;
                }
            }
        }
        kupony.remove(id); //tak czy inaczej nic nie wygra - można usunąć
    }

    public void sprawdźKupony() {
        for(String a : new HashSet<>(kupony.keySet())) {
            sprawdźKupon(a);
        }
    }

    public void zmieńCentralę(CentralaTotolotka nowaCentrala) {
        if (nowaCentrala == null)
            throw new NullWartość("Gracz.zmieńCentralę()");
        sprawdźKupony(); // odbieramy wszystkie kupony starejCentrali
        this.centrala = nowaCentrala;
    }

    // metody dostępowe

    public String imię() {
        return this.imię;
    }

    public String nazwisko() {
        return this.nazwisko;
    }

    public String PESEL() {
        return this.PESEL;
    }

    public long stanKonta() {
        return this.stanKonta;
    }

    public Kupon kupon(String id) {
        return kupony.get(id);
    }

    public ArrayList<Kupon> kupony() {
        return new ArrayList<>(kupony.values());
    } 

    public String zapytajDetaleLosowanie(int nrLosowania) {
        return centrala.oLosowaniu(nrLosowania);
    }

    public int ilośćKuponów() {
        return kupony.size();
    }
}
