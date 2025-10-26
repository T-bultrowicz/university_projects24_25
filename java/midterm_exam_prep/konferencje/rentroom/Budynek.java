package rentroom;
import narzędzia.*;

public class Budynek {
    
    //dane
    public final Pokój[] pokoje;
    public final Adres adres;

    //techniczne
    public Budynek(Pokój[] pokoje, Adres adres) throws NullPointerException {
        for(Pokój a : pokoje)
            if(a == null) throw new NullPointerException();
        if(adres == null) throw new NullPointerException();

        this.adres = adres;
        this.pokoje = pokoje;
    }
}
