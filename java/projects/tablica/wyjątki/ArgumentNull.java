package wyjątki;

public class ArgumentNull extends ZłeArgumentyFunkcji {

    //techniczne
    public ArgumentNull(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Argument null w: " + getMessage();
    }
}
