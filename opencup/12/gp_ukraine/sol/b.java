import static java.math.BigInteger.valueOf;

import java.io.*;
import java.util.*;

public class B {

    static void solve() throws IOException {
        precalc();
        int q = nextInt();
        for (int i = 0; i < q; i++) {
            int n = nextInt(), k = nextInt();
            out.println(get(n, k));
        }
    }

    static final int MAX = 1010;
    static final int MOD = 1000000000 + 7;

    static int[][] values;
    static int[][] valuesWithAdditionalInfo;
    static int[] invFact;

    static int get(int n, int k) {
        if (n < MAX) {
            return values[k][n];
        }

        long num = 0, den = 1;
        int[] val = valuesWithAdditionalInfo[k];

        for (int i = 0; i <= k + 1; i++) {
            long curNum = val[i];
            long curDen = (n - i);
            long newNum = (num * curDen + den * curNum) % MOD;
            long newDen = den * curDen % MOD;
            num = newNum;
            den = newDen;
        }

        long ans = num % MOD;
        return (int) ans;
    }

    static int modInverse(int a) {
        return valueOf(a).modInverse(valueOf(MOD)).intValue();
    }

    static void precalc() {
        int[] pows = new int[MAX + 2];
        pows[0] = 0;
        for (int i = 0; i < pows.length; i++) {
            pows[i] = 1;
        }
        values = new int[MAX][MAX];
        for (int k = 1; k < MAX; k++) {
            int sum = 0;
            for (int n = 0; n < MAX; n++) {
                pows[n] = (int) ((long) pows[n] * n % MOD);
                sum += pows[n];
                if (sum >= MOD) {
                    sum -= MOD;
                }
                values[k][n] = sum;
            }
        }
        invFact = new int[MAX];
        invFact[0] = 1;
        for (int i = 1; i < MAX; i++) {
            invFact[i] = (int) ((long) invFact[i - 1] * modInverse(i) % MOD);
        }
        valuesWithAdditionalInfo = new int[MAX][MAX];
        for (int k = 1; k < MAX - 1; k++) {
            int[] val = values[k];
            int[] val2 = valuesWithAdditionalInfo[k];
            for (int i = 0; i <= k + 1; i++) {
                long cur = val[i];
                cur = cur * invFact[i] % MOD;
                cur = cur * invFact[k + 1 - i] % MOD;
                if (((k + 1 - i) & 1) != 0) {
                    cur = MOD - cur;
                }
                val2[i] = (int) cur;
            }
        }
    }

    public static void main(String[] args) throws Exception {
        br = new BufferedReader(new FileReader("b.in"));
        out = new PrintWriter("b.out");
        solve();
        out.close();
    }

    static BufferedReader br;
    static StringTokenizer st;
    static PrintWriter out;

    static String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            String line = br.readLine();
            if (line == null) {
                return null;
            }
            st = new StringTokenizer(line);
        }
        return st.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    static long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    static double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }
}
