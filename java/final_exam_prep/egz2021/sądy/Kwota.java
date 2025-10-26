package sądy;

public abstract class Kwota {
    public static String kwota(long l) {
        StringBuilder sb = new StringBuilder();
        sb.append(l / 100).append(", ").append(l % 100).append(" zł");
        return sb.toString();
    }
}
