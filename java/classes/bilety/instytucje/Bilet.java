package instytucje;

public class Bilet {
    // Dane
    private final Wydarzenie wydarzenie;
    private final int miejsce;

    // Techniczne
    public Bilet(Wydarzenie wydarzenie, int miejsce) {
        this.wydarzenie = wydarzenie;
        this.miejsce = miejsce;
    }

    // Operacje
    @Override
    public String toString() {
        return "Bilet{" +
                "wydarzenie=" + wydarzenie +
                ", miejsce=" + miejsce +
                '}';
    }

    // Operacje
    public Wydarzenie wydarzenie() {
        return wydarzenie;
    }

    public int miejsce() {
        return miejsce;
    }
}