package bigos;

import DynamicznaTablica.DynamicznaTablica;
import wyjątki.NiepoprawneDaneException;

public class Katalog extends Element {

    //dane
    String nazwa;
    DynamicznaTablica<Element> zawartosc;

    //techniczne
    public Katalog(Katalog zawarty, String nazwa) throws NiepoprawneDaneException, NullPointerException{
        super(zawarty);
        if(nazwa == null) throw new NullPointerException();
        if(nazwa == "" && zawarty != null) throw new NiepoprawneDaneException("Katalog musi mieć nazwę!");
        if(nazwa != "" && zawarty == null) throw new NiepoprawneDaneException("Katalog główny nie ma nazwy!");
        this.nazwa = nazwa;
        this.zawartosc = new DynamicznaTablica<Element>();
    }

    public void usunElement(Element doUsuniecia) {
        zawartosc.delete(doUsuniecia);
    }

    public void dodajElement(Element doDodania) throws NullPointerException {
        zawartosc.add(doDodania);
    }

    @Override
    public String toString() {
        if(zawarty == null) return "";
        return zawarty.toString() + "/" + this.nazwa;
    }

    //metody
    @Override
    public void usuń() {
        if(zawartosc.uzywaneMiejsce() == 0);
        if(zawarty == null) return;
        zawarty.usunElement(this);
    }

    public String wypiszElementy() {
        String res = "Katalog" + this.toString() + " zawiera elementy:\n";
        for(int i = 0; i < zawartosc.uzywaneMiejsce(); i++) {
            res += zawartosc.get(i).toString() + "\n";
            if(zawartosc.get(i) instanceof Katalog) {
                res += ((Katalog) zawartosc.get(i)).wypiszElementy(1) + "\n";
            }
        }
        return res;
    }

    public String wypiszElementy(int wcięcie) {
        String res = "";
        for(int i = 0; i < zawartosc.uzywaneMiejsce(); i++) {
            for(int j = 0; j < wcięcie; j++) {
                res += "  ";
            }
            res += zawartosc.get(i).toString() + "\n";
            if(zawartosc.get(i) instanceof Katalog) {
                res += ((Katalog) zawartosc.get(i)).wypiszElementy(wcięcie + 1) + "\n";
            }
        }
        return res;
    }

}
