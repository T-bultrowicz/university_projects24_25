package szczepienia;
import narzędzia.*;
import wyjątki.BrakPasującegoException;
import wyjątki.NiezmiennikException;

import java.util.Arrays;

public class Województwo {
    
    //dane
    private PunktSzczepień[] punkty;

    //techniczne
    public Województwo(PunktSzczepień[] nowy) throws NullPointerException {
        if(nowy == null) throw new NullPointerException();
        for(PunktSzczepień a : nowy)
            if(a == null) throw new NullPointerException();
        
        punkty = nowy;
        Arrays.sort(punkty);
    }

    //metody
    private int binSearch(int war, boolean less) {
        int l = 0, r = punkty.length - 1, mid;
        while(l < r) {
            mid = less ? l + r + 1 : l + r;
            mid /= 2;
            if(less) {
                if(war > punkty[mid].adres.adres) {
                    r = mid - 1;
                } else {
                    l = mid;
                }
            } else {
                if(war < punkty[mid].adres.adres) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
        }
        if(l == 0 && less && punkty[0].adres.adres > war)
            l = -1;
        if(l == punkty.length - 1 && !less && punkty[l].adres.adres < war)
            l = punkty.length; 
        return l;
    }


    public PunktSzczepień znajdźNajlepszy(Pacjent pacjent) throws BrakPasującegoException, NiezmiennikException{
        int lewo = binSearch(pacjent.adres.adres - pacjent.mxDyst, false);
        int prawo = binSearch(pacjent.adres.adres + pacjent.mxDyst, true);
        if(lewo == -1 || prawo == punkty.length)
            throw new BrakPasującegoException();

        Data bestData = Data.maxData();
        int bestDyst = Integer.MAX_VALUE;
        PunktSzczepień bestPunktSzczepień = null;

        for(int i = lewo; i <= prawo; i++) {
            if(punkty[i].typ.nazwa != pacjent.typ.nazwa) continue;
            if(punkty[i].zwróćTermin().wcześniejszaOd(bestData)) {
                bestPunktSzczepień = punkty[i];
                bestData = punkty[i].zwróćTermin();
                bestDyst = punkty[i].adres.absVAL(pacjent.adres);
                continue;
            }
            if(punkty[i].zwróćTermin().równa(bestData)) {
                if(punkty[i].adres.absVAL(pacjent.adres) < bestDyst) {
                    bestPunktSzczepień = punkty[i];
                    bestData = punkty[i].zwróćTermin();
                    bestDyst = punkty[i].adres.absVAL(pacjent.adres);
                    continue;                    
                }
            }
        }
        if(bestPunktSzczepień == null) throw new BrakPasującegoException();
        return bestPunktSzczepień;
    } 
}
