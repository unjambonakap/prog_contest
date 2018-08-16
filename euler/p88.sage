

def euler_p88():
  maxk= 12012
  res=0
  di
  for i in range(2,maxk):
    s1 = 0
    cnt = 0
    for f in list(factor(i)):
      s1 += f[0] * f[1]
      cnt +=0 
    if i-s1 <=12000: res+=1
  print(res)

def euler_p228():
  (low, high) = (1864, 1909)
  (low, high) = (3, 4)
  s = set()
  for i in range(low, high+1):
    for k in range(i):
      m = 2*k
      d = gcd(m, i)
      s.add((m / d, i / d))
  print(len(s))

euler_p228()


