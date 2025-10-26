package główny;
import java.util.Random;

import bilbo.*;
import skarb.Skarb;

public class Main {

    Skarb[] generujTablicęSkrabów(int ile, int maxSize) {
        assert (ile > 0 && maxSize > 0);
        Random rng = new Random();
        Skarb skarby[] = new Skarb[ile];

        for(int i = 0; i < ile; i++) {
            skarby[i] = new Skarb(rng.nextInt(maxSize));
        }
        return skarby;
    }

    Krasnal[] generujTablicęKrasnali(int ile, int maxWor) {
        assert (ile > 0 && maxWor > 0);
        Random rng = new Random();
        Krasnal krasnale[] = new Krasnal[ile];

        for(int i = 0; i < ile; i++) {
            int rodzaj = rng.nextInt(3);
            int wor = rng.nextInt(maxWor) + 1;
            switch (rodzaj) {
                case 0:
                    krasnale[i] = new KrasnalLos("Jacek", wor, rng.nextFloat() + (float) 0.3);
                    break;
                case 1:
                    krasnale[i] = new KrasnalAnalityk("Bartuś", wor, (rng.nextFloat() * 2 - 1) * 5);
                    break;
                case 2: default:
                    krasnale[i] = new KrasnalProcent("Adaś", wor, 1 - rng.nextFloat());
            }
        }
        return krasnale;
    }

    boolean krasnalGra(Krasnal[] k) {
        for(int i  = 0; i < k.length; i++) {
            if(k[i].getCzyGraDalej()) return true;
        }
        return false;
    }

    void Rozegraj(Skarb[] s, Krasnal[] k) {
        int indeksSkarb = 0, indeksKrasnal = 0;
        while(indeksSkarb < s.length && krasnalGra(k)) {
            if(k[indeksKrasnal].getCzyGraDalej()) {
                boolean dec = k[indeksKrasnal].decyzjaKrasnala();
                k[indeksKrasnal].rozpatrz(s[indeksSkarb].getRozmiar(), dec);
                if(dec) indeksSkarb++;
            }
            indeksKrasnal++;
            if(indeksKrasnal == k.length) indeksKrasnal = 0;
        }
        return;
    }

    public static void main(String[] args) {
        System.out.println("Start");
        Main o = new Main();
        Krasnal krasnale[] = o.generujTablicęKrasnali(5, 100);
        Skarb skarby[] = o.generujTablicęSkrabów(10, 100);
        for(Krasnal a : krasnale) {
            System.out.println(a);
        }
        for(Skarb a : skarby) {
            System.out.println(a);
        }
        o.Rozegraj(skarby, krasnale);
        for(Krasnal a : krasnale) {
            System.out.println(a);
        }
        System.out.println("Koniec");
    }
}