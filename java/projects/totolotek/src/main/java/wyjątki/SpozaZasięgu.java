package wyjątki;

public class SpozaZasięgu extends ZłeArgumentyFunkcji {
    
    public SpozaZasięgu(String message, int val) {
        super("Wartość " + val + " spoza zakresu w " + message);
    }

    public SpozaZasięgu(int val, int val2, String message) {
        super("Wartość " + val + " spoza zasięgu: do " + val2
                    + "....    w " + message);
    }
}
