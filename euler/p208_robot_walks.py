#!/usr/bin/env python

from chdrft.cmds import CmdsList
from chdrft.main import app
from chdrft.utils.cmdify import ActionHandler
from chdrft.utils.misc import Attributize
import glog
from collections import defaultdict

global flags, cache
flags = None
cache = None


def args(parser):
  clist = CmdsList().add(test)
  ActionHandler.Prepare(parser, clist.lst)
  parser.add_argument('--n', type=int, default=35)


vec = [[1, 5, [10, -2, 0, 0, 0, 0, 2, 0]],
       [1, 2, [-10, 2, 0, 0, 0, 0, 2, 0]],
       [2, 1, [-10, 2, 0, 0, 0, 0, 2, 0]],
       [2, 3, [0, -4, 0, 0, 0, 0, -3, 1]],
       [3, 2, [0, -4, 0, 0, 0, 0, -3, 1]],
       [3, 4, [0, 0, 0, 0, 0, 0, 2, -2]],
       [4, 3, [0, 0, 0, 0, 0, 0, 2, -2]],
       [4, 5, [0, 4, 0, 0, 0, 0, -3, 1]],
       [5, 4, [0, 4, 0, 0, 0, 0, -3, 1]],
       [5, 1, [10, -2, 0, 0, 0, 0, 2, 0]],]

actions = defaultdict(lambda: [])
for src, dst, v in vec:
  actions[src].append((dst, v))


def add(a, b):
  return tuple([x + y for x, y in zip(a, b)])


def test(ctx):
  zpos = tuple([0] * len(vec[0][2]))
  state = (1, zpos)
  cur = {state: 1}
  for step in range(flags.n):
    print('ON >> ', step, len(cur))
    nxt = defaultdict(lambda: 0)
    for (pos, v), count in cur.items():
      for npos, dv in actions[pos]:
        nstate = (npos, add(v, dv))
        nxt[nstate] += count
    cur = nxt

  tot = 0
  for i in range(1, 6):
    tot += cur[(i, zpos)]
  print(tot)


def main():
  ctx = Attributize()
  ActionHandler.Run(ctx)

# could do meet in the middle
#331951449665644800

app()
