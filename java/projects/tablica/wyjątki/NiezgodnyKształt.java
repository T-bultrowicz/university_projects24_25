package wyjątki;

public class NiezgodnyKształt extends ZłeArgumentyFunkcji {

    //techniczne
    public NiezgodnyKształt(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Złe kształty w: " + getMessage();
    }
}
