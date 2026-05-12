import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
edges = [(0,1,4),(0,2,3),(1,2,1),(1,3,2),(2,4,5),(3,4,6),(3,5,7),(4,5,8),(4,6,2),(5,6,3),(5,7,4),(6,7,6)]
for u,v,w in edges: G.add_edge(u,v,weight=w)

mst = nx.minimum_spanning_tree(G, algorithm='kruskal')
pos = nx.spring_layout(G, seed=2)

nx.draw(G, pos, with_labels=True, edge_color='gray', width=1)
nx.draw(mst, pos, with_labels=True, edge_color='red', width=3)
nx.draw_networkx_edge_labels(G, pos, {(u,v): d['weight'] for u,v,d in G.edges(data=True)})
plt.title(f"Kruskal MST  w={mst.size(weight='weight')}")
plt.show()