import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Vector;
import java.util.PriorityQueue;

public class App {
    // 힝 백준 버전 낮아서 요 코드는 안 돌아감
    // public record Node(int end, int value) {}
    public static class Node {
    public int end;
    public int value;
        public Node(int end, int value) {
            this.end = end;
            this.value = value;
        }
    }

    // 최솟값 저장할 곳
    public static Vector<Integer> homeToParty;
    public static Vector<Integer> partyToHome;
    // 노드 개수, 간선 개수, 목적지 노드
    public static int N, M, X;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        N = Integer.parseInt(input[0]);
        M = Integer.parseInt(input[1]);
        X = Integer.parseInt(input[2]) - 1; // 노드 번호 1 빼주기
        
        // 최소거리 초깃값 설정
        homeToParty = new Vector<>();
        partyToHome = new Vector<>();
        for (int i = 0; i < N; i++) {
            // 초기 거리 무한대 설정
            homeToParty.add(Integer.MAX_VALUE);
            partyToHome.add(Integer.MAX_VALUE);
        }
        // 목적지는 거리 0으로 설정
        homeToParty.set(X, 0);
        partyToHome.set(X, 0);


        // 입력은
        // 1 (1, 3) 즉 출발지 (목적지, 거리)
        Vector<Vector<Node>> vec = new Vector<Vector<Node>>(M);
        Vector<Vector<Node>> vecR = new Vector<Vector<Node>>(M);
        for (int i = 0; i < N; i++) {
            vec.add(new Vector<>());
            vecR.add(new Vector<>());
        }

        for (int i = 0; i < M; i++) {
            input = br.readLine().split(" ");
            // 시작, 도착, 거리 추출
            int start = Integer.parseInt(input[0])-1; // 노드 번호 1 빼주기
            int end = Integer.parseInt(input[1])-1; // 노드 번호 1 빼주기
            int value = Integer.parseInt(input[2]);

            vec.get(start).add(new Node(end, value)); 
            vecR.get(end).add(new Node(start, value)); 
        }
        // 그리구 그냥 다익스트라 돌림
        
        // 집에서 파티가는 초깃값
        PriorityQueue<Node> pq = new PriorityQueue<>((n1, n2) -> n1.value - n2.value);
        for (int i = 0; i < vec.get(X).size(); i++) {
            int end = vec.get(X).get(i).end;
            int value = vec.get(X).get(i).value;
            pq.add(new Node(end, value));
        }
        while (!pq.isEmpty()) {
            Node current = pq.peek();
            int end = current.end;
            int value = current.value;

            // 현재 저장된, 해당 노드까지 도달하는 데 최소값보다 지금이 더 작다면
            if (homeToParty.get(end) >= value) {
                // 값을 업데이트하고
                homeToParty.set(end, value);
                // 해당 노드부터 갈 수 있는 곳들을 큐에 추가
                for(int i = 0; i < vec.get(end).size(); i++){
                    // 이 노드 부터는 dest노드를 갈 수 있고
                    int dest = vec.get(end).get(i).end;
                    // 거기까지 가는데엔 지금까지 거리 + dest노드까지의 거리임
                    int newValue = vec.get(end).get(i).value + value;
                    pq.add(new Node(dest, newValue));
                }
            }
            pq.poll();
        }

        
        // 파티에서 집가는 초깃값
        pq = new PriorityQueue<>((n1, n2) -> n1.value - n2.value);
        for (int i = 0; i < vecR.get(X).size(); i++) {
            int end = vecR.get(X).get(i).end;
            int value = vecR.get(X).get(i).value;
            pq.add(new Node(end, value));
        }
        while (!pq.isEmpty()) {
            Node current = pq.peek();
            int end = current.end;
            int value = current.value;

            // 현재 저장된, 해당 노드까지 도달하는 데 최소값보다 지금이 더 작다면
            if (partyToHome.get(end) >= value) {
                // 값을 업데이트하고
                partyToHome.set(end, value);
                // 해당 노드부터 갈 수 있는 곳들을 큐에 추가
                for(int i = 0; i < vecR.get(end).size(); i++){
                    // 이 노드 부터는 dest노드를 갈 수 있고
                    int dest = vecR.get(end).get(i).end;
                    // 거기까지 가는데엔 지금까지 거리 + dest노드까지의 거리임
                    int newValue = vecR.get(end).get(i).value + value;
                    pq.add(new Node(dest, newValue));
                }
            }
            pq.poll();
        }

        int max = 0;
        for (int i = 0; i < N; i++) {
            int sum = homeToParty.get(i) + partyToHome.get(i);
            // System.out.print(homeToParty.get(i) + " ");
            // System.out.println(partyToHome.get(i));
            if (sum > max) {
                max = sum;
            }
        }

        System.out.println(max);
    }
}
