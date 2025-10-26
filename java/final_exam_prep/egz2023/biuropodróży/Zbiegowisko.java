package biuropodróży;

public class Zbiegowisko extends Miejsce {
    
    // dane
    private int wspSpadku;

    // techniczne
    public Zbiegowisko(String nazwa, int temperatura, int[] bazaAtrakcyjna
                        , int wspSpadku) {
        super(nazwa, temperatura, bazaAtrakcyjna);
        this.wspSpadku = wspSpadku;
    }

    // metody
    @Override
    public int[] bazaAtrakcyjna(int rok, int dzieńRoku) {
        int[] res = bazaAtrakcyjna.clone();
        if(Kalendarz.ferie(rok, dzieńRoku) || Kalendarz.wakacje(rok, dzieńRoku))
            for(int i = 0; i < res.length; i++)
                res[i] -= res[i] * wspSpadku / 100;
        return res;
    }

}
