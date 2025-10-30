
public class Main {

    private static int fibonacci(int x) {
        if (x == 1 ) {
            return 0;
        } else if (x == 2) {
            return 1;
        }
        return fibonacci(x-1) + fibonacci(x-2);
    }

    private static boolean isSorted(int[] numbers) {
        boolean sorted = true;
        for (int i = 0; i < numbers.length - 1; i++) {
            if (numbers[i] > numbers[i+1]) {
                sorted = false;
                break;
            }
        }
        return sorted;
    }

    private static void sieves(int number) {

        boolean[] primes = new boolean[number + 1];

        for (int i = 2; i <= number; i++) {
            primes[i] = true;
        }
        
        for (int i = 2; i <= Math.sqrt(number); i++) {
            if (primes[i]){
                for (int j = i*i; j <= number; j += i) {
                        primes[j] = false;
                }
            }
        }

        for (int i = 0; i <= number; i++){
            if (primes[i]){
                System.out.println(i);
            }
        }
    }

    public static void main(String[] args) {
        sieves(fibonacci(9));
    }
}
