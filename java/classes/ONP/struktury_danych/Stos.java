package struktury_danych;

public class Stos {
    // Dane
    private int[] elty;
    //int elty[];
    private int wierzchołek; // indeks ostatniego elementu na stosie


    // Techniczne
    public Stos(int rozmiar) throws ZłyRozmiar {
        if (rozmiar <= 0)
            throw new ZłyRozmiar("Podano rozmiar = " + rozmiar);
        else{
            wierzchołek = -1;
            elty = new int[rozmiar];
        }
    }

    @Override
    public String toString() {  // niejasne co byśmy chcieli tu mieć (np. wypisanie całego stosu)
        StringBuilder sb = new StringBuilder();
        sb.append("Stos: ");
        for (int i = 0; i <= wierzchołek; i++) {
            sb.append(elty[i]);
            if (i < wierzchołek) {
                sb.append(", ");
            }
        }
        return sb.toString();
    }

    // Operacje
    public void wstaw(int elt) throws BrakMiejsca{
        if (wierzchołek == elty.length - 1)
            throw new BrakMiejsca("Przy wstawianiu " + elt +
                                  " na stosie o rozmiarze " + elty.length);
        else
            elty[++wierzchołek] = elt;
    }

    public void pobierz() throws PustyStos{
        if (wierzchołek == -1)
            throw new PustyStos("Nie można pobrać z pustego stosu ");
             // + this
        else
            wierzchołek--;
    }

    public int NaWierzchołku() throws PustyStos{
        if (wierzchołek == -1)
            throw new PustyStos("Nie można obejrzeć wierzchołka pustego stosu ");
            // + this

        return elty[wierzchołek];
    }

    public boolean czyPusty() {
        return wierzchołek == -1;
    }

    public void czyść(){
        wierzchołek = -1;
    }
}
