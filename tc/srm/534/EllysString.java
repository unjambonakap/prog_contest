
import java.util.Arrays;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class EllysString {
    static final int INF = (int) 1e9;
    

    public static void main (String[] args){
        String [] a={"abcde"};
        String [] b={"edcba"};
        System.out.println(theMin(a,b));
    }


    public static int theMin(String[] _s, String[] _t) {
        String s = concatenate(_s);
        String t = concatenate(_t);
        if (s.length() != t.length()) throw new RuntimeException();
        int[] scnt = new int[26];
        int[] tcnt = new int[26];
        for (char ch : s.toCharArray()) ++scnt[ch - 'a'];
        for (char ch : t.toCharArray()) ++tcnt[ch - 'a'];
        int[][] spos = new int[26][];
        int[][] tpos = new int[26][];
        for (int i = 0; i < 26; ++i) {
            spos[i] = new int[scnt[i]];
            tpos[i] = new int[tcnt[i]];
        }
        int[] best = new int[s.length() + 1];
        Arrays.fill(best, INF);
        best[0] = 0;
        for (int start = 0; start < s.length(); ++start) {
            best[start + 1] = Math.min(best[start + 1], best[start] + 1);
            Arrays.fill(scnt, 0);
            Arrays.fill(tcnt, 0);
            int numEqual = 26;
            int totalDelta = 0;
            for (int len = 1; start + len <= s.length(); ++len) {
                int ch = s.charAt(start + len - 1) - 'a';
                if (scnt[ch] == tcnt[ch]) --numEqual;
                spos[ch][scnt[ch]++] = len;
                if (scnt[ch] <= tcnt[ch]) {
                    totalDelta += Math.abs(spos[ch][scnt[ch] - 1] - tpos[ch][scnt[ch] - 1]);
                }
                if (scnt[ch] == tcnt[ch]) ++numEqual;
                ch = t.charAt(start + len - 1) - 'a';
                if (scnt[ch] == tcnt[ch]) --numEqual;
                tpos[ch][tcnt[ch]++] = len;
                if (tcnt[ch] <= scnt[ch]) {
                    totalDelta += Math.abs(spos[ch][tcnt[ch] - 1] - tpos[ch][tcnt[ch] - 1]);
                }
                if (scnt[ch] == tcnt[ch]) ++numEqual;
                if (numEqual == 26) {

                    System.out.println(start);
                    System.out.println(totalDelta/2);
                    best[start + len] = Math.min(best[start + len], best[start] + totalDelta / 2);
                }
            }
        }
        return best[s.length()];
    }

    public static String concatenate(String[] t) {
        StringBuilder b = new StringBuilder();
        for (String x : t) b.append(x);
        return b.toString();
    }
}
