package wyjątki;

public class NiezgodnyWymiar extends ZłeArgumentyFunkcji {

    //techniczne
    public NiezgodnyWymiar(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Podano niezgodny wymiar w: " + getMessage();
    }
}
