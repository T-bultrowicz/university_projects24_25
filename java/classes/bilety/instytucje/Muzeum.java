package instytucje;

import osoby.Osoba;

import java.util.Arrays;

public class Muzeum extends InstytucjaAbstr {
    // Dane
    private int[] miejsca; // Tablica indeksowana wydarzeniami

    // Techniczne

    public Muzeum(String nazwa, int[] miejsca) {
        super(nazwa);
        assert miejsca != null: "Muzeum.Muzeum: w " + this + ", miejsca == null";

        this.miejsca = miejsca.clone();
    }

    public Muzeum(String nazwa, int domyślnaLiczbaMiejsc, int liczbaWydarzeń) {
        super(nazwa);
        this.miejsca = new int[liczbaWydarzeń];
        for (int i = 0; i < liczbaWydarzeń; i++) {
            miejsca[i] = domyślnaLiczbaMiejsc;
        }
    }

    @Override
    public String toString() {
        return "Muzeum{" + nazwa() +
                ", miejsca=" + Arrays.toString(miejsca) +
                '}';
    }

    // Operacje
    @Override
    public boolean wydajBilety(Wydarzenie wyd, Osoba osoba) {
        assert wyd != null: "Muzeum.wydajBilety: w " +
                this +
                ", wyd == null dla osoby " + osoba;
        assert osoba != null: "Muzeum.wydajBilety: w " +
                this +
                ", osoba == null dla wydarzenia " + wyd;

        assert wyd.id() >= 0 && wyd.id() < miejsca.length:
                "Muzeum.wydajBilety: w " + this +
                ", wyd.id() = " + wyd.id() +
                ", miejsca.length = " + miejsca.length;

        if(miejsca[wyd.id()] > 0) {
            miejsca[wyd.id()]--;
            osoba.weźBilet(new Bilet(wyd, -1)); // -1 bo nie numerujemy
            return true;
        }
        else
            return false;
    }

    @Override
    public int ileWolnych(Wydarzenie wyd) {
        assert wyd != null: "Muzeum.ileWolnych: w " +
        this + ", wyd == null";
        assert wyd.id() >= 0 && wyd.id() < miejsca.length:
                "Muzeum.ileWolnych: w " + this +
                ", wyd.id() = " + wyd.id() +
                ", miejsca.length = " + miejsca.length;
        return miejsca[wyd.id()];
    }
}
