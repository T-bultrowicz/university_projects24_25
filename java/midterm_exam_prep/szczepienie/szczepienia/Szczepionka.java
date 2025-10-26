package szczepienia;
import wyjątki.*;

public class Szczepionka {
    
    //dane
    /* EWENTUALNE ROZSZERZENIE:
     * static private STRING[] lista_szczepionek.
     * nadzoruje wszystkie stworzone i pilnuje braku duplikatów 
     */
    public final String nazwa;

    //techniczne
    public Szczepionka(String nazwa) throws NullPointerException, NiezmiennikException{
        if(nazwa == null) throw new NullPointerException();
        if(nazwa == "") throw new NiezmiennikException("Nazwa nie pusta");
        this.nazwa = nazwa;
    }
}
