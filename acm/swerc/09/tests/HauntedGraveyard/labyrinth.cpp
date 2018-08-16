#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <cassert>
using namespace std;

/* 
Solution to "Enchanted graveyard"
SWERC 2009, Madrid
Enrique Martín
*/
//#define DEBUG

const int infinity = 2e9;

class GhostHole
{
  public:
  int x1, y1, x2, y2, t;
  GhostHole( int _x1 = -1, int _y1 = -1, int _x2 = -1, int _y2 = -1 , int _t = 0 ) : 
    x1(_x1), y1(_y1), x2(_x2), y2(_y2), t(_t)
  {}

  bool operator<( const GhostHole& a ) const
  { 
    if( x1 < a.x1 ) return true;
    else if ( x1 == a.x1 && y1 < a.y1 ) return true;
    else return false; 
  }
};

class Position
{
  public:
  int x, y;
  Position( int _x = -1, int _y = -1 ) : x(_x), y(_y) {}

  bool operator<( const Position& a ) const
  { 
    if( x < a.x ) return true;
    else if ( x == a.x  && y < a.y) return true;
    else return false;  
  }

  void show() const
  { cout << "(" << x << ", " << y << ")"; }
};

class Edge
{
  public:
  int orig, dest, cost;
  
  Edge( int _orig, int _dest, int _cost ) : orig(_orig), dest(_dest), cost(_cost) {}
  void show() const
  { cout << "< orig: " << orig << ", dest: " << dest << " | cost: " << cost << " >"; }
};

set< Position > gravestones;
set< GhostHole > ghostholes;
list< Edge > edges;
vector< int > vdist;
vector< int > vpred;


inline int nodeNumber( int x, int y, int w )
{ return x + (w*y); }

#ifdef DEBUG
// Show the distance to the cells
inline pair<int, int> numberNode( int cell, int w )
{
  return make_pair( cell % w, cell / w );
}
#endif

inline bool inRange( int x, int y, int w, int h )
{ return (x >= 0) && (x < w) && (y >= 0) && (y < h); }

bool isGravestone( int x, int y )
{
  Position p(x,y);
  set< Position >::iterator it;

  it = gravestones.find( p );
  return (it != gravestones.end() );
}

bool isGhostHole( int x, int y )
{
  GhostHole gh(x,y,0,0,0);
  set< GhostHole >::iterator it;
  it = ghostholes.find( gh );

  return (it != ghostholes.end() );
}

inline list< Edge > adjacentNodes( int x, int y, int w, int h )
{
  if (x == w - 1 && y == h - 1) return list< Edge >();

  list< Edge > res;
  const int orig = nodeNumber( x, y, w );
  
  int vx[] = { -1, 0, 1, 0 };
  int vy[] = { 0, 1, 0, -1 };

  for( int i = 0; i < 4; ++i )
  {
    int xx = x+vx[i], yy = y+vy[i];
    if( inRange(xx, yy, w, h) && !isGravestone(xx,yy) )
    {
      Edge e( orig, nodeNumber(x+vx[i], y+vy[i], w), 1);
      res.push_back( e );
    }
  }

  return res;
}

void createGraph( int w, int h )
{
  // Clear previous data
  edges.clear();
  
  for( int x = 0; x < w; ++x )
    for( int y = 0; y < h; ++y )
    {
      int node = nodeNumber(x,y,w);
      if( isGravestone(x,y) )
      { /* Do nothing */ }
      else if ( isGhostHole(x,y) )
      { // It is a ghosthole position
        GhostHole gh(x,y,0,0,0);
        set< GhostHole >::iterator it;
        it = ghostholes.find( gh );
        gh = *it;

        int destNode = nodeNumber( gh.x2, gh.y2, w );
        Edge e(node, destNode, gh.t );
        edges.push_back( e );
      }
      else
      { // It is a normal position
        list< Edge > res = adjacentNodes( x, y, w, h );
        edges.insert( edges.end(), res.begin(), res.end() );
      }
    }
  
}

bool bellmanFord( int origin, int total, int w )
{
  const int n = total;
  list< Edge >::iterator it;
  
  vdist.resize( n );
  vpred.resize( n );
  for( int i = 0; i < n; ++i )
  {
    vdist.at(i) = infinity;
    vpred.at(i) = -1;
  }  
  vdist.at(origin) = 0;

  for( int i = 1; i < n; ++i )
  {
    // Process all the edges in the graph
    for( it = edges.begin(); it != edges.end(); it++ )
    {
      const int u = (*it).orig;
      const int v = (*it).dest;
      const int cost = (*it).cost;
       
      // Update the distance, only if the origin nade is reachable and the and the new distance is than the previous
      if(  vdist.at(u) != infinity && vdist.at(v) > vdist.at(u) + cost )
      {
        vdist.at(v) = vdist.at(u) + cost;
        vpred.at(v) = u;
      }
    }
  }
  
  #ifdef DEBUG
  // Show the distances of the cells
  for ( unsigned int i = 0; i < vdist.size(); ++i )
  {
    pair<int,int> p = numberNode(i,w);
    cout << "vdist[" << p.first << ", " << p.second << "]: " << vdist.at(i) << endl;
  }
  #endif
  
  // Check REACHABLE negative cycles
  for( it = edges.begin(); it != edges.end(); it++ )
  {
    const int u = (*it).orig;
    const int v = (*it).dest;
    const int cost = (*it).cost;
      
    // If u is reachable and the distance can be improved, then there are reachable negative cicles
    if ( vdist.at(u) != infinity && vdist.at(v) > vdist.at(u) + cost )
      return false;
  }
  
  return true;  
}



void showGraph()
{
  cout << "-------------------------------------" << endl;
  list< Edge >::iterator it;
  for ( it = edges.begin(); it != edges.end(); it++ )
    (*it).show();
    
  cout << "-------------------------------------" << endl;
}

void showSet( set<Position> s )
{
  cout << "Set: ";
  for( set<Position>::iterator it = s.begin(); it != s.end(); it++ )
  {
    (*it).show();
    cout << " ";
  }
  cout << endl;
}






int main()
{
  int g, gh, w, h;
  bool ok;

  cin >> w >> h;
  while( w > 0 && h > 0 )
  {
    cin >> g;
    gravestones.clear();
    for( int i = 0; i < g; ++i )
    {
      Position p;

      cin >> p.x >> p.y;
      pair< set< Position >::iterator, bool > par;
      par = gravestones.insert( p );
      assert( par.second );
    }

    cin >> gh;
    ghostholes.clear();
    for( int i = 0; i < gh; ++i )
    {
      GhostHole ghole;
      cin >> ghole.x1 >> ghole.y1 >> ghole.x2 >> ghole.y2 >> ghole.t;
      ghostholes.insert( ghole );
    }
    
    createGraph(w,h);
    ok = bellmanFord( 0, w*h, w ); 
    if( !ok )
      cout << "Never" << endl;
    else
      {
        if( vdist.at( w*h - 1 ) == infinity )
          cout << "Impossible" << endl;
        else
          cout << vdist.at( w*h - 1 ) << endl; 
      }

    cin >> w >> h;
  }  

  return 0;
}

