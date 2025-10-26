package wyjątki;

public class BrakKuponuBaza extends RuntimeException {

    public BrakKuponuBaza(String message) {
        super("Brak kuponu w bazie: " + message);
    }

    public BrakKuponuBaza(int nrkol, String id) {
        super("Brak kuponu o identyfikatorze " + id + 
                        " w bazie kolektury o numerze " + nrkol + "\n");
    }
}
