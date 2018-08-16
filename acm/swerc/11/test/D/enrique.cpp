/*
 Enrique Martin's solution
 O( B.log N )
*/

#include <iostream>
#include <queue>
using namespace std;

const int LEN = 8096;

class Distr
{
private:
  int maxHabPerBallot(int h, int b)
  {
    int r = h/b;
    if ( h % b != 0 ) r++;
    return r;
  }
  
public:
  int inhabitants;
  int ballots;
  int ratio;
  
  Distr(int h, int b) : inhabitants(h), ballots(b)
  {
    ratio = maxHabPerBallot(h,b);
  }
  
  void addBallot()
  {
    ballots++;
    ratio = maxHabPerBallot(inhabitants,ballots);
  }
  
  const bool operator <(const Distr& b) const
  {
    if (ratio == b.ratio) return ballots < b.ballots;
    else return ratio < b.ratio;
  }
  
  friend ostream& operator <<(ostream& out, const Distr& a)
  {
    out << "{hab:" << a.inhabitants << ", ballots:" << a.ballots << ", ratio:" << a.ratio << "}";
    return out;
  }

};

priority_queue<Distr> *q; /*'List' of cities-ballots ordered by the ratio inhabitants/ballots */
char buf[LEN];

int main()
{
  int ntowns, nballots, hab, ballot;
  
  while( true )
  {
    cin >> ntowns >> nballots;
    if( (ntowns == -1) && (nballots == -1))
      break;
      
    q = new priority_queue<Distr>; 
    for( int i = 0; i < ntowns; ++i )
    {
      cin >> hab;
      Distr d(hab,1);
      q->push(d);
    }
    cin.getline (buf,LEN); //Skips the blank line
    ballot = ntowns;
    
    /*Add a new ballot to the most crowed city*/
    for( int i = ntowns; i < nballots; ++i )
    {
      Distr d = q->top();
      q->pop();
      d.addBallot();
      q->push(d);
    }
    
    cout << q->top().ratio << endl;
    delete q;
  }
  
  return 0;
}
