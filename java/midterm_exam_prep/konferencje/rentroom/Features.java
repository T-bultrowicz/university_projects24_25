package rentroom;

public class Features {
    
    //dane
    public final boolean rzutnik;
    public final boolean interaktywne;
    public final boolean niepełnosprawni;

    //techniczne
    public Features(boolean rzutnik, boolean interaktywne, boolean niepełnosprawni) {
        this.rzutnik = rzutnik;
        this.interaktywne = interaktywne;
        this.niepełnosprawni = niepełnosprawni;
    }

    //metody
    public boolean satisfies(Features requests) {
        if(requests.rzutnik && !this.rzutnik) return false;
        if(requests.interaktywne && !this.interaktywne) return false;
        if(requests.niepełnosprawni && !this.niepełnosprawni) return false;
        return true;
    }
}
