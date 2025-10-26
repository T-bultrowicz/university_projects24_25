package lotto;
import java.util.Collection;
import wyjątki.NullWartość;
import wyjątki.ŹlePodaneLiczby;

public class GraczStałoliczbowy extends GraczStały {
    
    // dane
    private final int[] ulubioneLiczby;

    // techniczne
    public GraczStałoliczbowy(String imię, String nazwisko, String PESEL, 
            long stanKonta, CentralaTotolotka centrala, Collection<Kolektura> 
            ulubione, int[] ulubioneLiczby) throws ŹlePodaneLiczby {
        super(imię, nazwisko, PESEL, stanKonta, centrala, ulubione, 10);
        if(ulubioneLiczby == null) {
            throw new NullWartość("GraczStałoliczbowy.konstruktor()");
        }
        if (!Weryfikacje.dobrzePodaneLiczby(ulubioneLiczby))
            throw new ŹlePodaneLiczby(TYPOWANYCH_LICZB + " z zakresu [1, " 
                    + ILOŚĆ_LICZB + "] nie powtarzających się", ulubioneLiczby,
                    " w GraczStałoliczbowy.konstruktor()");
        this.ulubioneLiczby = ulubioneLiczby;
    }

    // Zdegenerowany konstruktor, losuje wartości nie podane, tak jak zostało
    // opisane w GraczStały oraz dolosowuje ulubioneLiczby.
    public GraczStałoliczbowy(String imię, String nazwisko, String PESEL, 
                long stanKonta, CentralaTotolotka centrala) {
        super(imię, nazwisko, PESEL, stanKonta, centrala);
        this.ulubioneLiczby = MaszynaLosująca.losujLiczby
                                (TYPOWANYCH_LICZB, 1, ILOŚĆ_LICZB);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Gracz stałoliczbowy - \nUlubione liczby: ");
        for (int liczba : ulubioneLiczby) {
            sb.append(liczba).append(" ");
        }
        sb.append("\nUlubione kolektury: ");
        for (Kolektura k : ulubione) {
            sb.append(k.nrKolektury()).append(" ");
        }
        sb.append("\n").append(super.toString());
        return sb.toString();
    }

    // metody
    @Override
    protected Blankiet twórzBlankiet() {
        Blankiet blankiet = new Blankiet();
        for(int liczba : ulubioneLiczby) {
            blankiet.zaznaczTyp(1, liczba);
        }
        for(int i = 2; i <= ILOŚĆ_TYPÓW; i++) {
            blankiet.zaznaczAnuluj(i);
        }
        blankiet.zaznaczIlośćZakładów(ILOŚĆ_ZAKŁADÓW);
        return blankiet;
    }
}
