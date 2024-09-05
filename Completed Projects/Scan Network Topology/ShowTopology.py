import networkx as nx
import matplotlib.pyplot as plt

# Load the saved GraphML file
def load_topology(filename="network_topology.graphml"):
    G = nx.read_graphml(filename)
    return G

# Visualize the loaded topology graph
def plot_topology(G):
    pos = nx.spring_layout(G, k=0.15, iterations=20)
    labels = nx.get_edge_attributes(G, 'weight')
    
    plt.figure(figsize=(12, 8))
    nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=1500, edge_color='gray')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    plt.title("Loaded Network Topology")
    plt.show()

if __name__ == "__main__":
    # Load the saved topology from GraphML file
    G = load_topology("network_topology.graphml")
    print("Topology loaded successfully.")

    # Visualize the topology
    plot_topology(G)
