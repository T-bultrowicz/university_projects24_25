package narzędzia;

import wyjątki.NiezmiennikException;

public class Interval {
    
    //dane
    public final Data wcześniejsza;
    public final Data późniejsza;

    //techniczne
    public Interval(Data wcześniejsza, Data późniejsza) throws NiezmiennikException, NullPointerException {
        if(!wcześniejsza.wcześniejszaOd(późniejsza))
            throw new NiezmiennikException("Pierwsza data musi być wcześniejsza!");
        this.wcześniejsza = wcześniejsza;
        this.późniejsza = późniejsza;
    }

    @Override
    public String toString() {
        return "Od: " + wcześniejsza + "   do:" + późniejsza + "\n";
    }

    //metody
    public boolean późniejszyOd(Interval drugi) {
        return drugi.późniejsza.wcześniejszaOd(this.wcześniejsza);
    }
    
    public boolean wcześniejszyOd(Interval drugi) {
        return this.późniejsza.wcześniejszaOd(drugi.wcześniejsza);
    }

    public boolean overLap(Interval drugi) {
        return (this.wcześniejszyOd(drugi) || this.późniejszyOd(drugi));
    }

}
