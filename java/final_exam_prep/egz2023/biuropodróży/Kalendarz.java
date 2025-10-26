package biuropodróży;

public abstract class Kalendarz {
    
    public static boolean weekend(int rok, int dzień) {
        return (rok * 365 + dzień - 2) % 7 >= 5;
    }

    public static boolean ferie(int rok, int dzień) {
        if(rok % 2 == 0) return dzień >= 23 && dzień <= 40;
        else return dzień >= 41 && dzień <= 58;
    }

    public static boolean zima(int rok, int dzień) {
        return dzień <= 60 || dzień >= 331;
    }

    public static boolean wakacje(int rok, int dzień) {
        return dzień >= 160 && dzień <= 220;
    }
}
