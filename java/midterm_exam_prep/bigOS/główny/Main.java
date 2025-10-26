package główny;
import java.util.Random;

import bigos.*;
import wyjątki.NiepoprawneDaneException;

public class Main {

    static void testuj() {
        try {
            Random rng = new Random();
            Element[] system = new Element[50];
            system[0] = new Katalog(null, "");
            system[1] = new Katalog((Katalog) system[0], "home");
            system[2] = new Katalog((Katalog) system[0], "bin");
            system[3] = new Katalog((Katalog) system[0], "dick");
            for(int i = 4; i < 10; i++) {
                system[i] = new Katalog((Katalog) system[1], "folder" + i);
            }
            for(int i = 10; i < 30; i++) {
                int a = rng.nextInt(10);
                system[i] = new Plik((Katalog) system[a], "plik" + i);
                System.out.println(system[i]);
            }
            for(int j = 30; j < 50; j++) {
                int a = rng.nextInt(10);
                int b = 10 + rng.nextInt(20);
                system[j] = new Dowiązanie((Katalog) system[a], (Plik) system[b]);
                System.out.println(system[j]);
            }
            System.out.println(((Katalog) system[0]).wypiszElementy());
            system[11].usuń(); 
            system[12].usuń();
            system[10].usuń();
            System.out.println(((Katalog) system[0]).wypiszElementy());       
        } catch(NullPointerException | NiepoprawneDaneException nde) {
            System.out.println(nde);
        }
    }
    public static void main(String[] args) {
        testuj();
    }
}