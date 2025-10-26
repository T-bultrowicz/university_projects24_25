package główna;
import kalendarz.Data;

public class Główna {
    public static void main(String[] args) {
        System.out.println("start");

        Data abc = new Data();
        for(int i = 0; i < 100; i++) {
            abc.następnyDzień();
            System.out.println(abc);
        }
        for(int i = 0; i < 100; i++) {
            abc.poprzedniDzień();
            System.out.println(abc);
        }

        abc.dataZa(171);
        assert abc.równa(new Data(20,6,1900));
        assert abc.późniejsza(new Data(19, 6, 1900));
        System.out.println(abc);

        abc.dataPrzed(149);
        assert abc.równa(new Data(23,1,1900));
        assert !abc.wcześniejsza(new Data(1,1,1504));
        System.out.println(abc);


        System.out.println("koniec");
    }
}
