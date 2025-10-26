package wyjątki;

public class ZłyIndeks extends ZłeArgumentyFunkcji {

    //techniczne
    public ZłyIndeks(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Podano zły indeks w: " + getMessage();
    }
}
