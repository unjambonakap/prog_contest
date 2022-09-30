#!/usr/bin/env python

from chdrft.cmds import CmdsList
from chdrft.main import app
from chdrft.utils.cmdify import ActionHandler
from chdrft.utils.misc import Attributize
from chdrft.utils.path import FileFormatHelper
import glog

global flags, cache
flags = None
cache = None


def args(parser):
  clist = CmdsList().add(check_float)
  ActionHandler.Prepare(parser, clist.lst)
  parser.add_argument('--file1', type=FileFormatHelper.Read)
  parser.add_argument('--file2', type=FileFormatHelper.Read)
  parser.add_argument('--precision', type=float)
  parser.add_argument('--multiline', action='store_true')
  parser.add_argument('--no-check', action='store_true')


def compare(ctx, a, b):
  a = a.strip()
  b = b.strip()
  n1 = float(a)
  n2 = float(b)
  diff = abs(n1-n2)
  glog.info('Comparing %s %s', n1, n2)
  return (diff <=  ctx.precision) or (abs(n1-n2) / max(abs(n1), abs(n2)) <= ctx.precision)

def check_float(ctx):
  if ctx.no_check: return 0
  if ctx.multiline:
    for a, b in zip(ctx.file1.splitlines(), ctx.file2.splitlines()):
      assert compare(ctx, a,b)
  else:
    compare(ctx, ctx.file1, ctx.file2)


def main():
  ctx = Attributize()
  ActionHandler.Run(ctx)


app()
