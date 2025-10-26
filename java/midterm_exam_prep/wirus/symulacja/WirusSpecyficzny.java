package symulacja;

import wyjątki.*;

public class WirusSpecyficzny extends Wirus{
    
    //dane
    private boolean[] zmiany;

    //techniczne
    /*  NIEZMIENNIKI:
     * 1. Wszystkie jak dla Wirus
     * 2. Tabela zmiany ma długość 4 i min 2 wartości true
     */

    private int suma(boolean[] a) {
        int res = 0;
        for(int i = 0; i < 4; i++) {
            if(a[i]) res++;
        }
        return res;
    }

    public WirusSpecyficzny(int mutagenność, char[] DNAWirusa) throws NiepoprawneDaneException {
        super(mutagenność, DNAWirusa);
        zmiany = new boolean[4];
        for(int i = 0; i < 4; i++) zmiany[i] = true;
    }

    public void changeZmiany(boolean[] zmiany) throws NiepoprawneDaneException {
        if(zmiany == null) throw new NiepoprawneDaneException("Null boolean[]");
        if(zmiany.length != 4) throw new NiepoprawneDaneException("Zly rozmiar tablicy zmiany");
        if(suma(zmiany) < 2) throw new NiepoprawneDaneException("Za malo mozliwosci mutowania w tab zmiany");
        this.zmiany = zmiany;   
    }

    public WirusSpecyficzny(int mutagenność, char[] DNAWirusa, boolean[] zmiany) throws NiepoprawneDaneException {
        super(mutagenność, DNAWirusa);
        changeZmiany(zmiany);
    }

    //metody
    @Override
    void mutuj() {
        int pozycja = rng.nextInt(DNAWirusa.length);
        int na_co = rng.nextInt(suma(zmiany)), i = 0;
        while(na_co > 0) {
            if(zmiany[i++]) na_co--;
        }
        switch (i) {
            case 0:
                DNAWirusa[pozycja] = 'A';
                break;
            case 1:
                DNAWirusa[pozycja] = 'C';
                break;
            case 2:
                DNAWirusa[pozycja] = 'G';
                break;
            case 3:
                DNAWirusa[pozycja] = 'T';
                break;
            default:
                break;
        }
        return;
    }
}
