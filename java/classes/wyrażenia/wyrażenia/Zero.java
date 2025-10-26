package wyrażenia;

public class Zero extends Stała {
    public Zero() {
        super(0.0);
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
