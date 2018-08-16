#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <queue>
#include <set>
#include <map>

using namespace std;

typedef long long ll ;
typedef pair<ll,ll> pll ;
typedef map<ll,ll> mll ;

struct node
{
  ll spinf ;
  ll spsup ;
  ll value ;
};

const ll MOD = 1000000007 ;

int NBTEST ;

ll getTree( int sp , int i , int h , int hmax , node * tree )
{

  if( h > hmax )
    return 0 ;

  if( tree[i].spsup < sp )
    return tree[i].value ;

  if( tree[i].spinf >= sp )
    return 0 ;


  return ( getTree( sp , 2*i , h+1, hmax, tree ) + getTree( sp , 2*i+1 , h+1, hmax, tree ) ) % MOD ;  
}

void addTree( int v , int i , node * tree )
{
  if( i == 0 )
    return ;
  
  tree[i].value = (tree[i].value + v) % MOD ;
  addTree( v , i/2 , tree ) ;
}


int main()
{
  cin >> NBTEST ;
  for( int TEST = 1 ; TEST <= NBTEST ; TEST ++ )
    {
      ll result = 0 ;
      ll result2 = 0 ;

      ll n, m, X, Y , Z ;
      cin >> n >> m >> X >> Y >> Z ;

      ll * A = new ll[m] ;
      ll * speedLimits = new ll[n] ;

      for( int i = 0 ; i < m ; i ++ )
        {
          int scan ;
          scanf("%d", &scan ) ;
          A[i] = (ll) scan ;
        }


      for( int i = 0 ; i < n ; i ++ )
        {
          speedLimits[i] = A[i % m ] ;
          A[i % m] = ( X * A[i % m] + Y * (i + 1) ) % Z ;
        }
      
      for( int i = 0 ; i < n ; i ++ )
        {
          //cout << speedLimits[i] << endl ;
        }      

      
      /*
      ll V[n] ;
      for( int i = 0 ; i < n ; i ++ )
        V[i] = 1 ;

      for( int sl = 0 ; sl < n ; sl ++ )
        for( int sp = 0 ; sp < sl ; sp ++ )
          if( speedLimits[sp] < speedLimits[sl] )
            V[sl] = (V[sl] + V[sp]) % MOD ;
          
      for( int sp = 0 ; sp < n ; sp ++ )
        result = (result + V[sp]) % MOD ; 
      */
      
      set<ll> * ins = new set<ll>() ;
      mll * spI = new mll() ;
      for( int sp = 0 ; sp < n ; sp ++ )
        ins->insert( speedLimits[sp] ) ;

      ll nbDSL = ins->size() ;
      ll * distinctSL = new ll[nbDSL] ;
      int cmp = 0 ;
      for( set<ll>::iterator it = ins->begin() ; it != ins->end() ; it ++ )
        {
          distinctSL[cmp] = *it ;
          (*spI)[*it] = cmp ;
          //cout << *it << endl ;
          cmp ++ ;
        }
      
      int h = 0 ;
      while( nbDSL > (1<<h) )
        h ++ ;
      
      int sizeTree = 1 << (h+1) ;
      
      
      //cout << "TEST" << endl ;

      //cout << sizeTree << endl ;

      node * tree = new node[ sizeTree ] ;
      
      //cout << "TEST" << endl ;
      //cout << "seg" << endl; 
      
      for( int i = sizeTree -1 ; i >= 1 ; i -- )
        {

          //cout << i<< endl ;
        if( i >= (1 << h) )
          {
            int borne ;
            if( i - (1 << h ) < nbDSL )
              {
              borne = distinctSL[ i - (1 << h) ] ;
              }
            else
              {
              borne = 2*MOD  ;
              }
            tree[i].spsup = borne ;
            tree[i].spinf = borne ;
            tree[i].value = 0 ;
          }
        else
          {
            tree[i].spsup = max( tree[2*i].spsup , tree[2*i+1].spsup ) ;
            tree[i].spinf = min( tree[2*i].spinf , tree[2*i+1].spinf ) ;
            tree[i].value = 0 ;
          }
        }
      
  

      //cout << sizeTree << endl ;
      //for( int i = 1 ; i < sizeTree ; i ++ )
      //  cout << tree[i].spsup << " " << tree[i].spinf << " " << tree[i].value << endl ;
      
      //ll getTree( int sp , int i , int h , int hmax , node * tree )
      //void addTree( int v , int i , node * tree )

      for( int sp = 0 ; sp < n ; sp ++ )
        {
          ll v = 1 ;
          ll speed = speedLimits[sp] ;
          //cout << sp << endl ;
          v = (v + getTree( speed , 1 , 0 , h , tree )) % MOD ;
          
          //cout << sp << endl ;
          //cout << speedLimits[sp] << " " << v << endl ;
          //          cout << v << endl ;
          
          result2 = (result2 + v) % MOD ;
          addTree( v , (1<<h) + (*spI)[speed] , tree ) ;
          
          //cout << sp << endl ;
        }
      
      //cout << sizeTree << endl ;
      //for( int i = 1 ; i < sizeTree ; i ++ )
      //  cout << tree[i].spsup << " " << tree[i].spinf << " " << tree[i].value << endl ;
      
      delete[] tree ;
      delete[] distinctSL;
      delete[] speedLimits ;
      delete[] A ;
      delete ins ;
      delete spI ;
      //cout << "Case #" << TEST << ": " << result << endl ;
      cout << "Case #" << TEST << ": " << result2 << endl ;

      
    }
} 
