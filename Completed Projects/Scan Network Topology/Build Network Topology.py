import nmap
from scapy.all import sr1, IP, ICMP
import networkx as nx
import matplotlib.pyplot as plt
import concurrent.futures

# Initialize nmap scanner
nm = nmap.PortScanner()

# Function to perform ICMP ping
def ping_host(host):
    pkt = IP(dst=host)/ICMP()
    reply = sr1(pkt, timeout=1, verbose=0)  # Timeout set to 1 second
    if reply is None:
        return None
    return reply.ttl  # Hop count gives an idea of how many hops away the host is

# Scan the local network for active devices
def scan_network(network):
    nm.scan(hosts=network, arguments='-sn')  # -sn for ping scan
    devices = []
    for host in nm.all_hosts():
        if nm[host].state() == "up":
            devices.append(host)
    return devices

# Concurrent function to check connectivity between two devices
def check_connection(device_pair):
    device, other_device = device_pair
    ttl = ping_host(other_device)
    if ttl is not None:
        return (device, other_device, ttl)
    return None

# Build a topology graph using NetworkX with parallel pings
def build_topology(devices):
    G = nx.Graph()
    G.add_nodes_from(devices)
    
    device_pairs = [(device, other_device) for device in devices for other_device in devices if device != other_device]
    
    # Use ThreadPoolExecutor to handle the pings concurrently
    with concurrent.futures.ThreadPoolExecutor(max_workers=100) as executor:
        for result in executor.map(check_connection, device_pairs):
            if result:
                device, other_device, ttl = result
                G.add_edge(device, other_device, weight=ttl)
    
    return G

def save_topology(G, filename="network_topology.graphml"):
    nx.write_graphml(G, filename)
    print(f"Topology saved to {filename}")

if __name__ == "__main__":
    # Adjust network range for your setup
    network_range = "10.10.0.0/22"  # This will scan the entire /22 range

    print("Scanning network...")
    devices = scan_network(network_range)
    print(f"Devices found: {devices}")

    print("Building network topology...")
    G = build_topology(devices)

    print("Saving network topology...")
    save_topology(G, filename="network_topology.graphml")

    print("Visualizing topology...")
    import ShowTopology
    ShowTopology.plot_topology(G)
