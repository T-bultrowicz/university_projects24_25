package giełda;

public abstract class Kwota {
    public static String kwota(long kwota) {
        return (kwota / 100) + "," + String.format("%02d", kwota % 100) + "zł"; 
    }
}
