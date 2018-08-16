/*
 * Solution to "Handwritten arithmetic"
 * Enrique Martin
*/

#include <iostream>
#include <cctype>
#include <algorithm>
using namespace std;

const int MAXVAR = 5;

typedef struct expr{
  char op;
  int* v;
  expr* izq;
  expr* der;
} expr;

int values[MAXVAR];
string expression;

expr* parseExpression(const string expression, int &pos, int &nvar)
{
  expr *ret = NULL;
  
  if( expression[pos] == '(' )
  {
    ret = new expr;
    pos++;
    ret->izq = parseExpression( expression, pos, nvar);
    ret->op = expression[pos];
    pos++;
    ret->der = parseExpression( expression, pos, nvar);
    pos++; //Para comerse el ')'    
  }
  else if (islower(expression[pos]))
  {
    ret = new expr;
    ret->v = values + nvar;
    ret->izq = ret->der = NULL;
    pos++;
    nvar++;
  }
  else
  {
    throw "Invalid Expression";
  }
  
  return ret;
}

int evalExpression( expr* e )
{
  int res = -1;
  
  if( (e->izq == NULL) && (e->der == NULL) )
  {
    res = *(e->v);
  }
  else
  {
    int v1 = evalExpression(e->izq);
    int v2 = evalExpression(e->der);
    switch (e->op)
    {
    case '+': res = v1 + v2; break;
    case '-': res = v1 - v2; break;
    case '*': res = v1 * v2; break;
    }
  }
  
  return res;
}


void freeExpr( expr* &e)
{
  if( e->izq != NULL ) freeExpr(e->izq);
  if( e->der != NULL ) freeExpr(e->der);
  delete e;
}

void showExpression( expr* e )
{
  if( (e->izq == NULL) && (e->der == NULL) )
  {
    cout << "V";
  }
  else
  {
    cout << '(';
    showExpression( e->izq);
    cout << e->op;
    showExpression( e->der);
    cout << ')';
  }
}

int main()
{
  expr* e;
  int pos = 0, nvar = 0;
  /*values[0] = 1;
  values[1] = 2;
  values[2] = 3;
  values[3] = 4;
  values[4] = 5;
  cin >> expression;
  while( expression != "")
  {
    e = parseExpression(expression,pos,nvar);
    showExpression(e);
    cout << "= " << evalExpression(e) << endl;
    
    cin >> expression;
    pos = nvar = 0;
  }*/
  int n, result, act;
  bool possible;

  /*cout << n << " ";
  for( int i = 0; i < n; ++i )
  {
    cout << values[i] << " ";
  }
  cout << result << endl;*/
  
  while( true )
  {
    cin >> n;
    for( int i = 0; i < n; ++i )
    {
      cin >> values[i];
    }
    sort(values, values+n);
    cin >> result;
    
    if( (n == 0) && (result == 0) )
      break;
  
    cin >> expression;
    pos = nvar = 0;
    e = parseExpression(expression,pos,nvar);
    //cout << "<" << expression << ">" << endl;
    
    possible = false;
    do
    {
      act = evalExpression(e);
      if (act == result)
      {
        possible = true;
      }
    } while( !possible && next_permutation(values,values+n));
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;
    freeExpr(e);
  }
  
  return 0;
}
