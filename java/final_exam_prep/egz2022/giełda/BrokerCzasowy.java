package giełda;

public class BrokerCzasowy extends Broker {

    // techniczne
    public BrokerCzasowy(Giełda giełda, int pobór, Strategia strategia) {
        super(giełda, pobór, strategia);
    }
    public BrokerCzasowy(int pobór, Strategia strategia) {
        super(pobór, strategia);
    }

    // metody
    
    @Override
    public boolean filter(Zasób z, Realizacja r) {
        return true;
    }

    @Override
    public void obsługaSprzedażyKlienta(Realizacja r) {
        for(Inwestycja i : r.inwestycje())
            if(strategia.czySprzedać(i, giełda, programy))
                sprzedajInwestycję(i, r);
    }

    @Override
    public void zakończenie(Realizacja r) {
        for(Inwestycja i : r.inwestycje())
            sprzedajInwestycję(i, r);
        r.zadanie().klient().zmianaFundusz(r.fundusz());
        realizacje.remove(r);
    }
}
