from scapy.all import *
import random, time

IFACE = "Ethernet"   # change this: e.g. "eth0", "enp3s0", "Ethernet"
COUNT = 300
HOLD_SECONDS = 60

conf.checkIPaddr = False
BCAST = "ff:ff:ff:ff:ff:ff"

def mac_bytes(mac):
    return bytes.fromhex(mac.replace(":", ""))

def fake_mac(i):
    # Locally administered MAC: 02:xx:xx:xx:xx:xx
    return "02:00:00:%02x:%02x:%02x" % ((i >> 16) & 255, (i >> 8) & 255, i & 255)

def dhcp_opt(pkt, name):
    for opt in pkt[DHCP].options:
        if isinstance(opt, tuple) and opt[0] == name:
            return opt[1]
    return None

def get_lease(mac):
    xid = random.randint(1, 0xffffffff)
    chaddr = mac_bytes(mac)
    client_id = b"\x01" + chaddr

    discover = (
        Ether(src=mac, dst=BCAST) /
        IP(src="0.0.0.0", dst="255.255.255.255") /
        UDP(sport=68, dport=67) /
        BOOTP(chaddr=chaddr, xid=xid, flags=0x8000) /
        DHCP(options=[
            ("message-type", "discover"),
            ("client_id", client_id),
            ("param_req_list", [1, 3, 6, 15, 51, 54]),
            "end"
        ])
    )

    sendp(discover, iface=IFACE, verbose=False)

    offer = sniff(
        iface=IFACE,
        timeout=5,
        count=1,
        lfilter=lambda p:
            p.haslayer(DHCP) and
            p.haslayer(BOOTP) and
            p[BOOTP].xid == xid and
            dhcp_opt(p, "message-type") == 2
    )

    if not offer:
        print(f"{mac}: no DHCPOFFER")
        return None

    offer = offer[0]
    offered_ip = offer[BOOTP].yiaddr
    server_id = dhcp_opt(offer, "server_id")

    request = (
        Ether(src=mac, dst=BCAST) /
        IP(src="0.0.0.0", dst="255.255.255.255") /
        UDP(sport=68, dport=67) /
        BOOTP(chaddr=chaddr, xid=xid, flags=0x8000) /
        DHCP(options=[
            ("message-type", "request"),
            ("client_id", client_id),
            ("requested_addr", offered_ip),
            ("server_id", server_id),
            "end"
        ])
    )

    sendp(request, iface=IFACE, verbose=False)

    ack = sniff(
        iface=IFACE,
        timeout=5,
        count=1,
        lfilter=lambda p:
            p.haslayer(DHCP) and
            p.haslayer(BOOTP) and
            p[BOOTP].xid == xid and
            dhcp_opt(p, "message-type") == 5
    )

    if not ack:
        print(f"{mac}: offered {offered_ip}, but no DHCPACK")
        return None

    print(f"{mac} -> {offered_ip} from DHCP server {server_id}")
    return {
        "mac": mac,
        "ip": offered_ip,
        "server": server_id,
        "client_id": client_id,
        "chaddr": chaddr,
    }

def release_lease(lease):
    pkt = (
        Ether(src=lease["mac"], dst=BCAST) /
        IP(src=lease["ip"], dst=lease["server"]) /
        UDP(sport=68, dport=67) /
        BOOTP(
            chaddr=lease["chaddr"],
            ciaddr=lease["ip"],
            xid=random.randint(1, 0xffffffff)
        ) /
        DHCP(options=[
            ("message-type", "release"),
            ("client_id", lease["client_id"]),
            ("server_id", lease["server"]),
            "end"
        ])
    )
    sendp(pkt, iface=IFACE, verbose=False)
    print(f"released {lease['ip']} / {lease['mac']}")

leases = []

for i in range(COUNT):
    lease = get_lease(fake_mac(i + 1))
    if lease:
        leases.append(lease)
    time.sleep(0.3)

print(f"\nHolding {len(leases)} leases for {HOLD_SECONDS} seconds...")
time.sleep(HOLD_SECONDS)

print("\nReleasing leases...")
for lease in leases:
    release_lease(lease)
