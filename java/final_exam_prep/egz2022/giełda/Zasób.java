package giełda;

public record Zasób(String nazwa, Kategoria kategoria) {
    @Override
    public int hashCode() {
        return nazwa.hashCode();
    }
}
