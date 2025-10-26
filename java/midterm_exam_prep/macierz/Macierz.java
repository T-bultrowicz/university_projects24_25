import java.util.Scanner;

public class Macierz {

    public static double[][] mnożenieMacierzy(double[][] macierz1, double[][] macierz2) {
        int rozmiar1 = macierz1.length, rozmiar2 = macierz2.length, rozmiarWspolny = macierz1[0].length;
        double[][] res = new double[rozmiar1][rozmiar2];
        for(int i = 0; i < rozmiar1; i++) {
            for(int j = 0; j < rozmiar2; j++) {
                res[i][j] = 0;
                for(int k = 0; k < rozmiarWspolny; k++) {
                    res[i][j] += macierz1[i][k] * macierz2[k][j];
                }
            }
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner wejście = new Scanner(System.in);
        int rozmiar1 = wejście.nextInt(), rozmiar2 = wejście.nextInt(), rozmiarWspolny = wejście.nextInt();
        double[][] macierz1 = new double[rozmiar1][rozmiarWspolny], macierz2 = new double[rozmiarWspolny][rozmiar2];
        for(int i = 0; i < rozmiar1; i++) {
            for(int j = 0; j < rozmiarWspolny; j++) {
                macierz1[i][j] = wejście.nextDouble();
            }
        }
        for(int i = 0; i < rozmiarWspolny; i++) {
            for(int j = 0; j < rozmiar2; j++) {
                macierz2[i][j] = wejście.nextDouble();
            }
        }
        long dostańCzas = System.currentTimeMillis();
        double[][] macierzWyjściowa = mnożenieMacierzy(macierz1, macierz2);
        long dostańCzas2 = System.currentTimeMillis();

        for(int i = 0; i < rozmiar1; i++) {
            for(int j = 0; j < rozmiar2; j++) {
                System.out.print(macierzWyjściowa[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println("Czas wykonania to " + (dostańCzas2 - dostańCzas) + " milisekund");
        wejście.close();
    }
}