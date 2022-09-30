#!/usr/bin/env python
from collections import defaultdict
from fractions import Fraction
import numpy as np

class MathUtils:

  def __init__(self, n, mod=None, pw=1):
    self.n = n
    self.mod = mod
    self.fact = [1] * (n + 1)
    self.ifact = [1] * (n + 1)
    self.isp = set()
    self.pw = pw

    for i in range(1, n + 1):
      self.fact[i] = self.fact[i - 1] * (i ** self.pw)
      if mod is not None:
        self.fact[i] %= mod

    if mod is None:
      self.ifact = None
    else:
      for i in range(1, n + 1):
        self.ifact[i] = gmpy2.invert(self.fact[i], mod)

  def cnk(self, n, k):
    if n < k or k < 0: return 0
    if self.mod is not None:
      return self.fact[n] * self.ifact[k] % self.mod * self.ifact[n - k] % self.mod
    return self.fact[n] // self.fact[k] // self.fact[n - k]

kMA  = MathUtils(130)

def get_typ(xl):
  n = len(xl)
  if all(x == xl[0] for x in xl): return 0
  if n == 2: return 1
  if xl[0] == xl[1]: return 3
  if xl[0] == xl[2]: return 2
  return 1

def solve(tb):
  ans, scores = zip(*tb)
  n = len(ans)
  q = len(ans[0])

  typ2pos = defaultdict(list)
  for i in range(q):
    xl = [x[i] for x in ans]
    t = get_typ(xl)
    typ2pos[t].append(i)

  ntyp = 2**(n-1)
  nl = [len(typ2pos[i]) for i in range(ntyp)]
  outcomes = []
  if n == 3:
    for i in range(nl[0]+1):
      m = []
      m.append([1, 0, 0,0, i])
      m.append([1,1,-1,-1, scores[0]-nl[2]-nl[3]])
      m.append([1,-1,1,-1, scores[1]-nl[1]-nl[3]])
      m.append([1,-1,-1,1, scores[2]-nl[1]-nl[2]])
      m = np.array(m)
      try:
        sol=np.linalg.solve(m[:,:-1], m[:,-1])
        sol = np.round(sol).astype(int)
        cnt = 1
        if not np.all(sol >= 0): continue
        if not np.all(sol <= nl): continue
        for cx, nx in zip(sol, nl):
          cnt *= kMA.cnk(nx, cx)
        sol =list(map(int, np.round(sol)))
        outcomes.append((sol, cnt))

      except:
        pass

  elif n == 2:
    nt= len(typ2pos[0])
    n1= len(typ2pos[1])
    diff = scores[1] - scores[0]
    #n00 + n01 = sc0
    # n00 + (n1-n01) = sc1
    n00 = (scores[0] + scores[1] - n1) // 2
    n01 = scores[0] - n00
    outcomes.append([(n00, n01), 1])
  else:
    outcomes.append([(scores[0], ), 1])


  res = Fraction(0)
  tot = sum(x[1] for x in outcomes)
  typ_val = dict()
  for i in range(ntyp):
    if nl[i] == 0: continue
    p = Fraction(0)
    for vals, cnt in outcomes:
      a = Fraction(vals[i] * cnt, nl[i])
      p = p+a
    p = p / tot
    if p*2 < 1:
      typ_val[i] = 0
      res += nl[i] * (1-p)
    else:
      typ_val[i] = 1
      res += nl[i] * p

  sx = ''
  for i in range(q):
    xl = [x[i] for x in ans]
    t = get_typ(xl)
    v=xl[max(t-1, 0)]
    if not typ_val[t]:
      v = 'F' if v == 'T' else 'T'
    sx += v


  return sx, (res.numerator, res.denominator)

def main():
  tn = int(input())
  for ti in range(tn):
    n, q = list(map(int, input().split()))
    tb = []
    for i in range(n):
      vals, sc = input().split()
      tb.append((vals, int(sc)))

    sol, score = solve(tb)
    print(f'Case #{ti+1}: {sol} {score[0]}/{score[1]}')

main()
