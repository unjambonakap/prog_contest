#!/usr/bin/env python
# coding: utf-8

# In[1]:


init_jupyter()


# In[105]:




def analyse(nround, npot, nsame):
  free_cnt = [0] * npot
  mu = Z.opa_math.MathUtils(nround+1)

  nboost = 0
  for i in range(nboost):
    free_cnt[i] = (nround - npot) // nboost

  fcache = Z.opa_cache.FilelessCacheDB()
  fcache.__enter__()

  @Z.Cachable.cachedf(alt_key=f'2KEY_{0}_{npot}_{nround}')
  def go(rempos, rem, minv):
    if rempos == 0:
      return int(rem == 0)

    free = 0
    for i in range(rempos):
      free += free_cnt[i]

    if rempos * minv > rem + free: return 0
    res = 0

    cur_free = free_cnt[rempos - 1]
    for v in range(minv, rem + cur_free+1):
      need = v - cur_free
      if need < 0: continue
      res += go(rempos - 1, rem - need, minv) * mu.cnk(rem, need)
    return res

  x = 0
  
  for u in range(1, nsame+1):
    for minv in range(nround // npot + 1):
      rem = nround - u* minv
      if rem < 0: continue
      px = go(npot - u, rem, minv+1)
      x += px *  mu.cnk(npot, u) * mu.fact[nround] // mu.fact[rem] // (mu.fact[minv] ** u)
  #x = go(npot, nround, 0)
  x /= (npot**nround)
  x *= (1-1/npot) ** (nsame-1)
  print(x)
  print(free_cnt)


# In[108]:


print(i, analyse(195, 20, 3))


# In[65]:


for i in range(3, 10):
  print(i, analyse(99, 20, i))

