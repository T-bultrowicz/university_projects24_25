package lotto;
import java.util.Arrays;
import wyjątki.NierozstrzygnięteLosowanie;

public class Losowanie implements Lotto {

    //dane
    static private int ID_GENERATOR = 1;
    private final int[] wylosowane;
    private long[] wartNagród;
    private long[] ilZwycięzców;
    private int id;

    // techniczne
    public Losowanie() {
        this.wylosowane = MaszynaLosująca.losujLiczby(TYPOWANYCH_LICZB,
                1, ILOŚĆ_LICZB);
        this.id = ID_GENERATOR++;
    }

    // koniecznie prywatny w finalnej wersji
    public Losowanie(int[] liczby) {
        int[] tmp = liczby.clone();
        Arrays.sort(tmp);
        this.wylosowane = tmp;
        this.id = ID_GENERATOR++;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Losowanie nr ").append(id).append("\n");
        sb.append("Wynik: ");
        for (int i = 0; i < TYPOWANYCH_LICZB; i++) {
            if(wylosowane[i] < 10) {
                sb.append(" ");
            }
            sb.append(wylosowane[i]).append(" ");
        }
        return sb.toString();
    }

    //metody
    public long[] wartNagród() {
        if(wartNagród == null) {
            throw new NierozstrzygnięteLosowanie
            (id, "Losowanie.wartNagród()");
        }
        return this.wartNagród;
    }

    public long[] ilZwycięzców() {
        if(ilZwycięzców == null) {
            throw new NierozstrzygnięteLosowanie
            (id, "Losowanie.ilZwycięzców()");
        }
        return this.ilZwycięzców;
    }

    // Ograniczona widoczność do pakietu, aby potencjalnie nie dało się
    // podejrzeć i dokupić bilet. 
    int[] wylosowane() {
        return this.wylosowane;
    }

    public int id() {
        return this.id;
    }

    // Po przeprowadzeniu oficjalnie CentralaTotolotka wpisuje wartości
    void przeprowadź(long[] wartNagród, long[] ilZwycięzców) {
        if (wartNagród == null || ilZwycięzców == null) {
            return;
        } else if (wartNagród.length != ILOŚĆ_NAGRÓD || ilZwycięzców.length != ILOŚĆ_NAGRÓD) {
            return;
        } else if (this.wartNagród != null) {
            return;
        }
        this.wartNagród = wartNagród.clone();
        this.ilZwycięzców = ilZwycięzców.clone();
    }

}
