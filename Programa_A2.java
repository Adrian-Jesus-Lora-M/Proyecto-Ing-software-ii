import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Programa_A2 {

    public static void main(String[] args) {
        int numeroEntero, sumaInt = 0;
        double numeroDouble, sumaDouble = 0;

        File f = new File("c:/Users/ajlm_/OneDrive/Documentos/ITI/CURSOS/Ing de Software/numeros.txt");

        try  (Scanner entrada = new Scanner(f)) {

            
            System.out.println("Numeros de tipo int: ");

            while (entrada.hasNextInt()) { 
                numeroEntero = entrada.nextInt(); 
                System.out.print(numeroEntero + " "); 
                sumaInt = sumaInt + numeroEntero;  
            }


            System.out.println("\nSuma de los int: " + sumaInt);

            
            System.out.println("Numeros de tipo double: ");

            while (entrada.hasNextDouble()) { 
                numeroDouble = entrada.nextDouble();                                    
                System.out.print(numeroDouble + " ");  
                sumaDouble = sumaDouble + numeroDouble; 
               
            }

            
            System.out.println("\nSuma de los doubles: " + sumaDouble);

        } catch (FileNotFoundException e) {
            System.out.println(e.toString());
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }
}
