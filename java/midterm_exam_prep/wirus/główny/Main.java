import symulacja.*;
import wyjątki.*;

public class Main {

    private class Szczepionka {
        //dane
        final char[] wzorzecDNA;
        //techniczne
        private void wzorzecChecker(char[] wzorzec) throws NiepoprawneDaneException{
            for(int i = 0; i < wzorzec.length; i++) {
                if(wzorzec[i] != 'A' && wzorzec[i] != 'C' && 
                    wzorzec[i] != 'G' && wzorzec[i] != 'T') {
                        throw new NiepoprawneDaneException("Zły znak w DNA");
                    } 
            }
        }

        public Szczepionka(char[] wzorzecDNA) throws NiepoprawneDaneException{
            if(wzorzecDNA == null) throw new NiepoprawneDaneException("null wzorzec");
            wzorzecChecker(wzorzecDNA);
            this.wzorzecDNA = wzorzecDNA;
        }

        //metody
        public boolean czyZwalcza(Wirus wirus) {
            return wirus.getDNAWirusa().contains(String.copyValueOf(wzorzecDNA));
        }
    }

    void testuj() {
        try {
            Szczepionka c = new Szczepionka(new char[]{'A', 'C', 'G', 'T', 'A', 'A', 'A'});
            Wirus[] wirusy = new Wirus[10];
            for(int i = 0; i < 10; i++) {
                wirusy[i] = new WirusDziwny(i, new char[]{'A', 'C', 'G', 'A', 'A', 'A', 'T'});
            }
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 10; j++) {
                    wirusy[j].mutujPrzezMiesiąc();
                    String info = c.czyZwalcza(wirusy[j]) ? "pokonuje" : "nie pokonuje";
                    System.out.println("Szczepionka " + info + " wirusa:\n" + wirusy[j] + "\n");
                }
            }
        } catch (NiepoprawneDaneException nde) {
            System.out.println(nde);
        }
    }

    void testuj2() {
        try {
            Wirus wir = new WirusDziwny(10, null);
            wir.mutujPrzezMiesiąc();
        } catch(NiepoprawneDaneException nde) {
            System.out.println(nde);
        }
    }

    public static void main(String[] args) {
        System.out.println("Start!");
        Main o = new Main();
        o.testuj();
        o.testuj2();
        System.out.println("Koniec!");
    }
}
