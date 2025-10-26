package biuropodróży;

public abstract class Klient {
     
    // dane
    private String nazwa;
    protected Strategia strategia;
    protected int środki;
    
    // techniczne
    public Klient(String nazwa, int środki, Strategia strategia) {
        this.nazwa = nazwa;
        this.środki = środki;
        this.strategia = strategia;
    }

    @Override
    public String toString() {
        return "Klient " + nazwa + ", stan funduszy: " + środki;
    }

    // metody
    abstract protected boolean porównaj(Wycieczka a, Wycieczka b);
    private void mergesort(Wycieczka[] tab, int od, int dodo) {
        if(od == dodo) return;
        int mid = (od + dodo) / 2;
        mergesort(tab, od, mid);
        mergesort(tab, mid + 1, dodo);
        Wycieczka[] res = new Wycieczka[dodo - od];
        int l = od, r = mid + 1, ind = 0;
        while(l < mid && r < dodo)
            if(porównaj(tab[l], tab[r]))
                res[ind++] = tab[l++];
            else res[ind++] = tab[r++];
        while(l < mid)
            res[ind++] = tab[l++];
        while(r < dodo)
            res[ind++] = tab[r++];
        for(int i = od; i < dodo; i++)
            tab[i] = res[i - od];
        return;
    }

    private Wycieczka[] wybierzWycieczki(Wycieczka[] w) {
        return strategia.wybierz(w, środki);
    }

    public void odwiedźBiuro(Biuro b) {
        Wycieczka[] wycieczki = null; // TODO
        mergesort(wycieczki, 0, wycieczki.length);
        b.zakupWycieczki(wybierzWycieczki(wycieczki), this);
    }

    public void zapisanie(Wycieczka w) {
        środki -= w.cena();
    }
}
