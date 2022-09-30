#!/usr/bin/env python



s = int(input())
v = 1
pos = 1
while s!=v:
  pos += 1
  v = v * pos
print(pos)
