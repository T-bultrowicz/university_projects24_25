package wyjątki;

public class ZłaWartość extends RuntimeException {
    public ZłaWartość(Object o, String desk, String mes) {
        super("Zła wartość w " + mes + " oczekiwano " + desk + " a jest " + o);
    }
}
