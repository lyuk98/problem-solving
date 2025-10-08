import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class App {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        

        int n = Integer.parseInt(br.readLine().trim());
        String[] input = br.readLine().split(" ");
        ArrayList<Integer> train = new ArrayList<>();
        ArrayList<Integer> prefixSum = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            train.add(Integer.parseInt(input[i]));
        }
        int maxLength = Integer.parseInt(br.readLine().trim());

        // prefixSum[0] = 0 (편의상 1-indexed처럼 사용)
        prefixSum.add(0);
        for (int i = 1; i <= n; i++) {
            prefixSum.add(prefixSum.get(i - 1) + train.get(i - 1));
        }

        // dp[k][i] : 기관차 k대로 i번째 객차까지 고려했을 때 최대 손님 수
        int[][] dp = new int[4][n + 1];

        for (int k = 1; k <=3; k++) {
            for (int i = 0 * maxLength; i < dp.length; i++) {
                dp[k][i] = Math.max(dp[k][i-1],
                    dp[k - 1][i - maxLength] + (prefixSum.get(i) - prefixSum.get(i-maxLength))
                    );
            }
        }

        System.out.println(dp[3][n]);
    }
}
