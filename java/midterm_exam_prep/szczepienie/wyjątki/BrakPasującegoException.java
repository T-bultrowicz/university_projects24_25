package wyjątki;

public class BrakPasującegoException extends Exception {
    public BrakPasującegoException() {
        super();
    }

    public BrakPasującegoException(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Nie ma punktu pas. dla pacjenta! " + getMessage();
    }
}
