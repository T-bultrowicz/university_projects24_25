package giełda;

import java.util.Random;

public abstract class ML {
    private final static Random rng = new Random();
    public static int przedział(int od, int dodo) {
        return rng.nextInt(od, dodo - od + 1);
    }

    public static int randomNum() {
        return przedział(0, 9);
    }
}
