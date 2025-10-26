package rentroom;

public class Miasto {
    
    //dane
    public final Budynek[] budynki;

    //techniczne
    public Miasto(Budynek[] budynki) throws NullPointerException{
        for(Budynek a : budynki)
            if(a == null) throw new NullPointerException();
        this.budynki = budynki;
    }
}
