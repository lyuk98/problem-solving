import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	static class Count {
		public int n1;
		public int z;
		public int p1;

		public Count(int n1, int z, int p1) {
			this.n1 = n1;
			this.z = z;
			this.p1 = p1;
		}
	}

	static Count count(short[][] paper, int r, int c, int n) {
		if (n < 2) {
			switch (paper[r][c]) {
			case -1:
				return new Count(1, 0, 0);
			case 0:
				return new Count(0, 1, 0);
			case 1:
				return new Count(0, 0, 1);
			default:
				return new Count(0, 0, 0);
			}
		}

		Count s = new Count(0, 0, 0);
		int l = n / 3;

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				Count add = count(paper, r + l * i, c + l * j, l);
				
				s.n1 += add.n1;
				s.z += add.z;
				s.p1 += add.p1;
			}
		}

		if (s.n1 == 9 && s.z == 0 && s.p1 == 0) {
			return new Count(1, 0, 0);
		}
		else if (s.n1 == 0 && s.z == 9 && s.p1 == 0) {
			return new Count(0, 1, 0);
		}
		else if (s.n1 == 0 && s.z == 0 && s.p1 == 9) {
			return new Count(0, 0, 1);
		}

		return s;
	}

	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

		int n = Integer.parseInt(in.readLine());
		short[][] paper = new short[n][n];

		for (int i = 0; i < n; ++i) {
			StringTokenizer tokens = new StringTokenizer(in.readLine());
			for (int j = 0; j < n; ++j) {
				paper[i][j] = Short.parseShort(tokens.nextToken());
			}
		}

		Count result = count(paper, 0, 0, n);

		System.out.println(result.n1);
		System.out.println(result.z);
		System.out.println(result.p1);

		in.close();
	}
}
