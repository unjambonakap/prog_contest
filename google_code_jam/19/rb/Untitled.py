#!/usr/bin/env python
# coding: utf-8

# In[1]:


init_jupyter()


# In[14]:



def test(n1, n2):
  uj = Z.graph_base.UnionJoinLax()
  for i in range(n1*n2):
    i1 = i % n1
    i2 = i % n2
    uj.join(i1, n1+i2)
    cx = uj.cnt(i1)
    print(i, cx)
    if cx == n1 + n2: break
    
    
test(9, 4)


# In[ ]:




