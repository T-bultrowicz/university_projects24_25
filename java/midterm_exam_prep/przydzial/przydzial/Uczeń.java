package przydzial;

import niezmiennik.NiezmiennikException;

public class Uczeń {
    
    //dane
    private String imię;
    private String nazwisko;
    private PojemnikPodań podania;
    private int najlepszePodanie;

    //techniczne
    public Uczeń(String imię, String nazwisko, PodanieGenerator[] podania) throws NullPointerException, NiezmiennikException {
        if(imię == null || nazwisko == null || podania == null) throw new NullPointerException();
        for(PodanieGenerator a : podania)
            if(a == null) throw new NullPointerException();
        
        if(imię == "" || nazwisko == "") throw new NiezmiennikException("Pustę pole imię lub nazwisko!");
        this.imię = imię;
        this.nazwisko = nazwisko;
        this.podania = new PojemnikPodań(podania);
        this.najlepszePodanie = -1;
    }

    public PojemnikPodań getPojemnikPodań() {
        return podania;
    }

    //metody
    public boolean czyGdziekolwiekPrzyjęty() {
        return najlepszePodanie != -1;
    }

    public boolean maLepsze(int priorytet) {
        return najlepszePodanie >= priorytet;
    }

    public void setNajlepszePodanie(int i) throws IndexOutOfBoundsException {
        if(i < 0 || i >= podania.getLength()) throw new IndexOutOfBoundsException();
        najlepszePodanie = i;
    }

    public int getNajlepszePodaniePozycja() throws IndexOutOfBoundsException {
        return podania.getPozycjaLista(najlepszePodanie);
    }
}
