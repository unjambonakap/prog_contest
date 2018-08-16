# -*- coding: utf-8 -*-

def possible(D, messages):
    if D < 0:
        return False
    
    first = messages[0]
    # a and b are leftmost and rightmost positions at the previous message
    a = first[1] - D
    b = first[1] + D
    last = first[0]
    for T, P in messages[1:]:
        time = T - last
        a -= time
        b += time
        a = max(a, P - D)
        b = min(b, P + D)
        if a > b:
            return False
        last = T
    return True
        
    
import sys
fin = sys.stdin
T = int(fin.readline())
for case in range(1,T+1):
    N = int(fin.readline())
    messages = []
    for i in range(N):
        P, T = map(int, fin.readline().split())
        messages.append((T,P))
    messages.sort()
    
    a = -1
    b = 2*10**9
    # a and b are limits, inclusive
    # b always possible, a never possible
    while b - a > 1:
        guess = (a+b)/2
        if possible(guess, messages):
            b = guess
        else:
            a = guess
    if possible(b-0.5, messages):
        b -= 0.5
    
    print "Case #%d: %s" % (case, b)
