package giełda;
import java.util.ArrayList;

public interface Strategia {
    public int ileKupić(Zasób z, Giełda g, ArrayList<Program> p);
    public boolean czySprzedać(Inwestycja i, Giełda g, ArrayList<Program> p);
    public void dodaj(Broker b, Program p);
}
