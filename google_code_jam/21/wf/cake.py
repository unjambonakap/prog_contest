#!/usr/bin/env python
from collections import defaultdict
from fractions import Fraction
import numpy as np


def sgn(x):
  if x < 0: return -1
  return x > 0


class QuadPoly:

  def __init__(self, a=0, b=0, c=0):
    self.a = a
    self.b = b
    self.c = c

  def __add__(self, peer):
    return QuadPoly(self.a + peer.a, self.b + peer.b, self.c + peer.c)

  def __mul__(self, k):
    return QuadPoly(self.a * k, self.b * k, self.c * k)

  def __neg__(self):
    return QuadPoly(-self.a, -self.b, -self.c)

  def shift(self, x):
    return self + QuadPoly(0, 2 * self.a * x, self.a * x**2 + self.b * x)

  def __call__(self, x):
    return self.a * x**2 + self.b * x + self.c

  def __repr__(self):
    return f'({self.a}, {self.b}, {self.c})'

  def get_abs_min(self, x0, x1):
    if sgn(self(x0)) != sgn(self(x1)):
      return 0
    if self.a != 0:
      xx = -self.b / 2 / self.a
      if xx >= x0 and xx <= x1: 
        v = self(xx)
        if sgn(v) != sgn(self(x0)): return 0
        return self(xx)
    return self(x0)


def get_tr1(x, y):
  return QuadPoly(Fraction(y, x * 2), 0, 0)


def get_tr2(x, y):
  return QuadPoly(-Fraction(y, x * 2), Fraction(y), 0)


def solve(p1, p2, xyab):
  xl = set()
  area = Fraction(abs(p1[0] * p2[1] - p1[1] * p2[0]), 2)
  if p1[0] > p2[0]: p1, p2 = p2, p1
  vecs = []
  if p1[0] == 0:
    vecs.append(((0, p2[0]), get_tr2(p2[0], abs(p1[1]))))
  elif p2[0] == p1[0]:
    vecs.append(((0, p2[0]), get_tr1(p2[0], abs(p2[1] - p1[1]))))
  else:
    ip = Fraction(p2[1]) / p2[0] * p1[0]
    vecs.append(((0, p1[0]), get_tr1(p1[0], abs(ip - p1[1]))))
    vecs.append(((p1[0], p2[0]), get_tr2(p2[0] - p1[0], abs(ip - p1[1]))))

  events = defaultdict(list)

  for e in xyab:
    x = e[0]
    xl.add(x)
    xl.add(x + p1[0])
    xl.add(x + p2[0])

    df = e[2] + e[3]
    for rx, poly in vecs:
      np = poly.shift(-(x + rx[0]))
      np = np * df
      events[x + rx[0]].append(np)
      events[x + rx[1]].append(-np + QuadPoly(c=np(x + rx[1])))

  sumb = sum(x[3] for x in xyab)
  state = QuadPoly(c=-sumb * area)
  res = Fraction(abs(state(0)))

  def compute_res(v):
    return min(abs(v), res)

  last_x = 0
  for x in sorted(xl):
    if x != last_x:
      res = compute_res(state(x))
      res = compute_res(state(last_x))
      res = compute_res(state.get_abs_min(last_x, x))

    for q in events[x]:
      state = state + q
    last_x = x

  res = Fraction(res) / area
  return (res.numerator, res.denominator)


def read_int_list():
  return list(map(int, input().split()))


def main():
  tn, = read_int_list()
  for ti in range(tn):
    n, nx, ny = read_int_list()
    x1, y1, x2, y2 = read_int_list()
    xyab = [read_int_list() for i in range(n)]
    score = solve((x1, y1), (x2, y2), xyab)
    print(f'Case #{ti+1}: {score[0]}/{score[1]}')


main()
