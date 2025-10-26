package instytucje;

public class Wydarzenie {
    // Dane
    private Instytucja instytucja;
    private int id;
    private String nazwa;

    // Techniczne
    public Wydarzenie(Instytucja instytucja, int id, String nazwa) {
        this.instytucja = instytucja;
        this.id = id;
        this.nazwa = nazwa;
    }

    @Override
    public String toString() {
        return "Wydarzenie{" +
                "instytucja=" + instytucja +
                ", id=" + id +
                ", nazwa='" + nazwa + '\'' +
                '}';
    }

    // Operacje
    public int id() {
        return id;
    }
}
