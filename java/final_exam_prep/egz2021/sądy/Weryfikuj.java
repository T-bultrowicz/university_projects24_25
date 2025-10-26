package sądy;
import wyjątki.WartośćNull;
import wyjątki.ZłaWartość;

public abstract class Weryfikuj {
    public static void nullVal(String mes, Object... o) {
        for(Object obj : o) {
            if(obj == null)
                throw new WartośćNull(mes);
        }
    }

    public static void belowVal(String mes, Number... num) {
        for(Number n : num) {
            if(n.doubleValue() < 0.0)
                throw new ZłaWartość(num, ">= 0", mes);
        }
    }
}
