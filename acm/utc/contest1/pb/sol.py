#!/usr/bin/python

def update_cnx_id(vertices_cnx_id, old, new):
    for i,cnx_id in enumerate(vertices_cnx_id):
        if cnx_id == old:
            vertices_cnx_id[i] = new

def update_is_tree(vertices_is_tree, vertices_cnx_id, cnx_id_to_update):
    for i,cnx_id in enumerate(vertices_cnx_id):
        if cnx_id == cnx_id_to_update:
            vertices_is_tree[i] = 0

def add_edge(vertices_cnx_id, vertices_is_tree, edge):
    x,y = edge
    cnx_id_x,cnx_id_y = vertices_cnx_id[x], vertices_cnx_id[y]
    # si les noeud sont deja dans la meme composante connexe, alors on cre un cycle
    if cnx_id_x == cnx_id_y:
        update_is_tree(vertices_is_tree, vertices_cnx_id, cnx_id_x)
    # sinon on fusionne les deux composante connexes
    else:
        # si une des deux composantes connexes contient deja un cycle, 
        # alors la nouvelle composante connexe comportera un cycle
        if not vertices_is_tree[cnx_id_x]:
            update_is_tree(vertices_is_tree, vertices_cnx_id, cnx_id_y)
        if not vertices_is_tree[cnx_id_y]:
            update_is_tree(vertices_is_tree, vertices_cnx_id, cnx_id_x)
        # fusion des deux composantes connexes
        update_cnx_id(vertices_cnx_id, cnx_id_x, cnx_id_y)

if __name__ == '__main__':
    n,k = ( int(x) for x in raw_input().split() )
    vertices_cnx_id = [ i for i in xrange(n) ]
    vertices_is_tree = [ 1 for _ in xrange(n) ]
    for _ in xrange(k):
        action = [ int(x) for x in raw_input().split() ]
        # si ajout edge
        if action[0] == 0:
            add_edge(vertices_cnx_id, vertices_is_tree, (action[1]-1,action[2]-1))
        # question
        else:
            print vertices_is_tree[action[1]-1]
        #print 'action', action
        #print vertices_cnx_id
        #print vertices_is_tree
