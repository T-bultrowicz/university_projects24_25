package wyjątki;

public class BrakImplementacji extends RuntimeException {

    //techniczne
    public BrakImplementacji(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "BrakImplementacji operacji w " + getMessage();
    }
}
