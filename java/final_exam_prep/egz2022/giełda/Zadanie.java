package giełda;

public record Zadanie(Klient klient, int maxSpadek, int minWzrost, 
    Kategoria[] kategorie, long fundusz, int ileDni) {
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Kupuj w funduszu ").append(Kwota.kwota(fundusz));
        sb.append("\nW kategoriach - ");
        for(Kategoria a : kategorie)
            sb.append(a).append(", ");
        sb.append("\nW przedziale - ").append(maxSpadek).append("% straty i ");
        sb.append(minWzrost).append("% zysku trzymaj aktywa.");
        sb.append("\nW okresie - ").append(ileDni).append( " dni.");
        sb.append("\nZleca - ").append(klient);
        return sb.toString();
    }
}