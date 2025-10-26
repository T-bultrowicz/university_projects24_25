package wyjątki;

public class UjemnaWartość extends ZłeArgumentyFunkcji {
    public UjemnaWartość(String message) {
        super("Nieoczekiwana wartość ujemna w " + message);
    }

    public UjemnaWartość() {
        super("Nieoczekiwana wartość ujemna");
    }
}
