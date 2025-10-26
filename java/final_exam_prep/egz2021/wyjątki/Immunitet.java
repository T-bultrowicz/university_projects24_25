package wyjątki;
import sądy.Osoba;

public class Immunitet extends RuntimeException {
    public Immunitet(Osoba o) {
        super("Zainicjowano spór z " + o);
    }
}
