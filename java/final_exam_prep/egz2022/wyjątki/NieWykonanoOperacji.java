package wyjątki;

public class NieWykonanoOperacji extends RuntimeException{
    public NieWykonanoOperacji(String mes) {
        super("Nie można wykonać " + mes + 
                       " przez nieoczekiwane arg. wejściowe");
    }
}
