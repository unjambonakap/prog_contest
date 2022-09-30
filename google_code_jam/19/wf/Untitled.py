#!/usr/bin/env python
# coding: utf-8

# In[1]:


init_jupyter()


# In[11]:


import itertools
n = 50
can_pick = 4
mod = n-1
lst = list(range(mod))
def analyse(choice):
  inf = n+1
  tb = [inf] * len(lst)
  q = Z.Queue()
  tb[0] = 0
  q.put(0)
  while not q.empty():
    a = q.get()
    cost = tb[a] + 1
    for c in choice:
      nv  = (a+c)%mod
      if tb[nv] > cost:
        tb[nv] = cost
        q.put(nv)
  
  return max(tb)

best = n
for x in itertools.combinations(lst, can_pick):
  cnd = analyse(x)
  if cnd < best:
    best = cnd
    print(best, x)
  
  
  


# In[ ]:


best

