package bankBajtocji;

public class ZleceniePrzelewu {
    
    // dane
    private final String obciążane;
    private final String beneficjent;
    private final String waluta;
    private final long kwota;

    // techniczne
    public ZleceniePrzelewu(String obciążane, String beneficjent, String waluta
                    , long kwota) {
        this.obciążane = obciążane;
        this.beneficjent = beneficjent;
        this.waluta = waluta;
        this.kwota = kwota;
    }

    // getters
    public String obciążane() {
        return obciążane;
    }

    public String beneficjent() {
        return beneficjent;
    }

    public String waluta() {
        return waluta;
    }

    public long kwota() {
        return kwota;
    }
}
