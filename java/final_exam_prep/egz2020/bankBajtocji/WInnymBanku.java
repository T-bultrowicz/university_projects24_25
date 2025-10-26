package bankBajtocji;

public class WInnymBanku extends OperacjaTworząca {
    public WInnymBanku(Konto a, Konto b) {
        super("Konta " + a + " i " + b + " zawarte są w innych bankach!");
    }
}
