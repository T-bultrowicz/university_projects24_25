package szczepienia;

import wyjątki.BrakPasującegoException;
import wyjątki.NiezmiennikException;

public class CentralnaPoradaSzczepień {
    
    static public PunktSzczepień znajdźNajlepszy(Pacjent a) throws NiezmiennikException, BrakPasującegoException{
        return a.województwo.znajdźNajlepszy(a);
    } 
}
