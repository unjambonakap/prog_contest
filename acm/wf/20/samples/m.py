#!/usr/bin/env python
import gmpy2
import sys

def findit(a,b,mod):
  # ax = b (mod)
  if a == 0:
    if b==0: return 1
    return -1
  da = gmpy2.gcd(a,mod)
  db = gmpy2.gcd(b,mod)
  if db%da!=0: return -1
  ar = a // da
  br = b // db
  if db==mod:
    br=1
  return gmpy2.invert(ar, mod) * br * (db//da) % mod

def main():
  b,d,a = list(map(int, input().split(' ')))

  def checkit(a, b, cnt):
    mod = 10 ** cnt
    if d == 0:
      x = b
      cnt2 = 0
      cnt5 = 0
      while x % 2 == 0:
        x//=2
        cnt2 += 1
      while x % 5 == 0:
        x//=5
        cnt5 += 1
      if cnt < min(cnt2,cnt5) : return True
      fv = 2 ** max(0, cnt-cnt2) * 5 ** max(0, cnt-cnt5)
    else:
      target = int(str(d)*cnt)
      dd = gmpy2.gcd(b, mod)
      if target % dd != 0: return False
      target //= dd
      mod //= dd
      nb = b // dd
      ia = gmpy2.invert(nb, mod)
      fv = ia * target % mod
    if b * fv <= a:
      return True
    return False

  best=0
  T=1
  H = 10000
  while T<=H:
    M = (T+H)//2
    if checkit(a, b,M):
      T = M+1
      best = M
    else:
      H = M-1
  print(best)


main()
