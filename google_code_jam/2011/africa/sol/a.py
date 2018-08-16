# PROBLEM A

from decimal import *

# return ternary representation of x
def ternary(x):
    digits = []
    xvals = set()
    while x not in xvals and len(digits) < 60:
        xvals.add(x)
        y = x*3
        r = int(y)
        digits.append(r)
        x = y-r
        #print x, y, r
        #print r, sorted(xvals)
    return digits, 0 in xvals

# return cantor step at which x is excluded from cantor set, or None if member of cantor set
def cantor(x):
    t, term = ternary(x)
    try:
        p = t.index(1)
        if p == len(t)-1 and term:
            return None
        else:
            return p
    except ValueError:
        return None

# given list of numbers
def solve(nums):
    clist = []
    dvals = []
    for num in nums:
        p = cantor(num)
        print num, cantor(num), ternary(num)
        if p is None:
            clist.append(num)
        else:
            dvals.append((p,num))
    dvals.sort()
    clist.sort()
    return [n for p,n in dvals] + clist

import sys, copy, os
f = open(sys.argv[1])
out = open(os.path.splitext(sys.argv[1])[0] + '.out', 'w')
T = int(f.readline())

#print ternary(Decimal('0.30001'))
#print ternary(Decimal('0.33'))
#sys.exit(0)

for case in range(1, T+1):
    N = int(f.readline())
    nums = [ Decimal(f.readline()) for q in range(N) ]
    result = solve(nums)
    #print result
    out.write('Case #{0}:\n'.format(case))
    for n in result:
        out.write('{0!s}\n'.format(n))

out.close()
