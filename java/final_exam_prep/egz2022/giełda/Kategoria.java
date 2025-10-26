package giełda;

public enum Kategoria {
    BIOTECH("Biotech"),
    NANOTECH("Nanotech"),
    AI("AI"),
    EKOLOGIA("Ekologia");

    private String nazwa;
    private Kategoria(String nazwa) {
        this.nazwa = nazwa;
    }
    
    @Override
    public String toString() {
        return nazwa;
    }
}
