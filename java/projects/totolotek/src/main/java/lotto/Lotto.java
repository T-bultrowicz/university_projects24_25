package lotto;

public interface Lotto {

    /* 
    * By później łatwo w projekcie móc zmieniać wartości,
    * ewentualnie zezwala na szybkie dodanie hierarchii podklas
    * kuponów, blankietów itd., dostosowanych do innych loterii.
    */
    static int TYPOWANYCH_LICZB = 6;
    static int ILOŚĆ_LICZB = 49;
    static int ILOŚĆ_ZAKŁADÓW = 10;
    static int ILOŚĆ_TYPÓW = 8; // bardziej liczba Typowań (na Blankiet)
    static int CENA_ZAKŁADU = 300; // groszy
    static int NAJM_NAGRODA = 2400;
    static int ILOŚĆ_NAGRÓD = 4;
    static int[] ILOŚĆ_TRAFIEŃ = new int[]{3, 4, 5, 6}; // konieczna do nagrody
    // po ilu losowaniach Kolektury usuwają dane o Kuponach, co uniemożliwia
    // odbiór nagrody.
    static int PRZEDAWNIENIE = 30;
}
