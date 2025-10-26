package niezmiennik;

public class NiezmiennikException extends Exception {
    public NiezmiennikException() {
        super();
    }

    public NiezmiennikException(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Naruszenie niezmiennika: " + this.getMessage();
    }
}
