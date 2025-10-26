package sądy;
import wyjątki.Immunitet;

public abstract class OsobaImmunitet extends Osoba {

    protected OsobaImmunitet(String imię, String nazwisko) {
        super(imię, nazwisko, true);
    }

    @Override
    public void inicjujSpór(Osoba oskarżana) {
        throw new Immunitet(this);
    }

    @Override
    public String sprawozdanie() { return null;}

    @Override
    public long ileRząda() {return 0;}

    @Override
    public void przyjmijKarę(long kwota) {}

    @Override
    public void przyjmijOdszkodowanie(long Wartość) {}
}
