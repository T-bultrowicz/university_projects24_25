package bankBajtocji;

public class ZagregowaneExcep extends OperacjaTworząca {
    public ZagregowaneExcep(Konto k) {
        super("Próba podpięcia konta zagregowanego do " + k);
    }
}
