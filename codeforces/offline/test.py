#!/usr/bin/env python

init_jupyter()
from chdrft.cmds import CmdsList
from chdrft.main import app
from chdrft.utils.cmdify import ActionHandler
from chdrft.utils.misc import Attributize
import chdrft.utils.misc as cmisc
from chdrft.utils.misc import Attributize as A
import glog
import chdrft.utils.Z as Z
import chdrft.utils.K as K
import numpy as np
from pydantic import Field

global flags, cache
flags = None
cache = None


def args(parser):
  clist = CmdsList()
  ActionHandler.Prepare(parser, clist.lst, global_action=1)


def test(ctx):
  pass


mu = Z.opa_math.MathUtils(100)


def f1(n, k):
  cnt = 0
  for x in Z.itertools.product(range(k), repeat=n):
    cnt += k == len(set(x))
  return cnt


def f2(n, k):
  cnt = 0
  for i in range(k + 1):
    cnt += (k - i)**n * mu.cnk(k, i) * (-1)**i
  return cnt


Z.Cachable.ResetCache()
@Z.Cachable.cachedf()
def s2(n, k):
  if k > n: return 0
  if k < 0: return 0
  if n == 0: return 1
  return s2(n - 1, k - 1) + k * s2(n - 1, k)


def g1(n, k):
  cnt = 0
  for x in Z.itertools.product(range(k), repeat=n):
    d = cmisc.defaultdict(lambda: [n, -1])
    for i, a in enumerate(x):
      d[a][0] = min(d[a][0], i)
      d[a][1] = max(d[a][1], i)
    if len(d) != k: continue
    for v in range(1, k):
      if d[v - 1][0] > d[v][1]:
        break
    else:
      cnt += 1
  return cnt


def g2(n, k):
  tot = s2(n, k) * mu.fact[k]
  print()
  print(n,k,tot)
  for kx in range(2, k + 1):
    sgn = (-1)**(kx - 1)
    fx = (k - kx + 1)
    s = 0
    for m in range(kx, n + 1):
      #s += mu.cnk(n - 1, kx - 1) * mu.cnk(n, m) * (k - kx)**(n - m)
      s += mu.cnk(m - 1, kx - 1) * mu.cnk(n, m) * mu.fact[k-kx] * s2(n-m, k-kx)
    print(kx, sgn, fx, s)
    tot += sgn * fx * s
  return tot


for i in range(1, 6):
  for j in range(1, i + 1):
    print((i, j), g1(i, j), g2(i, j))

for i in range(1, 7):
  for j in range(1, i + 1):
    print(f2(i, j))


def main():
  ctx = Attributize()
  ActionHandler.Run(ctx)


app()
