package biuropodróży;

public class Miejsce implements ParametrM {
    
    // dane
    private final String nazwa;
    private final int temperatura;
    protected final int[] bazaAtrakcyjna;

    // techniczne
    public Miejsce(String nazwa, int temperatura, int[] bazaAtrakcyjna) {
        if(bazaAtrakcyjna.length != __M)
            throw new NullPointerException("Boomm");
        this.nazwa = nazwa;
        this.temperatura = temperatura;
        this.bazaAtrakcyjna = bazaAtrakcyjna.clone();
    }

    // getters
    public int[] bazaAtrakcyjna(int rok, int dzieńRoku) {
        return bazaAtrakcyjna;
    }

    public String nazwa() {
        return nazwa;
    }

    public int temperatura() {
        return temperatura;
    }
}
