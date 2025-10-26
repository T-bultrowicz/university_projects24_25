package biuropodróży;

public class Uzdrowisko extends Miejsce {

    // dane 
    private int wspWzrostu;

    // techniczne
    public Uzdrowisko(String nazwa, int temperatura, int[] bazaAtrakcyjna
                , int wspWzrostu) {
        super(nazwa, temperatura, bazaAtrakcyjna);
        this.wspWzrostu = wspWzrostu;
    }
    
    @Override
    public int[] bazaAtrakcyjna(int rok, int dzieńRoku) {
        int[] res = bazaAtrakcyjna.clone();
        if(Kalendarz.weekend(rok, dzieńRoku))
            for(int i = 0; i < res.length; i++)
                res[i] += res[i] * wspWzrostu / 100;
        return res;
    }
}
