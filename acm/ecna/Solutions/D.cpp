#include <iostream>
using namespace std;

struct config {
	int p[6];
} list[15504];

int start[17];

int main()
{
	int count=0;
	for(int m=0; m<=15; m++) {
		start[m] = count;
	for(int l=0; l<=15-m; l++) {
	for(int k=0; k<=15-m-l; k++) {
	for(int j=0; j<=15-m-l-k; j++) {
	for(int i=0; i<=15-m-l-k-j; i++) {
		list[count].p[0] = m;
		list[count].p[1] = l;
		list[count].p[2] = k;
		list[count].p[3] = j;
		list[count].p[4] = i;
		list[count].p[5] = 15-i-j-k-l-m;
		count++;
	}}}}}

	char ch;
	cin >> ch;
	int icase=0;
	while (ch != 'e') {
		cout << "Case " << ++icase << ": ";
		if (ch == 'm') {
			int p[6];
			for(int i=0; i<6; i++)
				cin >> p[i];
			int index=start[p[0]];
			for(int j=1; j<6; j++) {
				while(list[index].p[j] != p[j])
					index++;
			}
			cout << index << endl;
		}
		else {
			int n;
			cin >> n;
			cout << list[n].p[0];
			for(int i=1; i<6; i++)
				cout << ' ' << list[n].p[i];
			cout << endl;
		}

		cin >> ch;
	}
}
