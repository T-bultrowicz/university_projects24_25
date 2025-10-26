package wyjątki;

public class NieMaKuponu extends ZłeArgumentyFunkcji {
    public NieMaKuponu(String message) {
        super("Klient nie posiada tego kupony, więc nie może " + 
                "wykonać na nim działania!\n" + message);
    }
}
