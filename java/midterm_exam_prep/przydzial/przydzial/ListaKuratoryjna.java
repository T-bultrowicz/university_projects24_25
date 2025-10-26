package przydzial;

public class ListaKuratoryjna {

    //dane
    private PojemnikPodań pojemnik;

    //techniczne
    public ListaKuratoryjna(PojemnikPodań[] pakietyPodań) {

        int suma = 0;
        for(PojemnikPodań a : pakietyPodań) {
            suma += a.getLength();
        }
        PodanieGenerator[] generuj = new PodanieGenerator[suma];

        int j = 0;
        for(PojemnikPodań a : pakietyPodań) {
            for(int i = 0; i < a.getLength(); i++) {
                generuj[j++] = a.podanieGenerator(i);
            }
        }
        pojemnik = new PojemnikPodań(generuj);
        pojemnik.posortuj();
        pojemnik.nadajPozycjaLista();
    }

    //metody
    public void zrealizujPrzydział() {
        int i = 0;
        while(i < pojemnik.getLength()) {
            i = pojemnik.rozpatrzprzydział(i);
        }
    }
}