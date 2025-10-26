package wyjątki;
import lotto.Kwota;

public class BrakFunduszy extends Exception {
    
    private long brakującaKwota;

    public BrakFunduszy(long brakującaKwota, String message) {
        super("Brak funduszy na koncie. Brakuje " + 
                Kwota.kwota(brakującaKwota) + message);
        this.brakującaKwota = brakującaKwota;
    }

    public long brakującaKwota() {
        return brakującaKwota;
    }
}
