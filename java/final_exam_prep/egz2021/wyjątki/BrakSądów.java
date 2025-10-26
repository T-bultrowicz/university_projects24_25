package wyjątki;

public class BrakSądów extends RuntimeException {
    public BrakSądów() {
        super("Nie ma sądu do przydzielenia");
    }
}
