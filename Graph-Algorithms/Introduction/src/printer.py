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
    #nx.draw(G, with_labels=True, font_weight='bold')
    #plt.figure(i)
    #plt.savefig('../plots/' + dirtitle)
if __name__ == "__main__":
    plt.figure(figsize=(25,18))
    subax1 = plt.subplot(221)
    subax1.set_title('Graph')
    if sys.argv[1] == 'D':
        nx.draw(d('d', 'D'), with_labels=True, font_weight='bold', node_color='green')
    else:
        nx.draw(d('u', 'U'), with_labels=True, font_weight='bold', node_color='green')
    subax2 = plt.subplot(222)
    subax2.set_title('DFS Tree')
    nx.draw(d('tDFS', 'U'), with_labels=True, font_weight='bold', node_color='cyan')
    subax3 = plt.subplot(223)
    subax3.set_title('BFS Tree')
    nx.draw(d('tBFS', 'U'), with_labels=True, font_weight='bold', node_color='red')
    plt.show()
    print('plots done')
    #plt.savefig('../../plots/graphs.png')


