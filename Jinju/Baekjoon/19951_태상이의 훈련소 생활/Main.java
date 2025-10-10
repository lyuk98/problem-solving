import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int N, M;
        N = Integer.parseInt(input[0]);
        M = Integer.parseInt(input[1]);

        ArrayList<Integer> ground = new ArrayList<>();
        input = br.readLine().split(" ");
        for (int i = 0; i < N; i++) {
            ground.add(Integer.parseInt(input[i]));
        }

        ArrayList<Integer> diff = new ArrayList<>(Collections.nCopies(N+2, 0));
        for (int i = 0; i < M; i++) {
            input = br.readLine().split(" ");
            int start, end, height;
            start   = Integer.parseInt(input[0]);
            end     = Integer.parseInt(input[1]) + 1;
            height  = Integer.parseInt(input[2]);

            diff.set(start, diff.get(start) + height);
            diff.set(end,   diff.get(end)   - height);
            // System.err.println("중간 결과");
            // for (Integer integer : diff) {
            //     System.out.print(integer + " ");
            // }
            // System.err.println();
        }

        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum = diff.get(i+1) + sum;
            int result = ground.get(i) + sum;
            System.out.print(result + " ");
        }

    }
}
