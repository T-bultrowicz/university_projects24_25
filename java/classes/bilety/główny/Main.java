package główny;

import instytucje.*;
import osoby.*;

public class Main {
    public void testuj(){
        Instytucja muzeum = new Muzeum("Muzeum Narodowe", 3, 2);
        Instytucja teatr = new Teatr("Och-teatr", 3, 3);
        Wydarzenie w1 = new Wydarzenie(muzeum, 0, "Wystawa malarstwa Wyspiańskiego");
        Wydarzenie w2 = new Wydarzenie(muzeum, 1, "Architektura romańska");

        Wydarzenie w3 = new Wydarzenie(teatr, 0, "Hamlet");
        Wydarzenie w4 = new Wydarzenie(teatr, 1, "Ferdydurke");
        Wydarzenie w5 = new Wydarzenie(teatr, 2, "Złodziej");
        Wydarzenie[] pakiet = new Wydarzenie[3];
        pakiet[0] = w3;
        pakiet[1] = w4;
        pakiet[2] = w5;

        System.out.println(teatr.ileWolnych(pakiet));
        teatr.wydajBilety(w3, new Kapryśny("Jan"));
        System.out.println(teatr);
        System.out.println(teatr.ileWolnych(pakiet));
        teatr.wydajBilety(w3, new Kapryśny("Ewa"));
        System.out.println(teatr);
        System.out.println(teatr.ileWolnych(pakiet));
        teatr.wydajBilety(w3, new Osoba[]{new MiłośnikTeatru("Ula"),
                                        new MiłośnikTeatru("Ala")});
        System.out.println(teatr);
        System.out.println(teatr.ileWolnych(pakiet));
        Osoba[] grupka = new Osoba[3];
        grupka[0] = new MiłośnikTeatru("Grzegorz");
        grupka[1] = new MiłośnikTeatru("Roman");
        grupka[2] = new Kapryśny("Małgorzata");

        muzeum.wydajBilety(w1, grupka[0]);
        muzeum.wydajBilety(w2, grupka[2]);
        assert muzeum.wydajBilety(w2, grupka) == false;
        teatr.wydajBilety(w5, grupka);
        System.out.println(muzeum);
        System.out.println(teatr);

        System.out.println(muzeum.ileWolnych(w2));
        System.out.println(muzeum.ileWolnych(w1));
        System.out.println(teatr.ileWolnych(pakiet));

    }

    public static void main(String[] args) {
       System.out.println("Hej kulturo!");

       Main m = new Main();
       m.testuj();

       System.out.println("Koniec");
    }
}
