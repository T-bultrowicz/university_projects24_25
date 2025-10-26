package lotto;

import wyjątki.NullWartość;
import wyjątki.ŹlePodaneLiczby;
import java.util.Arrays;

public class Typowanie implements Lotto {
    
    //dane
    private final int[] typowaneLiczby;

    //techniczne

    // wypełnianie ustalonymi liczbami
    public Typowanie(int[] liczby) throws ŹlePodaneLiczby {
        if(liczby == null)
            throw new NullWartość("Typowanie.konstruktor(int[] liczby)");
        if(!Weryfikacje.dobrzePodaneLiczby(liczby)) {
            throw new ŹlePodaneLiczby("Zamiast " + TYPOWANYCH_LICZB + 
            " liczb z zakresu [1, " + ILOŚĆ_LICZB + "] nie powtarzających się",
            liczby, " w Typowanie.konstruktor(int[] liczby)");
        }
        int[] tmp = liczby.clone();
        Arrays.sort(tmp);
        typowaneLiczby = tmp;
    }

    // wypełnienie na chybił trafił
    public Typowanie() {
        this.typowaneLiczby = MaszynaLosująca.losujLiczby
                            (TYPOWANYCH_LICZB, 1, ILOŚĆ_LICZB);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < TYPOWANYCH_LICZB; i++) {
            if (typowaneLiczby[i] < 10) {
                sb.append(" ");
            }
            sb.append(typowaneLiczby[i]).append(" ");
        }
        return sb.toString();
    }

    // metody
    public int[] typowaneLiczby() {
        return this.typowaneLiczby;
    }
}
