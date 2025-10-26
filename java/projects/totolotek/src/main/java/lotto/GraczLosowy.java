package lotto;
import wyjątki.BrakFunduszy;
import wyjątki.NieMaKuponu;

public class GraczLosowy extends Gracz {

    // techniczne
    public GraczLosowy(String imię, String nazwisko, String PESEL, 
                                            CentralaTotolotka centrala) {
        super(imię, nazwisko, PESEL, 0, centrala);
        pobierzFundusze(MaszynaLosująca.przedział(0, 99999999));
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Gracz losowy - \n");
        sb.append(super.toString());
        return sb.toString();
    }

    // metody
    @Override
    public void zakupLosowania() {
        int ileKupuje = MaszynaLosująca.przedział(1, 100);
        int nrKolektury = MaszynaLosująca.przedział
                                                (1, centrala.ilośćKolektur());
        Kolektura kolektura = centrala.znajdźKolekturę(nrKolektury);
        for(int i = 0; i < ileKupuje; i++) {
            try {
                Kupon k = kolektura.zakupKupon(MaszynaLosująca.przedział
        (1, ILOŚĆ_ZAKŁADÓW), MaszynaLosująca.przedział(1, ILOŚĆ_TYPÓW), this);
                kupony.put(k.id(), k);
            } catch (BrakFunduszy e) {
                System.out.println(e);
                break;
            }
        }
    }

    @Override
    public void odbierzNagrodę(String id) {
        if(!kupony.containsKey(id))
            throw new NieMaKuponu("GraczLosowy.odbierzNagrodę()");
        int nrKolektury = kupony.get(id).nrKolektury();
        odbierzNagrodę(id, centrala.znajdźKolekturę(nrKolektury));
    }
    
}
