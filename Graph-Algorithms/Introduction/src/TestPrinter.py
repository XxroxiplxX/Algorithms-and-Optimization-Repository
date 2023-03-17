import pandas as pd
import matplotlib.pyplot as plt
import networkx as nx
import itertools
import sys
def d(dirtitle, direction):

    data = pd.read_csv('/tmp/graph_v' + dirtitle + '.csv', delimiter=';')
    vertices = data['v']
    data2 = pd.read_csv('/tmp/graph_e' + dirtitle + '.csv', delimiter=';')
    edges1 = data2['e1']
    edges2 = data2['e2']


    if direction == 'D':
        G = nx.DiGraph()
    else:
        G = nx.Graph()
    for v in vertices:
        G.add_node(v)
    for (e1, e2) in zip(edges1, edges2):
        G.add_edge(e1,e2)
    return G

if __name__ == "__main__":
    G=d(sys.argv[2], 'D')
    if sys.argv[1] == 'D':
        nx.draw(G, with_labels=True, font_weight='bold', node_color='green', node_size=800, pos=nx.spring_layout(G))
    else:
        nx.draw(G, with_labels=True, font_weight='bold', node_color='green')

    print('plot done')
    plt.savefig('../../plots/' + sys.argv[2] + '_test.png')