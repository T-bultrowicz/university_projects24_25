package narzędzia;
import wyjątki.*;

public class Data {
    
    //dane
    private int godzina, dzień, miesiąc, rok;

    //techniczne
    private int dniWMiesiącu() {
        switch (miesiąc) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return 31;
            case 4: case 6: case 9: case 11:
                return 30;
            case 2: default:
                return (rok % 4 == 0) ? 29 : 28;
        }
    }

    public Data(int godzina, int dzień, int miesiąc, int rok) throws NiezmiennikException {
        if(rok < 1000 || rok > 9999) throw new NiezmiennikException("Rok ma być 4cyfrowy!");
        if(miesiąc < 1 || miesiąc > 12) throw new NiezmiennikException("Nie istnieje taki miesiąc");
        if(godzina < 0 || godzina > 23) throw new NiezmiennikException("Zła godzina!");
        this.rok = rok;
        this.miesiąc = miesiąc;
        if(dzień < 1 || dzień > dniWMiesiącu()) throw new NiezmiennikException("Zły dzień miesiąca");
        this.dzień = dzień;
        this.godzina = godzina;
    }

    public Data() {
        this.dzień = 1;
        this.miesiąc = 1;
        this.rok = 2021;
        this.godzina = 0;
    }

    @Override
    public String toString() {
        return this.dzień + "." + this.miesiąc + "." + this.rok + "   " + this.godzina + ":00\n";
    }

    //metody
    public void next() {
        if(miesiąc == 12 && dzień == 31) {
            this.dzień = 1;
            this.miesiąc = 1;
            this.rok += 1;
        } else if(dzień == dniWMiesiącu()) {
            this.dzień = 1;
            this.miesiąc += 1;
        } else {
            this.dzień += 1;
        }
    }

    public boolean równa(Data druga) {
        return (this.dzień == druga.dzień && this.miesiąc == druga.miesiąc
                                        && this.rok == druga.rok);
    }

    public boolean wcześniejszaOd(Data druga) {
        if(druga.rok > this.rok) return true;
        if(druga.rok < this.rok) return false;
        if(druga.miesiąc > this.miesiąc) return true;
        if(druga.miesiąc < this.miesiąc) return false;
        if(druga.dzień > this.dzień) return true;
        if(druga.dzień < this.dzień) return false;
        if(druga.godzina > this.dzień) return true;
        return false;
    }

    static public Data maxData() {
        Data a = new Data();
        a.dzień = 31;
        a.miesiąc = 12;
        a.rok = 9999;
        a.godzina = 23;
        return a;
    }
}
