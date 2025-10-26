package kalendarz;

public class Data {
    //dane
    private int dzień;
    private int miesiąc;
    private int rok;

    //techniczne

    /* Niezmienniki 
     * sprawdza poprawny zakres daty, czyli warunki:
     *
     * 1) miesiąc w zakresie 1-12
     * 
     * 2) rok w zakresie 1-9999
     * 
     * 3) dzień mniejszy równy od ostatniego dnia miesiąca, uwzględniając
     * przestępność roku dla lutego
     * 
     * 4) rok uznajemy za przestępny gdy jest podzielny przez 4 
    */

    //sprawdza niezmienniki oraz zwraca ostatni dzień miesiąca
    private class Funkcjonalne {
        int ostatni_dzień(int miesiąc, int rok) {
            switch (miesiąc) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    return 31;
                case 4: case 6: case 9: case 11:
                    return 30;
                default:
                    return (rok % 4 == 0) ? 29 : 28; 
            }
        }
        boolean niezmiennik(int dzień, int miesiąc, int rok) {
            if(miesiąc < 1 || miesiąc > 12) return false;
            if(rok < 1 || rok > 9999) return false;
            if(dzień < 1 || dzień > ostatni_dzień(miesiąc, rok)) return false;
            return true;
        }
    }

    //konstruktory
    public Data(int dzień, int miesiąc, int rok) {
        assert new Funkcjonalne().niezmiennik(dzień, miesiąc, rok) : "Zły format daty!\n";
        this.dzień = dzień;
        this.miesiąc = miesiąc;
        this.rok = rok;
        return;
    }

    public Data() {
        this.dzień = 1;
        this.miesiąc = 1;
        this.rok = 1900;
        return;
    }

    //wyczytanie
    @Override
    public String toString() {
        return "Data to: dzień - " + this.dzień + " miesiąc - " + this.miesiąc + " rok - " + this.rok;
    }

    //metody dla użytkownika
    public void następnyDzień() {
        assert new Funkcjonalne().niezmiennik(this.dzień, this.miesiąc, this.rok) : "Zły format daty!\n";
        if(this.dzień == 31 && this.miesiąc == 12) {
            this.dzień = 1;
            this.miesiąc = 1;
            this.rok += 1;
            return;
        }
        if(this.dzień == new Funkcjonalne().ostatni_dzień(this.miesiąc, this.rok)) {
            this.dzień = 1;
            this.miesiąc += 1;
            return;
        }
        this.dzień += 1;
        assert new Funkcjonalne().niezmiennik(this.dzień, this.miesiąc, this.rok) : "Złe działanie funkcji";
        return;
    }

    public void dataZa(int dni) {
        while(dni > 0) {
            int dni_do_pelnego = new Funkcjonalne().ostatni_dzień(this.miesiąc, this.rok) - this.dzień;
            if(dni >= dni_do_pelnego + 1) {
                dni -= dni_do_pelnego + 1;
                if(this.miesiąc == 12) {
                    this.rok += 1;
                    this.miesiąc = 1;
                } else {
                    this.miesiąc += 1;
                }
                this.dzień = 1;
            } else {
                this.dzień += dni;
                dni = 0;
            }
        }        
    }

    public void poprzedniDzień() {
        assert new Funkcjonalne().niezmiennik(this.dzień, this.miesiąc, this.rok) : "Zły format daty!\n";
        if(this.dzień == 1 && this.miesiąc == 1) {
            this.dzień = 31;
            this.miesiąc = 12;
            this.rok -= 1;
            return;
        }
        if(this.dzień == 1) {
            this.dzień = new Funkcjonalne().ostatni_dzień(this.miesiąc - 1, rok);
            this.miesiąc -= 1;
            return;
        }
        this.dzień -= 1;
        assert new Funkcjonalne().niezmiennik(this.dzień, this.miesiąc, this.rok) : "Złe działanie funkcji";  
        return;
    }

    public void dataPrzed(int dni) {
        assert new Funkcjonalne().niezmiennik(this.dzień, this.miesiąc, this.rok) : "Zły format daty!\n";
        assert dni > 0: "Zła ilość dni\n";
        while(dni > 0) {
            if(dni >= this.dzień) {
                dni -= this.dzień;
                if(this.miesiąc == 1) {
                    this.rok -= 1;
                    this.miesiąc = 12;
                } else {
                    this.miesiąc -= 1;
                }
                this.dzień = new Funkcjonalne().ostatni_dzień(this.miesiąc, this.rok);
            } else {
                this.dzień -= dni;
                dni = 0;
            }
        }
        assert new Funkcjonalne().niezmiennik(this.dzień, this.miesiąc, this.rok) : "Złe działanie funkcji"; 
    }

    public boolean równa(Data data) {
        return this.dzień == data.dzień && this.miesiąc == data.miesiąc && this.rok == data.rok;
    }

    //zwraca true gdy obiekt data jest wcześniejszy od daty w parametrze funkcji
    public boolean wcześniejsza(Data data) {
        if(data.rok < this.rok) return false;
        if(data.rok > this.rok) return true;
        if(data.miesiąc < this.miesiąc) return false;
        if(data.miesiąc > this.miesiąc) return true;
        return data.dzień > this.dzień;
    }

    //analogicznie ale późniejszy
    public boolean późniejsza(Data data) {
        return !wcześniejsza(data) && !równa(data);
    }
}
