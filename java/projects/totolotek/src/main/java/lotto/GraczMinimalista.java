package lotto;
import wyjątki.BrakFunduszy;
import wyjątki.NullWartość;

public class GraczMinimalista extends Gracz {

    // dane
    private Kolektura ulubiona;

    // techniczne
    public GraczMinimalista(String imię, String nazwisko, String PESEL, 
            long stanKonta, Kolektura ulubiona, CentralaTotolotka centrala) {
        super(imię, nazwisko, PESEL, stanKonta, centrala);
        if(ulubiona == null)
                throw new NullWartość("GraczMinimalista.konstruktor()");
        this.ulubiona = ulubiona;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Gracz minimalista - \nUlubiona kolektura: ");
        sb.append(ulubiona.nrKolektury()).append("\n");
        sb.append(super.toString());
        return sb.toString();
    }

    // metody
    
    @Override
    public void zakupLosowania() {
        try {
            Kupon k = ulubiona.zakupKupon(1, 1, this);
            kupony.put(k.id(), k);
        } catch (BrakFunduszy e) {
            System.out.println(e);
        }
    }

    @Override
    public void odbierzNagrodę(String id) {
        odbierzNagrodę(id, ulubiona);
    }    
}
