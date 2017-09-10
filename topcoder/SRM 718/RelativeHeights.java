import java.io.*;
import java.util.*;

public class RelativeHeights {
    public int countWays(int[] h) {
        int n = h.length;
        Set S = new HashSet();
        for (int i = 0; i < n; ++i)
            S.add(toRank(h, i, n));
        return S.size();
    }

    private String toRank(int[] a, int at, int n) {
        int cnt = 0;
        int[] copy = new int[n - 1];
        for (int i = 0; i < n; ++i)
            if (i != at) copy[cnt++] = a[i];
        char[] rk = new char[n - 1];
        Arrays.sort(copy);
        cnt = 0;
        for (int i = 0; i < n; ++i)
            if (i != at) rk[cnt++] = (char) Arrays.binarySearch(copy, a[i]);
        return new String(rk);
	}

// CUT begin
    public static void main(String[] args){
        System.err.println("RelativeHeights (250 Points)");
        System.err.println();
        HashSet<Integer> cases = new HashSet<Integer>();
        for (int i = 0; i < args.length; ++i) cases.add(Integer.parseInt(args[i]));
        runTest(cases);
    }

    static void runTest(HashSet<Integer> caseSet) {
        int cases = 0, passed = 0;
        while (true) {
            String label = Reader.nextLine();
	    	if (label == null || !label.startsWith("--"))
	    		break;

            int[] h = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < h.length; ++i)
                h[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(h, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1502424552;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] h, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		RelativeHeights instance = new RelativeHeights();
		int __result = 0;
		try {
			__result = instance.countWays(h);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__result == __expected) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + __expected);
			System.err.println("           Received: " + __result);
			return false;
		}
	}

	static class Reader {
        private static final String dataFileName = "RelativeHeights.sample";
	    private static BufferedReader reader;

	    public static String nextLine() {
	        try {
                if (reader == null) {
                    reader = new BufferedReader(new InputStreamReader(new FileInputStream(dataFileName)));
                }
                return reader.readLine();
	        }
	        catch (IOException e) {
	            System.err.println("FATAL!! IOException");
	            e.printStackTrace();
	            System.exit(1);
	        }
	        return "";
	    }
	}
// CUT end
}
