#!/usr/bin/env python
# coding: utf-8

# In[1]:


init_jupyter()


# In[11]:


np.cross(pts[2] - pts[1], pts[3]-pts[1])


# In[12]:


pts=((6, -8),(2, 10),(-10, 9),(9, -2),(4, -5),(-6, -5),(-10, 0),(-10, -10),(9, 3),(4, -2),(4, -3),(2, 6))
hull = (7,6,2,1,8)

hull=(0,3,11)
pts=((-1, -3),(6, -6),(6, -5),(0, 10),(7, -7),(5, -2),(3, 8),(0, 3),(4, 9),(0, -8),(0, 0),(10, 10))
pts=((-134609572, -33320739),(256869808, 514774082),(766390428, 377679261),(159132460, 642838292),(86456114, 738065337),(68301800, 761852742),(154060050, 649484617),(212984598, 572276407),(-546732557, 726006041),(184699148, 609338532),(216738368, 567357882),(-756609572, 781679261))
hull = []
pts = [
(171660044, -451242935),
(398170002, -317995243),
(391975929, -321761197),
(173322059, -450266153),
(172187199, -450933121),
(175116134, -295243043),

      ]

pts = np.array(pts) 




pts_hull = [(pts[hull[i]], pts[hull[i+1]]) for i in range(len(hull)-1)]


    

























data = A(points=pts, lines=[], misc=[])
data.misc = [A(text=str(i), pos=pt, color='r', font_size=20) for i, pt in enumerate(pts)]
data.lines.extend(pts_hull)
oplt.plot(data)

