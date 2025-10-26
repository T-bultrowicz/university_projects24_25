package bigos;

public class Dowiązanie extends Element{
    
    //dane
    Plik doczepionyDo;

    //techniczne
    public Dowiązanie(Katalog zawarty, Plik doczepionyDo) throws NullPointerException {
        super(zawarty);
        if(zawarty == null || doczepionyDo == null) throw new NullPointerException();
        this.doczepionyDo = doczepionyDo;
        doczepionyDo.dodajDowiązanie(this);
    }

    @Override
    public String toString() {
        return zawarty.toString() + "/(" + doczepionyDo.nazwa + ")";
    }

    //metody

    public Plik getdoczepionyDo() {
        return doczepionyDo;
    }

    @Override
    public void usuń() {
        zawarty.usunElement(this);
    }
}
