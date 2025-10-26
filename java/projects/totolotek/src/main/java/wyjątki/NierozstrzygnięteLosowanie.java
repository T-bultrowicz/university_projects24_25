package wyjątki;

public class NierozstrzygnięteLosowanie extends RuntimeException {
    
    public NierozstrzygnięteLosowanie(int nrLosowania, String message) {
        super(message + "\nLosowanie o numerze " + nrLosowania + 
                    " nie zostało rozstrzygnięte.");
    }
}
