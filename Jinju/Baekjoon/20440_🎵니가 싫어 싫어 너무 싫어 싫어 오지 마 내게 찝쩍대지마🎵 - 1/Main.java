import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine().trim());

        TreeMap<Integer, Integer> map = new TreeMap<>();

        for (int i = 0; i < N; i++) {
            String[] input = br.readLine().split(" ");
            int start = Integer.parseInt(input[0]);
            int end = Integer.parseInt(input[1]);

            map.put(start, map.getOrDefault(start, 0) + 1);
            map.put(end, map.getOrDefault(end, 0) - 1);
        }

        int maxMogi = 0;
        int current = 0;
        int startResult = -1, endResult = -1;

        for (Map.Entry<Integer, Integer> e : map.entrySet()) {
            int time = e.getKey();
            current += e.getValue();

            // 새로운 최대값 갱신
            if (current > maxMogi) {
                maxMogi = current;
                startResult = time;
                endResult = -1; // 다시 초기화
            }

            // 최대 모기 유지하다가 줄어드는 순간 → 끝나는 시점
            if (current < maxMogi && endResult == -1) {
                endResult = time;
            }
        }

        System.out.println(maxMogi);
        System.out.println(startResult + " " + endResult);
    }
}
