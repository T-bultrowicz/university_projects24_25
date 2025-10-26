package wyjątki;

public class Najwyższa extends RuntimeException {
    public Najwyższa() {
        super("Już odwołano się do najwyższej instancji!\n");
    }
}
