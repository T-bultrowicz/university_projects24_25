package przydzial;

import java.util.Arrays;

public class PojemnikPodań {
    
    //dane
    private class Podanie implements Comparable<Podanie> {
        public Status status;
        public final Uczeń uczeń;
        public final Szkoła szkoła;
        public final Klasa klasa;
        public final int wynik;
        public int priorytet;
        public int pozycjaLista;

        public Podanie(PodanieGenerator a) {
            this.uczeń = a.uczeń;
            this.klasa = a.klasa;
            this.wynik = a.wynik;
            this.szkoła = a.szkoła;
        }

        @Override
        public int compareTo(Podanie drugiePodanie) {
            return Integer.compare(drugiePodanie.wynik, this.wynik);
        }

    }
    protected Podanie[] podania;

    //techniczne
    public PojemnikPodań(PodanieGenerator[] a) {
        this.podania = new Podanie[a.length];
        for(int i = 0; i < a.length; i++) {
            this.podania[i] = new Podanie(a[i]);
            this.podania[i].priorytet = i;
            this.podania[i].status = Status.NIEROZPATRZONE;
        }
    }

    public Podanie getPodanie(int index) throws IndexOutOfBoundsException {
        if(index < 0 || index >= podania.length)
            throw new IndexOutOfBoundsException();
        return podania[index];
    }

    public int getLength() {
        return podania.length;
    }

    //metody
    public void posortuj() {
        Arrays.sort(podania);
    }

    public PodanieGenerator podanieGenerator(int index) throws IndexOutOfBoundsException {
        if(index < 0 || index >= podania.length)
            throw new IndexOutOfBoundsException();
        Podanie a = podania[index];
        return new PodanieGenerator(a.uczeń, a.szkoła, a.klasa, a.wynik);
    }

    public void nadajPozycjaLista() {
        for(int i = 0; i < podania.length; i++) {
            podania[i].pozycjaLista = i;
        }
    }

    public int getPozycjaLista(int index) throws IndexOutOfBoundsException {
        if(index < 0 || index >= podania.length)
            throw new IndexOutOfBoundsException();
        return podania[index].pozycjaLista;
    }

    public int rozpatrzprzydział(int index) throws IndexOutOfBoundsException {
        if(index < 0 || index >= podania.length)
            throw new IndexOutOfBoundsException();
        Podanie a = podania[index];
        if(!a.klasa.czyMiejsce()) {
            a.status = Status.ODRZUCONE;
            return index++;
        } else if(!a.uczeń.czyGdziekolwiekPrzyjęty()) {
            a.status = Status.PRZYJĘTE;
            a.klasa.zajmijMiejsce();
            a.uczeń.setNajlepszePodanie(a.priorytet);
            return index++;
        } else if(!a.uczeń.maLepsze(a.priorytet)) {
            a.status = Status.PRZYJĘTE;
            int ret = a.uczeń.getNajlepszePodaniePozycja();
            a.uczeń.setNajlepszePodanie(a.priorytet);
            a.klasa.zajmijMiejsce();
            return ret;
        } else {

        }
        return -1;
    }


}
