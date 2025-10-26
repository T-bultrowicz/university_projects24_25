package wyjątki;

public class NullWartość extends ZłeArgumentyFunkcji {
    public NullWartość(String message) {
        super("Nieoczekiwana wartość null w " + message);
    }
}
