package bigos;

public abstract class Element {
    //dane
    Katalog zawarty;

    //techniczne
    public Element(Katalog zawarty) {
        this.zawarty = zawarty;
        if(zawarty != null) {
            zawarty.dodajElement(this);
        }
    }
    public abstract String toString();

    //metody
    public void zmieńKatalog(Katalog nowyKatalog) throws NullPointerException {
        if(nowyKatalog == null) throw new NullPointerException("katalog jest nullem");
        this.zawarty.usunElement(this);
        nowyKatalog.dodajElement(this);
        this.zawarty = nowyKatalog;
    }

    public abstract void usuń();
}
