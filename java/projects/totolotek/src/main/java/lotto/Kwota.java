package lotto;

public abstract class Kwota {
    static public String kwota(long k) {
        StringBuilder sb = new StringBuilder();
        sb.append((k / 100) + ",");
        sb.append(String.format("%02d", k % 100));
        sb.append(" zł");
        return sb.toString();
    }
}
