#!/usr/bin/python 


def pgcd(a,b):
    if b==0:
        return a
    else:
        r=a%b
        return pgcd(b,r)

def ppcm(a,b):
    return abs(a*b)/pgcd(a,b)

def is_impossible(k,x1,x2,y1,y2,t1,t2):
    return t1==t2 and x1-x2 != y1-y2

def cycle(x, t):
    return 1 if x==t else (x+1)
    
def basic_timer(k,x1,x2,y1,y2,t1,t2):
    if is_impossible(k,x1,x2,y1,y2,t1,t2):
        return -1
    n = 0
    while k!=0:
        x1 = cycle(x1, t1)
        x2 = cycle(x2, t2)
        n += 1
        if x1 == y1 and x2 == y2:
            k -= 1
    return n

def optimized_timer(k,x1,x2,y1,y2,t1,t2):
    if is_impossible(k,x1,x2,y1,y2,t1,t2):
        return -1
    n = basic_timer(1,x1,x2,y1,y2,t1,t2)
    size_cycle = ppcm(t1,t2)
    return n+(k-1)*size_cycle

while True:
    k,x1,x2,y1,y2,t1,t2 = ( int(x) for x in raw_input().split() )
    print k,x1,x2,y2,t1,t2
    if (k,x1,x2,y1,y2,t1,t2) == (0,0,0,0,0,0,0):
        break
    else:
        print optimized_timer(k,x1,x2,y1,y2,t1,t2)


