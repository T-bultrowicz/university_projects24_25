package wyjątki;
public class NiepoprawneDaneException extends Exception {
    public NiepoprawneDaneException() {
        super();
    }
    public NiepoprawneDaneException(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Wpisano niepoprawne dane: " + this.getMessage();
    }
}