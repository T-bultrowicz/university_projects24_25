package giełda;

public class BrokerPreferencyjny extends Broker {

    // techniczne
    public BrokerPreferencyjny(Giełda giełda, int pobór, Strategia strategia) {
        super(giełda, pobór, strategia);
    }

    public BrokerPreferencyjny(int pobór, Strategia strategia) {
        super(pobór, strategia);
    }

    // metody
    private boolean pozaLimitem(long cena, long og, int pGóra, int pDół) {
        if(cena >= og + (og * pGóra))
            return true;
        if(cena <= og - (og * pDół))
            return true;
        return false;
    }
    

    @Override
    protected boolean filter(Zasób z, Realizacja r) {
        for(Kategoria a : r.zadanie().kategorie())
            if(z.kategoria() == a)
                return true;
        return false;
    }

    @Override
    protected void obsługaSprzedażyKlienta(Realizacja r) {
        for(Inwestycja i : r.inwestycje()) {
            if(pozaLimitem(giełda.cena(i.zasób()), i.cenaKupna(), 
            r.zadanie().minWzrost(), r.zadanie().maxSpadek())) {
                sprzedajInwestycję(i, r);
            } else if(strategia.czySprzedać(i, giełda, programy)) {
                sprzedajInwestycję(i, r);
            }
        }
    }

    @Override
    protected void zakończenie(Realizacja r) {
        r.zadanie().klient().zmianaFundusz(r.fundusz());
        r.zmianaFundusz(-r.fundusz());
        realizacje.remove(r);
    }
}