import java.util.Random;

public class Osobistosc {
    public static boolean[][] twórzZnajomości(int liczbaOsób, int ktoOsobistość) {
        boolean[][] znajomości = new boolean[liczbaOsób][liczbaOsób];
        Random nowaWartość = new Random();
        for(int i = 0; i < liczbaOsób; i++) {
            for(int j = 0; j < liczbaOsób; j++) {
                znajomości[i][j] = nowaWartość.nextBoolean();
            }
        }
        if(ktoOsobistość != -1) {
            for(int i = 0; i < liczbaOsób; i++) {
                znajomości[ktoOsobistość][i] = false;
                znajomości[i][ktoOsobistość] = true;
            }
        }
        return znajomości;
    }

    public static int osobistość1(boolean[][] znajomości) {
        int liczbaOsób = znajomości[0].length;
        boolean[] kandydaci = new boolean[liczbaOsób];
        for(int i = 0; i < liczbaOsób; i++) kandydaci[i] = true;
        for(int i = 0; i < liczbaOsób; i++) {
            for(int j = 0; j < liczbaOsób; j++) {
                if(i != j) {
                    if(znajomości[i][j]) kandydaci[i] = false;
                    else kandydaci[j] = false;
                }
            }
        }
        for(int i = 0; i < liczbaOsób; i++) {
            if(kandydaci[i]) return i;
        }
        return -1;
    }

    public static int osobistość2(boolean[][] znajomości) {
        int liczbaOsób = znajomości[0].length, kandydat = 0;
        for(int i = 1; i < liczbaOsób; i++) {
            if(znajomości[kandydat][i]) kandydat = i;
        }

        for(int i = 0; i < liczbaOsób; i++) {
            if(i != kandydat) {
                if(znajomości[kandydat][i]) return -1;
                if(!znajomości[i][kandydat]) return -1;
            }
        }
        return kandydat;   
    }

    public static void main(String[] args) {
        boolean[][] znaj = twórzZnajomości(10, -1);
        boolean[][] znaj2 = twórzZnajomości(10, 8);
        System.out.println(osobistość1(znaj));
        System.out.println(osobistość2(znaj));
        System.out.println(osobistość1(znaj2));
        System.out.println(osobistość2(znaj2));
        return;
    }
}
