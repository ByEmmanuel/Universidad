import heapq
import matplotlib.pyplot as plt
import networkx as nx   

edges = [(0,1,4),(0,2,3),(1,2,1),(1,3,2),(2,4,5),(3,4,6),
         (3,5,7),(4,5,8),(4,6,2),(5,6,3),(5,7,4),(6,7,6)]

# Lista de adyacencia
adj = {}
for u,v,w in edges:
    adj.setdefault(u,[]).append((v,w))
    adj.setdefault(v,[]).append((u,w))

def dijkstra(src, tgt, adj):
    dist = {v: float('inf') for v in adj}
    prev = {v: None for v in adj}
    dist[src] = 0
    heap = [(0, src)]
    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]: continue
        for v, w in adj[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                prev[v] = u
                heapq.heappush(heap, (dist[v], v))
    # reconstruir camino
    path, node = [], tgt
    while node is not None:
        path.append(node); node = prev[node]
    return dist[tgt], list(reversed(path))

src, tgt  = 0, 7
dist, path = dijkstra(src, tgt, adj)
path_edges = list(zip(path[:-1], path[1:]))

# Dibujar con networkx solo como utilidad gráfica
G = nx.Graph()
for u,v,w in edges: G.add_edge(u,v,weight=w)
pos = nx.spring_layout(G, seed=2)

nx.draw(G, pos, with_labels=True, edge_color='gray', width=1)
nx.draw_networkx_edges(G, pos, edgelist=path_edges, edge_color='red', width=3)
nx.draw_networkx_edge_labels(G, pos,
    {(u,v): d['weight'] for u,v,d in G.edges(data=True)})
plt.title(f"Dijkstra manual {src}→{tgt}  d={dist}")
plt.show()