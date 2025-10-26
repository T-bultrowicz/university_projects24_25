package lotto;

import wyjątki.SpozaZasięgu;

public class Blankiet implements Lotto {
    
    // dane
    private boolean[][] polaTypowane;
    private boolean[] anulowane;
    private boolean[] ilośćZakładów;

    // techniczne
    public Blankiet() {
        this.polaTypowane = new boolean[ILOŚĆ_TYPÓW][ILOŚĆ_LICZB];
        this.anulowane = new boolean[ILOŚĆ_TYPÓW];
        this.ilośćZakładów = new boolean[ILOŚĆ_ZAKŁADÓW];
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < ILOŚĆ_TYPÓW; i++) {
            sb.append(i + 1).append("\n");
            for(int j = 0; j < ILOŚĆ_LICZB; j++) {
                if(polaTypowane[i][j]) {
                    sb.append("[ -- ] ");
                } else if(j < 9) {
                    sb.append("[  ").append(j + 1).append(" ] ");
                } else {
                    sb.append("[ ").append(j + 1).append(" ] ");
                }
                if(j % 10 == 9) {
                    sb.append("\n");
                }
            }
            sb.append("\n[ ").append(anulowane[i] ? "--" : "  ");
            sb.append(" ] anuluj\n");
        }
        sb.append("Ilość losowań: ");
        for(int i = 0; i < 10; i++) {
            if(ilośćZakładów[i]) {
                sb.append("[ -- ] ");
            } else if(i < 9) {
                sb.append("[  ").append(i + 1).append(" ] ");
            } else {
                sb.append("[ ").append(i + 1).append(" ] ");
            }
        }
        return sb.toString();
    }

    // metody
    public boolean[][] polaTypowane() {
        return this.polaTypowane;
    }

    public boolean[] ilośćZakładów() {
        return this.ilośćZakładów;
    }

    public boolean[] anulowane() {
        return this.anulowane;
    }

    public void zaznaczTyp(int typ, int liczba) throws SpozaZasięgu {
        if (typ < 1 || typ > ILOŚĆ_TYPÓW) {
            throw new SpozaZasięgu(ILOŚĆ_TYPÓW, typ, 
                        " Blankiet.zaznaczTyp()");
        } else if (liczba < 1 || liczba > ILOŚĆ_LICZB) {
            throw new SpozaZasięgu(ILOŚĆ_LICZB, liczba, 
                        " Blankiet.zaznaczTyp()");
        }
        this.polaTypowane[typ - 1][liczba - 1] = true;
    }

    public void zaznaczIlośćZakładów(int zakład) {
        if(zakład < 1 || zakład > ILOŚĆ_ZAKŁADÓW) {
            throw new SpozaZasięgu(ILOŚĆ_ZAKŁADÓW, zakład,
                        " Blankiet.zaznaczIlośćZakładów()");
        }
        this.ilośćZakładów[zakład - 1] = true;
    }

    public void zaznaczAnuluj(int typ) {
        if (typ < 1 || typ > ILOŚĆ_TYPÓW) {
            throw new SpozaZasięgu(ILOŚĆ_TYPÓW, typ, 
                        " Blankiet.zaznaczAnuluj()");
        }
        this.anulowane[typ - 1] = true;
    }
}
