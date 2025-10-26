package tablice;

import java.util.Arrays;

public class TablicaZLicznikami<T> {
    // dane
    private final T[] elty;  // Zawartość tablicy (String tylko dlatego by odróżnić od pozostały dwu tablic)

    private final int[] licznikiOdczytu; // Tu liczymy dostępy do elementów tablicy
    private final int[] licznikiZapisu;  // j.w.

    // techniczne
    @SuppressWarnings("unchecked")
    public TablicaZLicznikami(int rozmiar) {
        elty = (T[]) new Object[rozmiar];
        licznikiOdczytu = new int[rozmiar];
        licznikiZapisu = new int[rozmiar];
        // Korzystamy z tego, że Java inicjuje tablice zerami
    }

    @Override
    public String toString() {
        return "TablicaZLicznikami{" + Arrays.toString(elty) + '}';
    }

    // operacje
    private void sprawdźIndeks(int i) throws ZłyIndeks {
        if(i < 0 || i >= elty.length)
            throw new ZłyIndeks("Zły indeks: " + i +
                  " dla długości tablicy " + elty.length);
    }

    public T daj(int i) throws ZłyIndeks {
        sprawdźIndeks(i);
        licznikiOdczytu[i]++;
        return elty[i];
    }

    public void ustaw(int i, T el) throws ZłyIndeks {
        sprawdźIndeks(i);
        licznikiZapisu[i]++;
        elty[i] = el;
    }

    public int dajRozmiar(){
        return elty.length;
    }

    private int dajLicznik(int i, int[] liczniki) throws ZłyIndeks {
        sprawdźIndeks(i);
        return liczniki[i];
    }

    public int dajLicznikOdczytów(int i) throws ZłyIndeks {
         return dajLicznik(i, licznikiOdczytu);
    }

    public int dajLicznikZapisów(int i) throws ZłyIndeks {
        return dajLicznik(i, licznikiZapisu);
    }
}