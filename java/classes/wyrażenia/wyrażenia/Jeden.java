package wyrażenia;

public class Jeden extends Stała {
    public Jeden() {
        super(1);
    }
    @Override
    public Wyrażenie dodaj(Wyrażenie wyrażenie) {
        return wyrażenie;
    }

    @Override
    public Wyrażenie dodajJakoDrugi(Wyrażenie wyrażenie) {
        return wyrażenie;
    }
}
