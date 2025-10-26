package instytucje;

import java.util.Random;

public class RNG {

    private static Random rng = new Random();
    public static boolean nextBoolean() {
        return rng.nextBoolean();
    }
}
