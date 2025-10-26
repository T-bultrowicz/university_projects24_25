package skarb;

public class Skarb {
    
    //dane
    static private int ilSkarbow = 0;
    static private long sumaSkarbow = 0;
    private int rozmiarSkarbu;

    //techniczne
    public Skarb(int rozmiarSkarbu) {
        assert rozmiarSkarbu > 0;
        this.rozmiarSkarbu = rozmiarSkarbu;
    }

    @Override
    public String toString() {
        return "Skarb rozmiaru " + rozmiarSkarbu;
    }

    public int getRozmiar() {
        ilSkarbow++;
        sumaSkarbow += rozmiarSkarbu;
        return rozmiarSkarbu;
    }

    //metody
    static public float zwróćŚrednia() {
        if(ilSkarbow == 0) return 0;
        return (float) sumaSkarbow / ilSkarbow;
    }
}
