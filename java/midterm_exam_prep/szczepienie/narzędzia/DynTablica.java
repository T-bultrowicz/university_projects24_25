package narzędzia;

@SuppressWarnings("unchecked")
public class DynTablica<T> {
    
    //dane
    private T[] zawartość;
    private int uzywana;

    //techniczne
    public DynTablica() {
        this.zawartość = (T[]) new Object[1];
        this.uzywana = 0;
    }

    private void zarządźRozmiarem() {
        if(uzywana < zawartość.length) return;
        T[] nowaZawartość = (T[]) new Object[zawartość.length * 2];
        System.arraycopy(zawartość, 0, nowaZawartość, 0, zawartość.length);
        zawartość = nowaZawartość;
    }

    public void dodajElement(T elem) {
        zarządźRozmiarem();
        zawartość[uzywana++] = elem;
    }

    public void wyczytajElementy() {
        for(T t : zawartość)
            System.out.println(t.toString());
    }
}
