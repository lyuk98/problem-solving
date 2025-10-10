import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int N, M;
        String[] input = br.readLine().split(" ");
        N = Integer.parseInt(input[0]);
        M = Integer.parseInt(input[1]);

        ArrayList<ArrayList<Integer>> map = new ArrayList<>();
        ArrayList<ArrayList<Integer>> prefixMap = new ArrayList<>();
        
        for (int i = 0; i <= N; i++) {
            map.add(new ArrayList<>(Collections.nCopies(M+2, 0)));
            prefixMap.add(new ArrayList<>(Collections.nCopies(M+2, 0)));
        }

        for (int i = 1; i <= N; i++) {
            input = br.readLine().split(" ");
            for (int j = 1; j <= M; j++) {
                map.get(i).set(j, Integer.parseInt(input[j-1]));
                prefixMap.get(i).set(j, 
                    Integer.parseInt(input[j-1])  +
                    prefixMap.get(i).get(j-1)   +
                    prefixMap.get(i-1).get(j)   -
                    prefixMap.get(i-1).get(j-1)
                );
            }
        }

        // 누적합 출력
        // for (ArrayList<Integer> arr : prefixMap) {
        //     for (int a : arr) {
        //         System.out.print(a + "\t");
        //     }
        //     System.out.println();
        // }

        // 방법 1) 완전 탐색을 통한 답안 도출
        int maxSum = Integer.MIN_VALUE;

        // for (int r1 = 1; r1 <= N; r1++) {
        //     for (int c1 = 1; c1 <= M; c1++) {
        //         for (int r2 = r1; r2 <= N; r2++) {
        //             for (int c2 = c1; c2 <= M; c2++) {
        //                 int sum = prefixMap.get(r2).get(c2)
        //                         - prefixMap.get(r1-1).get(c2)
        //                         - prefixMap.get(r2).get(c1-1)
        //                         + prefixMap.get(r1-1).get(c1-1);
        //                 maxSum = Math.max(maxSum, sum);
        //             }
        //         }
        //     }
        // }

        // 방법 2) Kadane
        maxSum = Integer.MIN_VALUE;
        for (int r1 = 1; r1 <= N; r1++) {
            // 열 합 초기화
            int[] colSum = new int[M+1];
            
            // 행 끝
            for (int r2 = r1; r2 <= N; r2++) {
                // colSum 업데이트 (r2행 추가)
                for (int c = 1; c <= M; c++) {
                    colSum[c] += map.get(r2).get(c);
                }
                
                // Kadane's algorithm on colSum[1..M]
                int current = 0;
                for (int c = 1; c <= M; c++) {
                    current = Math.max(colSum[c], current + colSum[c]);
                    maxSum = Math.max(maxSum, current);
                }
            }
        }

        System.out.println(maxSum);

    }
}
