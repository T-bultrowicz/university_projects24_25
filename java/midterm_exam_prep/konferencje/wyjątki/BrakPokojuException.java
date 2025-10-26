package wyjątki;

public class BrakPokojuException extends Exception {
    public BrakPokojuException() {
        super();
    }

    public BrakPokojuException(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Nie ma odpowiedniej sali" + getMessage();
    }
}
