package przydzial;

public class PodanieGenerator {
    
    //dane
    public final Uczeń uczeń;
    public final Szkoła szkoła;
    public final Klasa klasa;
    public final int wynik;

    //techniczne
    public PodanieGenerator(Uczeń uczeń, Szkoła szkoła, Klasa klasa, int wynik) {
        this.uczeń = uczeń;
        this.szkoła = szkoła;
        this.klasa = klasa;
        this.wynik = wynik;
    }
}
