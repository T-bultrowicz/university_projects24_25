package giełda;

public record Inwestycja(Zasób zasób, long cenaKupna, int ilośćKupionych) {
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Inwestycja w ").append(zasób).append(" sztuk ");
        sb.append(ilośćKupionych).append(" po cenie ");
        sb.append(Kwota.kwota(cenaKupna));
        return sb.toString();
    }
}
