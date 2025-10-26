package instytucje;

import osoby.Osoba;

import java.util.Arrays;

public abstract class InstytucjaAbstr implements Instytucja {
    // Dane
    private String nazwa;
    // Techniczne
    public InstytucjaAbstr(String nazwa) {
        assert nazwa != null: "InstytucjaAbstr.InstytucjaAbstr: w " +
                              this +
                              ", nazwa == null";
        this.nazwa = nazwa;
    }

    // Operacje
    @Override
    public boolean wydajBilety(Wydarzenie wyd, Osoba[] osoby) {
        assert osoby != null: "InstytucjaAbstr.wydajBilety: w " +
                              this +
                              ", osoby == null dla wydarzenia " + wyd;
        assert wyd != null: "InstytucjaAbstr.wydajBilety: " +
                            this +
                            ", wyd == null dla osób " +
                            Arrays.toString(osoby);

        for (Osoba osoba: osoby) {
            if (!wydajBilety(wyd, osoba)) {
                return false;
            }
        } // for
        return true;
    }

    @Override
    public int ileWolnych(Wydarzenie[] wyd) {
        assert wyd != null: "InstytucjaAbstr.ileWolnych: w " +
                            this +
                            ", tablica wydarzeń to null";
        int res = 0;
        for(Wydarzenie w : wyd) {
            res += ileWolnych(w);
        } 
        return res;
    }

    public String nazwa() {
        return nazwa;
    }
}
