import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");

        int A, Q;
        A = Integer.parseInt(input[0]);
        Q = Integer.parseInt(input[1]);

        ArrayList<Integer> arr = new ArrayList<>(Collections.nCopies(A, 0));
        ArrayList<Integer> prefixArr = new ArrayList<>(Collections.nCopies(A, 0));
        input = br.readLine().split(" ");
        for (int i = 0; i < A; i++) {
            int value = Integer.parseInt(input[i]);
            arr.set(i, value);
        }
        arr.sort((a, b) -> a - b);

        prefixArr.set(0, arr.get(0));
        for (int i = 1; i < A; i++) {
            prefixArr.set(i, prefixArr.get(i-1) + arr.get(i));
        }

        for (int i = 0; i < Q; i++) {
            input = br.readLine().split(" ");
            int start, end;
            start   = Integer.parseInt(input[0]) - 1;
            end     = Integer.parseInt(input[1]) - 1;

            int result = prefixArr.get(end);;
            if (start - 1 >= 0) {
                result = prefixArr.get(end) - prefixArr.get(start - 1);
            }
            System.out.println(result);
        }
        
    }
}
