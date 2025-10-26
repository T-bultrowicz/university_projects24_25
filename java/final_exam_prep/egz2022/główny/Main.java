package główny;

import giełda.*;

public class Main {
    public static void main(String[] args) {
        Zasób a = new Zasób("Drewno", Kategoria.EKOLOGIA);
        Inwestycja ab = new Inwestycja(a, 100, 100000);
        System.out.println(ab);
        Zadanie z = new Zadanie(new Klient("bam", 100000000), 3, 5, 
           new Kategoria[]{Kategoria.AI, Kategoria.BIOTECH},100000, 3);
        System.out.println(z);
    }
}
