package wyjątki;

public class ZłaIlośćArgumentów extends ZłeArgumentyFunkcji {

    //techniczne
    public ZłaIlośćArgumentów(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Zła ilość argumentów w : " + getMessage();
    }   
}
