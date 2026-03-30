import socket

def wake_on_lan(mac, broadcast_ip="192.168.1.255", port=9):
    mac = mac.replace(":", "").replace("-", "").replace(".", "")
    if len(mac) != 12:
        raise ValueError("Invalid MAC")

    mac_bytes = bytes.fromhex(mac)
    packet = b"\xff" * 6 + mac_bytes * 16

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        s.sendto(packet, (broadcast_ip, port))

wake_on_lan("18:C0:4D:48:A7:D3")
