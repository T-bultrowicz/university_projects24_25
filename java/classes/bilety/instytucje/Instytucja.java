package instytucje;
import osoby.Osoba;

public interface Instytucja {
    boolean wydajBilety(Wydarzenie wydarzenie, Osoba osoba);
    boolean wydajBilety(Wydarzenie wydarzenie, Osoba[] osoby);
    int ileWolnych(Wydarzenie wydarzenie);
    int ileWolnych(Wydarzenie[] wydarzenia);
}
