package sądy;

public class SądWysoki extends Sąd {
    public SądWysoki(String nazwa, Sąd wyższy, ListaSądów lista) {
        super(nazwa, wyższy, lista, false);
    }
}
