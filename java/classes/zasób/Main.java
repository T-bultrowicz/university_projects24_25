import java.util.Random;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {

    private void m1() {
        Random r = new Random();

        while(r.nextFloat() < 0.5){
            Zasób1 z1 = new Zasób1();  // Pobranie zasobu


            if (r.nextFloat() < 0.5) {
                z1.zwolnij();  // Zwalnianie zasobu
                throw new RuntimeException("Nie zwolnię zasobu !!! ");
            }

            if (r.nextFloat() < 0.5) {
                z1.zwolnij();  // Zwalnianie zasobu
                return;
            }

            if (r.nextFloat() < 0.5) {
                z1.zwolnij();  // Zwalnianie zasobu
                break;
            }

            if (r.nextFloat() < 0.5) {
                z1.zwolnij();  // Zwalnianie zasobu
                continue;
            }


            z1.użyj();

            z1.zwolnij();
        }
    }

    private void m2() {
        Random r = new Random();

        while(r.nextFloat() < 0.9) {
            Zasób1 z1 = new Zasób1();
            try {
                if(r.nextFloat() < 0.5) {
                    throw new RuntimeException("Nie zwolnię zasobu !!! ");
                }
                if(r.nextFloat() < 0.5) {
                    continue;
                }
                z1.użyj();
            } catch(Exception e) {
                System.out.println("Doszło do błędu " + e.getMessage());
            } finally {
                z1.zwolnij();
            }
        }
    }

    private void m3() {

        Random r = new Random();
        while(r.nextFloat() < 0.5) {
            try(Zasób1 z1 = new Zasób1()) {
                if(r.nextFloat() < 0.5) {
                    throw new RuntimeException("Nie zwolnię zasobu !!! ");
                }
                if(r.nextFloat() < 0.5) {
                    continue;
                }   
                z1.użyj();             
            } catch(Exception e) {
                System.out.println("Doszło do błędu " + e.getMessage());
            }
        }
    }

    

    public static void main(String[] args) {
        //TIP Press <shortcut actionId="ShowIntentionActions"/> with your caret at the highlighted text
        // to see how IntelliJ IDEA suggests fixing it.
        System.out.println("Hej zasoby!");

        Main main = new Main();

        main.m1();
        main.m2();
        main.m3();
        System.out.println("Pa zasoby!");
    }

}