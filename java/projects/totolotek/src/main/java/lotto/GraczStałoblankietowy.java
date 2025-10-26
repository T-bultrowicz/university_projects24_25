package lotto;
import java.util.Collection;

import wyjątki.NullWartość;

public class GraczStałoblankietowy extends GraczStały {
    
    // dane
    private final Blankiet swójBlankiet;

    // techniczne
    public GraczStałoblankietowy(String imię, String nazwisko, String PESEL, 
            long stanKonta, CentralaTotolotka centrala, Collection<Kolektura> 
                    ulubione, int coIleLosowań, Blankiet swójBlankiet) {
        super(imię, nazwisko, PESEL, stanKonta, centrala, 
                                    ulubione, coIleLosowań);
        if (swójBlankiet == null) {
            throw new NullWartość("GraczStałoblankietowy.konstruktor()");
        }
        this.swójBlankiet = swójBlankiet;
    }

    // Zdegenrowany konstruktor, losuje wartości nie podane, tak jak zostało,
    // opisane w GraczStały oraz dolosowuje blankiet.
    public GraczStałoblankietowy(String imię, String nazwisko, String PESEL, 
            long stanKonta, CentralaTotolotka centrala) {
        super(imię, nazwisko, PESEL, stanKonta, centrala);
        this.swójBlankiet = MaszynaLosująca.losowyBlankiet();
    }

    @Override
    public String toString() {
       StringBuilder sb = new StringBuilder();
        sb.append("Gracz stałoblankietowy - korzysta z blankietu:\n");
        sb.append(swójBlankiet).append("\n"); 
        sb.append("co ").append(coIleLosowań).append(" losowań\n");
        sb.append("Ulubione kolektury: ");
        for (Kolektura k : ulubione) {
            sb.append(k.nrKolektury()).append(" ");
        }
        sb.append("\n").append(super.toString());
        return sb.toString();
    }

    // metody
    @Override
    protected Blankiet twórzBlankiet() {
        return swójBlankiet;
    }

    public Blankiet swójBlankiet(){
        return swójBlankiet;
    }
}
