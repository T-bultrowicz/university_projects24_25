package wybory;
import java.util.Arrays;

public class Komitet implements Comparable<Komitet> {
    
    //dane
    private Kandydat[] kandydaci;
    private Kandydat[] kandydaciWybrani;
    private int licznik;
    public final int ilośćGłosów;

    //techniczne
    public Komitet(Kandydat[] kandydaci) throws NullPointerException {
        if(kandydaci == null) throw new NullPointerException();
        int suma = 0;
        for(Kandydat a : kandydaci) {
            if(a == null) throw new NullPointerException();
            suma += a.ilośćGłosów;
        }
        this.kandydaci = kandydaci;
        Arrays.sort(this.kandydaci);
        this.kandydaciWybrani = null;
        this.ilośćGłosów = suma;
        this.licznik = 0;
    }

    @Override
    public int compareTo(Komitet drugiKomitet) {
        return Integer.compare(drugiKomitet.ilośćGłosów, this.ilośćGłosów);
    }

    public void dodajKandydata() {
        licznik++;
    }

    public void stworzKandydatowWybranych() {
        if(licznik == 0) return;
        kandydaciWybrani = new Kandydat[licznik];
        for(int i = 0; i < licznik; i++) {
            kandydaciWybrani[i] = kandydaci[i];
        }
    }

    public Kandydat[] getKandydaciWygrani() {
        return kandydaciWybrani;
    }
}
