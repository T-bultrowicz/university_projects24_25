package giełda;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class Giełda {
    
    // dane
    private static int ID_GIVER = 1;
    private ArrayList<HashMap <Zasób, DaneZasób>> historia;
    private HashSet<Gracz> gracze;

    // techniczne
    public Giełda() {
        this.historia = new ArrayList<>();
        historia.add(new HashMap<>());
        this.gracze = new HashSet<>();
    }

    // getters
    public int aktDzień() {
        return historia.size() - 1;
    }

    public Zasób[] zasoby() {
        return historia.get(aktDzień()).entrySet().toArray(new Zasób[1]);
    }

    public long cena(Zasób z) {
        return historia.get(aktDzień()).get(z).cena();
    }

    public long cena(Zasób z, int dniTemu) {
        int t = aktDzień() - dniTemu;
        if(t < 0) return -1;
        return historia.get(t).get(z).cena();
    }

    // metody
    public void zapisz(Gracz g) {
        gracze.add(g);
    }

    public String dajID() {
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < 8; i++) {
            sb.append(ML.randomNum());
        }
        sb.append(ID_GIVER++);
        return sb.toString();
    }

    public void zrealizuj(Inwestycja i) {

    }
}
