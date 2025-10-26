package wyjątki;

public class NiestniejąceLosowanie extends ZłeArgumentyFunkcji {

    public NiestniejąceLosowanie(int nrLosowania, String message) {
        super(message + "\nLosowanie o numerze " + nrLosowania + 
                    " nie istnieje, lub już się odbyło.");
    }

    public NiestniejąceLosowanie(String message) {
        super(message);
    }
}