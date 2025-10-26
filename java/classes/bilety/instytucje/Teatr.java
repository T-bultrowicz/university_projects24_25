package instytucje;

import osoby.Osoba;

import java.util.Arrays;

public class Teatr extends InstytucjaAbstr{
    // Dane
    private boolean[][] miejsca; // Indeksowana zdarzeniami tablica wolnych miejsc
    // Techniczne

    public Teatr(String nazwa, int liczbaWydarzeń, int liczbaMiejsc) {
        super(nazwa);
        assert liczbaWydarzeń > 0: "Teatr.Teatr: w " + this +
                                   ", liczbaWydarzeń <= 0: " + liczbaWydarzeń;
        assert liczbaMiejsc > 0: "Teatr.Teatr: w " + this +
                                 ", liczbaMiejsc <= 0: " + liczbaMiejsc;

        this.miejsca = new boolean[liczbaWydarzeń][liczbaMiejsc];
        // Poniższe nie jest konieczne, ale jawnie podaje nasze intencje

        for (int i = 0; i < liczbaWydarzeń; i++) {
            for (int j = 0; j < liczbaMiejsc; j++) {
                miejsca[i][j] = false; // Wszystkie miejsca są wolne
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Teatr{").append(nazwa()).append(", miejsca=[");
        for (int i = 0; i < miejsca.length; i++) {
            sb.append("[");
            for (int j = 0; j < miejsca[i].length; j++) {
                sb.append(miejsca[i][j] ? "X" : "O");
                if (j < miejsca[i].length - 1) {
                    sb.append(", ");
                }
            }
            sb.append("]");
            if (i < miejsca.length - 1) {
                sb.append(", ");
            }
        }
        sb.append("]}");
        return sb.toString();
    }
    // Operacje

    @Override
    public boolean wydajBilety(Wydarzenie wyd, Osoba osoba) {
        assert  wyd != null: "Teatr.wydajBilety: w " +
                this +
                ", wyd == null dla osoby " + osoba;
        assert osoba != null: "Teatr.wydajBilety: w " +
                this +
                ", osoba == null dla wydarzenia " + wyd;

        assert wyd.id() >= 0 && wyd.id() < miejsca.length:
                "Teatr.wydajBilety: w " + this +
                ", wyd.id() = " + wyd.id() +
                ", miejsca.length = " + miejsca.length;

        boolean[] miejsca = this.miejsca[wyd.id()];

        for(int i = 0; i < miejsca.length; i++) {
            if(!miejsca[i] && osoba.czyAkceptujeszMiejsce(i, wyd)) {
                miejsca[i] = true; // Zarezerwuj miejsce
                osoba.weźBilet(new Bilet(wyd, i)); // Numerujemy miejsca od 0
                return true;
            } // if
        } // for i

        return false; // Nie ma wolnych miejsc lub widz nic nie wybrał
    }

    @Override
    public boolean wydajBilety(Wydarzenie wyd, Osoba[] osoby) {
        assert osoby != null: "Teatr.wydajBilety: w " +
                this + ", osoby == null dla wydarzenia " + wyd;
        assert wyd != null: "Teatr.wydajBilety: " +
                this + ", wyd == null dla osób " + Arrays.toString(osoby);

        boolean[] miejsca = this.miejsca[wyd.id()];

        for(int i=0, ileWolnych = 0; i < miejsca.length; i++) {
            if(!miejsca[i]) {
                ileWolnych++;
                if(ileWolnych == osoby.length) {
                    for(int j = 0; j < osoby.length; j++) {
                        miejsca[i - j] = true; // Zarezerwuj miejsce
                        osoby[j].weźBilet(new Bilet(wyd, i - j)); // Numerujemy miejsca od 0
                    } // for j
                    return true;
                } // if ciąg wystarczającej długości
            } // if wolne
            else
                ileWolnych = 0;
        } // for i

        return false;
    }

    @Override
    public int ileWolnych(Wydarzenie wyd) {
        assert wyd != null: "Teatr.ileWolnych: w " +
        this + ", wyd == null";
        assert wyd.id() >= 0 && wyd.id() < miejsca.length:
                "Tearr.ileWolnych: w " + this +
                ", wyd.id() = " + wyd.id() +
                ", miejsca.length = " + miejsca.length;
        int res = 0;
        for(boolean b : miejsca[wyd.id()]) {
            if(!b) res++;
        }
        return res;        
    }

}
