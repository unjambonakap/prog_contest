#include <cstdio>
#include <vector>

using namespace std;


#ifdef VERB
bool prnt;
#endif

long long getMaxF(int D, int B) {
#ifdef VERB
if (prnt) printf("getMaxF(%d, %d)\n", D, B);
#endif
	long long f = 0, add = 1, pf = -1;
	for (int b = 1; f != pf && b <= B; b++) {
		pf = f;
		add = add*(D-b+1)/b;
		f += add;
#ifdef VERB
if (prnt) printf(" b %d, add %lld, f %lld\n", b, add, f);
#endif
		if (f >= 4294967296LL) return -1;
	}
#ifdef VERB
if (prnt) printf(" -> f %lld\n", f);
#endif
	return f;
}

int getMinB(int F, int D) {
#ifdef VERB
printf("getMinB(%d, %d)\n", F, D);
#endif
	long long f = 0, add = 1;
	for (int b = 1; f < F; b++) {
		add = add*(D-b+1)/b;
		f += add;
#ifdef VERB
printf(" b %d, add %lld, f %lld\n", b, add, f);
#endif
		if (f >= F) return b;
	}
	return -1;
}

int getMinD(int F, int B) {
#ifdef VERB
	prnt = false;
printf("getMinD(%d, %d)\n", F, B);
#endif
	if (B == 1) return F;

	int mx = 2000000000, mn = 0;
	while (mn+1 < mx) {
		int md = mn + (mx-mn)/2;
		long long f = getMaxF(md, B);
		if (f < 0 || f >= F) mx = md;
		else mn = md;
#ifdef VERB
printf(" md %d (F %lld) -> mx %d, mn %d\n", md, f, mx, mn);
#endif
	}
	return mx;
}

void doCase(int cn, int f, int d, int b) {
#ifdef VERB
	prnt = true;
#endif
	printf("Case #%d: ", cn);
	long long F = getMaxF(d, b);
	int D = getMinD(f, b);
	int B = getMinB(f, d);
	printf("%lld %d %d\n", F, D, B);
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int f, d, b;
		scanf(" %d %d %d", &f, &d, &b);
		doCase(i+1, f, d, b);
	}
	return 0;
}

