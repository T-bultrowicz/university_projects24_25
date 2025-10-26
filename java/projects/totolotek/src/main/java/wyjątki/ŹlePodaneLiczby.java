package wyjątki;
import java.util.Arrays;

public class ŹlePodaneLiczby extends Exception {
    public ŹlePodaneLiczby(String message, int[] liczby, String mes2) {
        super("Zamiast " + message + " podano: " + Arrays.toString(liczby) + mes2);
    }

    public ŹlePodaneLiczby(String message) {
        super("Podano błędne liczby " + message);
    }
}
