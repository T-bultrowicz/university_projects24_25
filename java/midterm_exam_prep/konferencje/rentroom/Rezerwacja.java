package rentroom;

import narzędzia.*;

public class Rezerwacja {
    
    //dane
    public final Pokój pokój;
    public final Interval interval;
    private Status status;

    //techniczne
    public Rezerwacja(Pokój pokój, Interval interval) throws NullPointerException {
        if(pokój == null || interval == null) throw new NullPointerException();
        this.pokój = pokój;
        this.interval = interval;
        this.status = Status.PENDING;
    }

    @Override
    public String toString() {
        String res = "REZERWACJA: pokój - " + pokój + " w czasie " + interval;
        switch(status) {
            case PENDING:
                return res + " -- oczekuje na potwierdzenie --\n";
            case CONFIRMED:
                return res + " -- potwierdzona --\n";
            case CANCELLED: default:
                return res + " -- anulowana --\n";
        }
    }

    //metody
    public void Odwołaj() {
        this.status = Status.CANCELLED;
        pokój.zwolnij(this);
    }

    public void Potwierdź() {
        this.status = Status.CONFIRMED;
    }
}
