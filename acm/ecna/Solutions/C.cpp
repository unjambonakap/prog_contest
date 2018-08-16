#include <iostream>
using namespace std;

class piece {
public:
	piece()
	{
		topPos = 0;
	}

	void setVals(int v[])
	{
		vals[0] = v[0];
		vals[1] = v[1];
		vals[2] = v[2];
		vals[3] = v[3];
		vals[4] = v[4];
		vals[5] = v[5];
	};

	void align(int val, int pos)
	{
		int i;
		for(i=0; i<6; i++) {
			if (vals[i] == val)
				break;
		}
		topPos = (6+i-pos)% 6;
//cout << "aligning top to position " << topPos << endl;
	};

	int val(int pos)
	{
		return vals[(pos+topPos)%6];
	};

	int vals[6];
	int topPos;
};

piece pieces[7];
int placement[7];
bool used[7];
int numSolution;

bool goodSolution()
{
	for(int place=1; place <7; place++) {
		piece thisPiece = pieces[placement[place]];
		piece nextPiece = pieces[placement[1]];
		if (place < 6)
			nextPiece = pieces[placement[place+1]];
		int pos = (place+1)%6;
		int thisVal = thisPiece.val(pos);
		int nextVal = nextPiece.val((pos+3)%6);
//cout << "thisVal = " << thisVal << ", nextVal = " << nextVal << endl;
		if (thisVal != nextVal)
			return false;
	}
	return true;
}

void doit(int place)
{
//cout << "Place " << place << endl;
	if (place == 7) {
		if (goodSolution()) {
			++numSolution;
			for(int i=0; i<7; i++) {
				cout << placement[i];
				if (i < 6)
					cout << ' ';
			}
			cout << endl;
		}
//		exit(0);
		return;
	}

	for(int i=0; i<7; i++) {
		if (used[i])
			continue;
		used[i] = true;
		placement[place] = i;
		if (place == 0) {
			pieces[i].align(1, 0);
		}
		else {
			int pos = (place+2)%6;
			int val = pieces[placement[0]].val((pos+3)%6);
			pieces[i].align(val, pos);
		}
		doit(place+1);
		used[i] = false;
	}
}

int main()
{
	int ncases;
	cin >> ncases;
	int tmp[6];
	for(int icase = 1; icase <= ncases; icase++) {
		for(int i=0; i<7; i++) {
			for(int j=0; j<6; j++)
				cin >> tmp[j];
			pieces[i].setVals(tmp);
		}

		numSolution = 0;
		for(int i=0; i<6; i++)
			used[i] = false;
		cout << "Case " << icase << ": ";
		doit(0);
		if (numSolution == 0)
			cout << "No solution" << endl;
		else if (numSolution > 1)
			cout << "***> Bad input, multiple solutions" << endl;
	}
}
