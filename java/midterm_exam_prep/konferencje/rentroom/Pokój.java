package rentroom;
import narzędzia.*;
import wyjątki.NiezmiennikException;

public class Pokój {
    
    //dane
    private DynTablica<Interval> zajeteTerminy;
    public final Features features;
    public final int mxIloscOsob;

    //techniczne
    public Pokój(Features f, int mxIloscOsob) throws NullPointerException, NiezmiennikException{
        if(mxIloscOsob < 0) throw new NiezmiennikException("Ujemna ilość osób??");
        this.features = new Features(f.rzutnik, f.interaktywne, f.niepełnosprawni);
        this.mxIloscOsob = mxIloscOsob;
    }

    //metody
    public boolean spełniaWymagania(Features f, int rqstedIlosc, Interval Termin) {
        if(rqstedIlosc > mxIloscOsob) return false;
        if(!features.satisfies(f)) return false;
        
        return true;
    }

    public void zwolnij(Rezerwacja rezerwacja) {
        //TODO implement
    }
}
