package wyjątki;

public class WartośćNull extends RuntimeException {
    public WartośćNull(String message) {
        super("Nieoczekiwana wartość null w " + message);
    }
}
