package symulacja;
import wyjątki.*;

public class WirusDziwny extends Wirus{
    
    //dane
    //techniczne
    /*  NIEZMIENNIKI:
     * 1. Wszystkie jak dla Wirus
     * 2. Długości min. 2 - aby miejsca mogły się zmieniać
     */
    public WirusDziwny(int mutagenność, char[] DNAWirusa) throws NiepoprawneDaneException {
        super(mutagenność, DNAWirusa);
        if(DNAWirusa.length < 2) throw new NiepoprawneDaneException("Za krótka długość Stringa");
    }

    @Override
    void mutuj() {
        int first_pos = rng.nextInt(DNAWirusa.length), second_pos;
        do {
            second_pos = rng.nextInt(DNAWirusa.length);
        } while(second_pos == first_pos);
        char a = DNAWirusa[first_pos];
        DNAWirusa[first_pos] = DNAWirusa[second_pos];
        DNAWirusa[second_pos] = a;
        return;
    }
}
