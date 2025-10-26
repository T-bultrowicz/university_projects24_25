package przydzial;

public class Kuratorium {
    
    //dane
    private Uczeń[] uczniowie;
    private Szkoła[] szkoły;

    //techniczne
    public Kuratorium(Uczeń[] uczniowie, Szkoła[] szkoły) throws NullPointerException {
        if(uczniowie == null || szkoły == null) throw new NullPointerException();
        for(Uczeń a : uczniowie)
            if(a == null) throw new NullPointerException();
        for(Szkoła a : szkoły)
            if(a == null) throw new NullPointerException();

        this.uczniowie = uczniowie;
        this.szkoły = szkoły;
    }

    //metody
    public void przeprowadźPrzydział() {

        PojemnikPodań[] zebranePodania = new PojemnikPodań[uczniowie.length];
        for(int i = 0; i < uczniowie.length; i++) {
            zebranePodania[i] = uczniowie[i].getPojemnikPodań();
        }
        ListaKuratoryjna kolejka = new ListaKuratoryjna(zebranePodania);
        kolejka.zrealizujPrzydział();
    }
}
