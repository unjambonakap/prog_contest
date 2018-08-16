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



def check_float(ctx):
  n1 = float(ctx.file1)
  n2 = float(ctx.file2)
  diff = abs(n1-n2)
  glog.info('Comparing %s %s', n1, n2)
  return (diff <=  ctx.precision) or (abs(n1-n2) / max(abs(n1), abs(n2)) <= ctx.precision)


def main():
  ctx = Attributize()
  ActionHandler.Run(ctx)


app()
