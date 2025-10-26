package bankBajtocji;

public class InniPosiadacze extends OperacjaTworząca {
    public InniPosiadacze(Konto a, Konto b) {
        super("Konta " + a + " i " + b + " mają innych posiadaczy!");
    }
}
