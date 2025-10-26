package bankBajtocji;
import java.util.HashMap;

public class Bank {

    // dane
    private HashMap<String, Konto> konta;

    public void zapiszKonto(Konto k) {
        konta.putIfAbsent(k.numer(), k);
    }

    public boolean zawiera(Konto k) {
        return konta.containsValue(k);
    }
}