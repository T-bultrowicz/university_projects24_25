public class Zasób1 implements AutoCloseable {
    // Dane
    // Techniczne
    public Zasób1(){  // Przydzielanie zasobu
        System.out.println("Zasób1");  // Tu np. otwieranie pliku, pobieranie pamięci, itp.
    }

    public void użyj(){
        System.out.println("używanie zasobu");
    }

    public void zwolnij(){  // Zwalnianie zasobu
        System.out.println("Zasób1 zwolniony");
    }

    @Override
    public void close() {
        zwolnij();
    }
}
