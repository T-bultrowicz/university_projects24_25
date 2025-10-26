package wybory;

import java.util.Arrays;
import niezmiennik.NiezmiennikException;

public class KomisjaWyborcza {

    public class Przelicznik {

        public final Komitet komitet;
        public final int wartość;

        public Przelicznik(Komitet komitet, int wartość) throws NullPointerException{
            this.komitet = komitet;
            this.wartość = wartość;
        }
    }

    private class Ciąg {

        public Przelicznik[] ciąg;

        public Ciąg(int ilośćMandatów, Komitet komitet) {
            ciąg = new Przelicznik[ilośćMandatów];
            for(int i = 0; i < ilośćMandatów; i++) {
                ciąg[i] = new Przelicznik(komitet, komitet.ilośćGłosów / (i + 1));
            }
        }

        public void scalCiąg(Ciąg a) {
            int i = 0, j = 0;
            Przelicznik[] nowyCiąg = new Przelicznik[a.ciąg.length + this.ciąg.length];
            while(i < a.ciąg.length && j < this.ciąg.length) {
                if(a.ciąg[i].wartość < this.ciąg[j].wartość) {
                    nowyCiąg[i + j] = this.ciąg[j];
                    j++;
                } else {
                    nowyCiąg[i + j] = a.ciąg[i];
                    i++;
                }
            }
            while(i < a.ciąg.length) {
                nowyCiąg[i + j] = a.ciąg[i];
                i++;
            }
            while(j < this.ciąg.length) {
                nowyCiąg[i + j] = this.ciąg[j];
                j++;
            }
            this.ciąg = nowyCiąg;
        }
    }

    private Komitet[] przytnij(Komitet[] komitety, float prógProcentowy) {
        int suma = 0, wybrano = 0;
        for(Komitet a : komitety) {
            suma += a.ilośćGłosów;
        }
        for(Komitet a : komitety) {
            if((float) a.ilośćGłosów / suma >= prógProcentowy)
                wybrano++;
        }
        Komitet[] newKomitet = new Komitet[wybrano];
        int i = 0;
        for(Komitet a : komitety) {
            if((float) a.ilośćGłosów / suma >= prógProcentowy)
                newKomitet[i++] = a;
        }
        return newKomitet;
    }

    public static void przeprowadźWybory(Komitet[] komitety, int ilośćMandatów, float prógProcentowy) throws NullPointerException, NiezmiennikException{
        KomisjaWyborcza wybor  = new KomisjaWyborcza();
        komitety = wybor.przytnij(komitety, prógProcentowy);
        Arrays.sort(komitety);



        Ciąg wartości = wybor.new Ciąg(ilośćMandatów, komitety[0]);
        for(int i = 1; i < komitety.length; i++) {
            wartości.scalCiąg(wybor.new Ciąg(ilośćMandatów, komitety[1]));
        }
        for(int i = 0; i < ilośćMandatów; i++) {
            wartości.ciąg[i].komitet.dodajKandydata();
        }
        for(Komitet a : komitety) {
            a.stworzKandydatowWybranych();
        }
    }

    public static void ogłośWyniki(Komitet[] komitety) {
        for(Komitet a : komitety) {
            if(a.getKandydaciWygrani() != null) {
                System.out.println("Z komitetu dostali się: \n");
                for(Kandydat b : a.getKandydaciWygrani()) {
                    System.out.println("Kandydat " + b + " dostał się!!!\n");
                }
            }
        }
    }
}