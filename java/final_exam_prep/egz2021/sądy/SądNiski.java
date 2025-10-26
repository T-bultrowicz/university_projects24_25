package sądy;

public class SądNiski extends Sąd {

    public SądNiski(String nazwa, Sąd wyższy, ListaSądów lista) {
        super(nazwa, wyższy, lista, true);
    }
}
