package wyjątki;

public abstract class ZłeArgumentyFunkcji extends Exception {
    
    //techniczne
    public ZłeArgumentyFunkcji(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Podano złe argumenty w: " + getMessage();
    }
}
