package wyjątki;
import lotto.Blankiet;

public class ZłyBlankiet extends Exception {

    Blankiet blankiet;

    public ZłyBlankiet(String message, Blankiet blankiet) {
        super("Źle wypełniony blankiet : " + message);
        this.blankiet = blankiet;
    }

    public Blankiet podany() {
        return blankiet;
    }
}
