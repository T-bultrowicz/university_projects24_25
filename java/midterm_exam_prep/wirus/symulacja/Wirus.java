package symulacja;
import java.util.Random;

import wyjątki.*;

public abstract class Wirus {
    
    //dane
    private final int mutagenność;
    protected char[] DNAWirusa;
    protected Random rng;

    //techniczne
    //NIEZMIENNIKI:
    /* 1. mutagenność jest liczbą nieujemną
     * 2. DNAWirusa składa się tylko ze znaków ACGT
     */

    protected class Niezmiennik {
        static void Poprawność(int a, char[] b) throws NiepoprawneDaneException {
            if(a < 0) throw new NiepoprawneDaneException("Ujemna mutagenność");
            if(b == null) throw new NiepoprawneDaneException("Null String");
            for(int i = 0; i < b.length; i++) {
                if(b[i] != 'A' && b[i] != 'C' && 
                    b[i] != 'G' && b[i] != 'T') {
                        throw new NiepoprawneDaneException("Zły znak w DNA");
                    } 
            }
        }
    }

    public Wirus(int mutagenność, char[] DNAWirusa) throws NiepoprawneDaneException {
        Niezmiennik.Poprawność(mutagenność, DNAWirusa);
        this.mutagenność = mutagenność;
        this.DNAWirusa = DNAWirusa;
        this.rng = new Random();
    }

    @Override
    public String toString() {
        return "Wirus typu - " + this.getClass().getName() + " o kodzie: " + String.copyValueOf(DNAWirusa);
    }

    public String getDNAWirusa() {
        return String.copyValueOf(DNAWirusa);
    }

    //metody
    abstract void mutuj();
    public void mutujPrzezMiesiąc() {
        for(int i = 0; i < mutagenność; i++) {
            mutuj();
        }
    }
    public void mutujPrzezXMiesięcy(int ileMiesięcy) throws NiepoprawneDaneException {
        if(ileMiesięcy < 0) throw new NiepoprawneDaneException("Ujemna ilość miesięcy!");
        for(int i = 0; i < ileMiesięcy; i++) {
            mutujPrzezMiesiąc();
        }
    }
}
