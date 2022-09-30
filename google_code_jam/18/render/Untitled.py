#!/usr/bin/env python
# coding: utf-8

# In[4]:


init_jupyter()


# In[6]:


oplt.plot([A(misc=[A(text='123', pos=(0,0))])])


# In[31]:


def render(t):
  elems = A(misc=[], lines=[])
  for i, x in enumerate(t.edges):
    
    elems.misc.append(A(text=str(i+1), pos=(x[0] + x[1])/2))
    elems.lines.append(x)
  
  oplt.plot([elems])
            


# In[40]:


import re
text = open('../r3/fake.in', 'r').read().strip()
ints = iter(map(int, re.split('\s', text, flags=re.MULTILINE)))

tests = []
nt = next(ints)
for i in range(nt):
  t = A()
  tests.append(t)
  nf, k = next(ints), next(ints)
  t.edges = []
  for j in range(nf):
    pl = np.array([(next(ints), next(ints)), (next(ints), next(ints))])
    t.edges.append(pl)

render(tests[0])


# In[33]:




