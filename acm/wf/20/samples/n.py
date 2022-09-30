#!/usr/bin/env python

from chdrft.cmds import CmdsList
from chdrft.main import app
from chdrft.utils.cmdify import ActionHandler
from chdrft.utils.misc import Attributize as A
import chdrft.utils.misc as cmisc
import glog
import chdrft.utils.Z as Z
import numpy as np
from scipy.spatial.transform import Rotation as R

global flags, cache
flags = None
cache = None


def args(parser):
  clist = CmdsList()
  ActionHandler.Prepare(parser, clist.lst, global_action=1)



def test(ctx):
  d, n= list(map(int, input().split(' ')))
  tb = []
  for i in range(n):
    v= list(map(float, input().split(' ')))
    tb.append(A(vec=np.array(v[:-1]), l=v[-1]))


  vl = []
  c = tb[0].l**2
  p0 = tb[0].vec
  sol = np.array([1,2,3,4])
  for i in range(1, n):
    if len(vl) == d: break
    p1 = tb[i].vec
    p01 = p1-p0
    for vx in vl:
      p01  -= vx * np.dot(p01, vx)
    np1 = p0 + p01
    nx = tb[i].l ** 2 - np.linalg.norm(np1-p1)**2
    nd = np.linalg.norm(p01)

    # lrem1**2 + (a*dist)**2 ==  c1**2
    # lrem1**2 + ((1-a)*dist)**2 ==  c2**2
    # -> 1
    alpha = (((c - nx)/nd**2+1)/2)
    c -= alpha**2 *  nd**2
    vl.append(p01/nd)
    p0 = p0 + p01 * alpha

  if len(vl) == d:
    res = p0
  else:
    res = np.random.random(d)
    for vx in vl:
      res -= vx * np.dot(res, vx)

    res = p0 + res * c**0.5 / np.linalg.norm(res)


  for i in res: print(i, end=' ')
  print()

def main():
  ctx = A()
  ActionHandler.Run(ctx)


app()
