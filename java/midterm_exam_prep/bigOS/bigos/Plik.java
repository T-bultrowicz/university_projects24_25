package bigos;

import DynamicznaTablica.DynamicznaTablica;
import wyjątki.NiepoprawneDaneException;

public class Plik extends Element {
    
    //dane
    String nazwa;
    static long przydzielMiejsceDysk = 0;
    long miejsceNaDysku;
    boolean czyOdczyt, czyModyfikacja;
    DynamicznaTablica<Dowiązanie> dowiązywany;


    //w przyszłości może być bardziej rozbudowane
    private long przydzielMiejsceDysk() {
        return przydzielMiejsceDysk++;
    }

    //techniczne
    public Plik(Katalog zawarty, String nazwa, boolean czyOdczyt, boolean czyModyfikacja) throws NullPointerException, NiepoprawneDaneException {
        super(zawarty);
        if(zawarty == null) throw new NullPointerException();
        zmieńNazwę(nazwa);
        if(czyModyfikacja == true && czyOdczyt == false)
            throw new NiepoprawneDaneException("Nie może istnieć plik modyfikowalny, nieodczytywalny");
        miejsceNaDysku = przydzielMiejsceDysk();
        this.czyModyfikacja = czyModyfikacja;
        this.czyOdczyt = czyOdczyt;
        this.nazwa = nazwa;
        this.dowiązywany = new DynamicznaTablica<Dowiązanie>();
    }

    public Plik(Katalog zawarty, String nazwa) throws NullPointerException, NiepoprawneDaneException {
        super(zawarty);
        if(nazwa == null) throw new NullPointerException();
        if(nazwa == "") throw new NiepoprawneDaneException("Nazwa pliku nie może być pusta");
        miejsceNaDysku = przydzielMiejsceDysk();
        this.czyModyfikacja = false;
        this.czyOdczyt = true;
        this.nazwa = nazwa;
        this.dowiązywany = new DynamicznaTablica<Dowiązanie>();
    }

    @Override
    public String toString() {
        return zawarty.toString() + "/" + nazwa; 
    }


    //metody
    @Override
    public void usuń() {
        for(int i = 0; i < dowiązywany.uzywaneMiejsce(); i++) {
            dowiązywany.get(i).usuń();
        }
        zawarty.usunElement(this);
    }

    public void zmieńNazwę(String nazwa) throws NullPointerException, NiepoprawneDaneException {
        if(nazwa == null) throw new NullPointerException();
        if(nazwa == "") throw new NiepoprawneDaneException("Nazwa pliku nie może być pusta"); 
        this.nazwa = nazwa;
    }

    public void dodajDowiązanie(Dowiązanie doDodania) throws NullPointerException {
        if(doDodania == null) throw new NullPointerException();
        dowiązywany.add(doDodania);
    }

}
