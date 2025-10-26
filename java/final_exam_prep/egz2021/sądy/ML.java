package sądy;
import java.util.Random;

public abstract class ML {
    private static Random rng = new Random();
    public static int getInt(int from, int to) {
        return rng.nextInt(from, to - from + 1);
    }
}
