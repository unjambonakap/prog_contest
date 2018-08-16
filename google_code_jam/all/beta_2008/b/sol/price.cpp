#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <fstream>
#include <map>
#include <queue>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#pragma warning( disable : 4244 4267 4018 )
using namespace std;

typedef vector< int > vi; typedef vector< vector< int > > vvi; typedef vector< string > vs; typedef vector< double > vd;
typedef vector< vd > vvd; typedef long long ll; typedef vector< ll > vll; typedef pair< int, int > pii;
#define all( v ) (v).begin( ), (v).end( )

typedef complex< double > point;
template < class T > T X( complex< T > const & a ) { return real( a ); }
template < class T > T Y( complex< T > const & a ) { return imag( a ); }
template < class T > T dot( complex< T > const & a, complex< T > const & b ) { return real( conj( a ) * b ); }
template < class T > T cross( complex< T > const & a, complex< T > const & b ) { return imag( conj( a ) * b ); }

template < class t > vector< t > split( string const & str )
{ istringstream iss( str ); return vector< t >( istream_iterator< t >( iss ), istream_iterator< t >( ) ); }

template < class T > struct indexes_cmp {
    indexes_cmp( vector< T > const & v ) : v_( v ) {}
    bool operator()( int a, int b ) const { return v_[a] < v_[b] || ( v_[a] == v_[b] && a < b ); }
    vector< T > const & v_;
};

template < class T >  void sorted_permutation( vector< T > const & v, vector< int > & p ) {
    p.resize( v.size(), 1 );
    for ( int i = 0; i < p.size(); ++i ) p[i] = i;
    sort( all( p ), indexes_cmp< T >( v ) );
}

void main() {
    ifstream in( "input.txt" );
    ofstream out( "output.txt" );

    int n;
    in >> n;
    string s;
    getline( in, s );
    
    for ( int i = 1; i <= n; ++i ) {
        out << "Case #" << i << ": ";

        string s1, s2;
        getline( in, s1 );
        getline( in, s2 );

        vs names = split< string >( s1 );
        vi prices = split< int >( s2 );

        int m = names.size();

        vi per;
        sorted_permutation( prices, per );

        vs seq;
        for ( int i = 0; i < m; ++i )
            seq.push_back( names[per[i]] );

        vvi p( m + 1, m + 1 );
        vector< vector< vs > > q( m + 1, vector< vs >( m + 1 ) );

        for ( int i = 1; i <= m; ++i ) {
            for ( int j = 1; j <= m; ++j ) {
                if ( names[i - 1] == seq[j - 1] ) {
                    p[i][j] = p[i-1][j-1] + 1;
                    q[i][j] = q[i-1][j-1];
                    q[i][j].push_back( names[i-1] );
                    sort( all( q[i][j] ) );
                } else {
                    if ( p[i-1][j] < p[i][j-1] || p[i-1][j] == p[i][j-1] && q[i-1][j] < q[i][j-1] ) {
                        p[i][j] = p[i][j-1];
                        q[i][j] = q[i][j-1];
                    } else {
                        p[i][j] = p[i-1][j];
                        q[i][j] = q[i-1][j];
                    }
                }
            }
        }

        sort( all( names ) );

        vs res;
        set_difference( all( names ), all( q[m][m] ), std::back_inserter( res ) );

        copy( all( res ), ostream_iterator< string >( out, " " ) );
        out << endl;
    }
}