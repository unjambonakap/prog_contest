#!/usr/bin/env python
# coding: utf-8

# In[1]:


init_jupyter()


# In[2]:


from sage.all import *


# In[70]:


x,f = var('x f')
a = (f-1) / ((1-x) * (f-exp(x*(f-1))))
u = var('u')

a =a.subs(x==u/(f-1))
ap = a.partial_fraction_decomposition(f)
print(ap)
tl = [A(term=f - exp(u), rem=exp(u)), A(term=f-u-1, rem=(u+1))]
for i, tx in enumerate(tl):
    px = ap[i]
    mul = -tx.rem
    v= 1/tx.rem
    g = u * (v - 1)
    fx=var('fx')
    ff = solve(g.function(u.function(x)) ==x, u)[0].rhs()
    print()
    print(ff)
    rem = px * tx.term
    print(rem.subs(u==ff).full_simplify())


# In[64]:


g


# In[44]:


solve(u==g, g)


# In[49]:


g.function(u)


# In[47]:


tmp = lambda u: 1 / (u+1) - 1
solve(tmp(u) == f, u)


# In[26]:


tl[0].term


# In[20]:





# In[14]:


a

