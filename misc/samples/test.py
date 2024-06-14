#!/usr/bin/env python

from chdrft.cmds import CmdsList
from chdrft.main import app
from chdrft.utils.cmdify import ActionHandler
from chdrft.utils.misc import Attributize
import chdrft.utils.misc as cmisc
from chdrft.utils.misc import Attributize as A
import glog
import chdrft.utils.Z as Z
import numpy as np
from pydantic import Field
from sage.all import *

global flags, cache
flags = None
cache = None


def args(parser):
  clist = CmdsList()
  ActionHandler.Prepare(parser, clist.lst, global_action=1)


mod = 998244353


def cx(n):
  return binomial(2 * n, n) // (n + 1)


def count_open(seq):
  cnt = 0
  no = 0
  for c in seq:
    if not c: no += 1
    elif c: no -= 1
    if no < 0: return -1
  return no


def en1(n):
  cnt = 0
  for s in Z.itertools.product(range(3), repeat=2 * n):
    n2 = len([x for x in s if x == 2])
    n0 = len([x for x in s if x == 0])
    n1 = len([x for x in s if x == 1])

    rem = n2 - abs(n0 - n1)
    if rem < 0: continue
    n20 = rem // 2 + max(0, n1 - n0)
    no = 0

    ns = []
    for c in s:
      if c == 2:
        ns.append(n20 <= 0)
        n20 -= 1
      else:
        ns.append(c)

    cnt += count_open(ns) == 0

  return cnt


def en2(n, k):
  cnt = 0
  for s in Z.itertools.product(range(2), repeat=2 * n + k):
    if count_open(s) == k: cnt += 1
  return cnt


def getk(x, k):
  c2 = (1 - sqrt(1 - 4 * x * x)) / (2 * x * x)
  c = (1 - sqrt(1 - 4 * x)) / (2 * x)
  d = sqrt(1 - 4 * x)
  b = 1 / d
  a = -b
  y1 = (1 - d) / (2 * x)
  y2 = (1 + d) / (2 * x)
  iy1 = 2 * x / (1 - d)
  iy2 = 2 * x / (1 + d)
  ca = x
  va = (a * -1 / y1 * (1 / y1)**k)
  vb = (b * -1 / y2 * (1 / y2)**k)
  print()
  print(va[:10], vb[:10])
  print(iy2)
  print(iy1)
  tmp = c / ca * (a * -(iy1**(k + 1)) + b * -(iy2**(k + 1)))
  tmp = tmp - 1 / x
  v = tmp
  print(k, v[:10])
  for i in range(k + 1):
    v = v.derivative()
  print(k, v[:10])
  for i in range(k + 1):
    v = v.integral()
  print(k, v.coefficients(10))
  print(v[0], v[6])
  print(v)
  print('xxx')
  return v
  return tmp


def en12(n):
  s = 0
  R, (x,) = LazyLaurentSeriesRing(QQ, names=['x']).objgens()
  for k in range(n + 1):
    gk = getk(x, k)
    print('>>>', gk[:10])
    a = (x * gk.derivative() + k * gk) / 2
    print(gk.coefficients(2 * n), a[:10])
    sa = (a**2).coefficient(2 * n)
    print(n, k, sa)
    s += sa
  return s / (2 * n)


def find_p_rec(seq):
  cnds = []
  for order in range(0, 4):
    for deg in range(0, 4):
      sz = (order + 1) * (deg + 1) - 1
      cnds.append((sz, order, deg))
  cnds.sort()

  for sz, order, deg in cnds:
    nx = len(seq) - order
    mat = matrix.zero(QQ, nx, sz)
    vec = matrix.zero(QQ, nx, 1)
    if sz >= nx: continue
    for i in range(nx):
      pos = 0
      for io in range(order + 1):
        for id in range(deg + 1):
          if io == 0 and id == deg: continue

          if io == order + 1:
            v = 1
          else:
            v = seq[i + order - io]
          mat[i, pos] = v * (i + 1)**id
          pos += 1
      vec[i] =  seq[i+order] * (i + order) ** deg
    try: 
      res = mat.solve_right(vec)
      return (order, deg, mat, res)
    except ValueError:
      continue



def test2(ctx=None):
  #tb = [en2(i, 0) for i in range(13)]
  #tb = [en1(i) for i in range(8)]
  tb = [1,1,5,36,253,1833,13939,109438,875127,7088511]
  print(tb)

  print(find_p_rec(tb))
  return

  R, (x,) = LazyLaurentSeriesRing(QQ, names=['x']).objgens()
  print(getk(x, 5)[:20])
  print(getk(x, 4)[:20])
  print(getk(x, 0)[:20])
  print(en2(4, 4))
  print(en2(5, 4))
  print(en2(0, 4))

  print('\n\n\n')
  print(en12(4))
  print(en1(4))

  return
  a = 1 / (1 - x)
  print(a.coefficient(10))
  u = (1 - sqrt(1 - 4 * x**2)) / (2 * x)
  print(u.coefficient(5))
  print(cx(5))

  e = u * u * x**2 / (1 - (1 - x)**2)
  print(en1(2))
  print(en2(5, 2))
  print(cx(2))
  #print(help(e.coefficient))
  return


@Z.Cachable.cachedf(key_serializer=lambda name, args, kwargs: tuple(name) + tuple(args))
def dp1(n, k):
  if k == -1: return 1
  res = 0
  for cnt in range(0, n + 1, 2**k):
    res += dp1(n - cnt, k - 1)
  return res % mod


@Z.Cachable.cachedf(key_serializer=lambda name, args, kwargs: tuple(name) + tuple(args))
def dp2(n, k, c):
  if k == 0: return 1
  res = 0
  for i in range(2 * n, c // (2**(k - 1))):
    res += dp2(i, k - 1, c)
  return res % mod


def solve1(n, k):
  n -= 2**(k - 1)
  if n < 0: return 0
  return dp1(n, k - 1)


def solve2(n, k):
  n -= 2**(k - 1)
  if n < 0: return 0
  mp, (x,) = GF(mod)['x'].objgens()
  f = mp.quotient(x**(n + 1))
  x = f.gen()
  p = 1
  p = (1 - x)
  for kk in range(k):
    p = p * (1 - x**(2**kk))
  p = 1 / p

  return p[n]


def test(ctx):

  tb = []
  kk = 5
  #print(solve2(200, kk))
  #return
  c = 2000

  print(solve1(50, 5))
  print(f'{solve1(30, 3)=}')
  print(f'{solve1(50, 3)=}')
  print(f'{solve1(8, 2)=}')
  print(f'{solve1(16, 2)=}')
  return

  if 0:
    for nn in range(1, 30):
      tb.append((nn, dp2(nn, kk, c)))

  else:

    for nn in range(1, 30):
      tb.append((nn, solve2(c - nn * 2**(kk - 1), kk)))

  print(tb)
  print(np.array(tb)[:, 1][::2])

  mp, (x,) = GF(mod)['x'].objgens()
  res = mp.lagrange_polynomial(tb)
  print(res)
  return

  for n, k in [(6, 3), (5, 1), (129, 5)]:

    print(solve1(n, k), solve2(n, k))

  pass


def main():
  ctx = Attributize()
  ActionHandler.Run(ctx)


app()
