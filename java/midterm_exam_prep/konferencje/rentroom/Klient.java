package rentroom;
import narzędzia.*;
import wyjątki.*;

public class Klient {
    
    //dane
    public final String imię;
    public final String nazwisko;
    private DynTablica<Rezerwacja> rezerwacje;

    //techniczne
    public Klient(String imię, String nazwisko) throws NullPointerException, NiezmiennikException {
        if(imię == "" || nazwisko == "") 
            throw new NiezmiennikException("Imię/nazwisko nie może być puste");
        this.imię = imię;
        this.nazwisko = nazwisko;
        this.rezerwacje = new DynTablica<Rezerwacja>();
    }

    //metody
    public void wypiszRezerwacje() {
        rezerwacje.wyczytajElementy();
    }

    public void złóżRezerwację(Rezerwacja rezerwacja) throws NullPointerException{
        rezerwacje.dodajElement(rezerwacja);
        Centrala.złóżRezerwację(rezerwacja);
    }

    public void poprośZłóżRezerwacja() throws BrakPokojuException {
        Rezerwacja a = Centrala.poprośRezerwacja();
        rezerwacje.dodajElement(a);
        Centrala.złóżRezerwację(a);
    }
}
