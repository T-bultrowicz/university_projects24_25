package giełda;

public abstract class Gracz {
    
    // dane
    private String nrID;
    protected Giełda giełda;
    private boolean ważny;

    // techniczne
    public Gracz() {
        ważny = false;
    }

    public Gracz(Giełda giełda) {
        giełda.zapisz(this);
        this.nrID = giełda.dajID();
        this.giełda = giełda;
        this.ważny = true;
    }

    @Override
    public String toString() {
        return "Gracz " + (ważny ? " o ID " + nrID : " nieaktywny");
    }

    @Override
    public int hashCode() {
        return nrID.hashCode();
    }

    // getters
    public String nrID() {
        return nrID;
    }

    // metody
    public void zarejestruj(Giełda giełda) {
        giełda.zapisz(this);
        this.nrID = giełda.dajID();
        this.giełda = giełda;
        this.ważny = true;
    }

    protected abstract void wrapFazaSprzedaży();
    protected abstract void wrapFazaZakupu();

    public void fazaZakupu() {
        if(!ważny) return;
        wrapFazaZakupu();
    }

    public void fazaSprzedaży() {
        if(!ważny) return;
        wrapFazaSprzedaży();
    }

}
