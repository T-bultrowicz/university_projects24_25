package DynamicznaTablica;

@SuppressWarnings("unchecked")
public class DynamicznaTablica <T> {

    //dane
    int uzywaneMiejsce;
    T[] elementy;

    //techniczne
    public DynamicznaTablica() {
        this.uzywaneMiejsce = 0;
        elementy = (T[]) new Object[1];
    }

    //metody
    // Dodanie elementu
    public void add(T element) {
        if (uzywaneMiejsce == elementy.length) {
            zwiekszTablice(); // jeśli brak miejsca, powiększamy tablicę
        }
        elementy[uzywaneMiejsce++] = element;
    }

    // Metoda powiększająca tablicę
    private void zwiekszTablice() {
        T[] newelementy = (T[]) new Object[elementy.length * 2];
        System.arraycopy(elementy, 0, newelementy, 0, elementy.length);
        elementy = newelementy;
    }

    // Dostęp do elementu
    public T get(int index) {
        if (index < 0 || index >= uzywaneMiejsce) {
            throw new IndexOutOfBoundsException();
        }
        return elementy[index];
    }

    // Aktualna liczba elementów
    public int uzywaneMiejsce() {
        return uzywaneMiejsce;
    }

    public void delete(T elem) {
        boolean znaleziono = false;
        for(int i = 0; i < uzywaneMiejsce; i++) {
            if(znaleziono) {
                elementy[i - 1] = elementy[i];
            }
            if(elementy[i] == elem) {
                znaleziono = true;
            }
        }
        if(znaleziono) uzywaneMiejsce--;
    }
}
