import socket
import struct

from onvif import ONVIFDiscovery


def get_ONVIF_List(timeout=5, interface=None):
    discovery = ONVIFDiscovery(
        timeout=timeout,
        interface=interface
    )

    devices = discovery.discover()
    camera_ips = []

    for device in devices:
        ip_address = device["host"]

        if ip_address not in camera_ips:
            camera_ips.append(ip_address)

    return camera_ips


def get_interface_ip(interface_name): #Use this function in linux if you are working with adapter names instead of IP addresses. E.g. "eth0"
    import fcntl
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    try:
        result = fcntl.ioctl(
            sock.fileno(),
            0x8915,  # SIOCGIFADDR
            struct.pack(
                "256s",
                interface_name[:15].encode("utf-8")
            )
        )

        return socket.inet_ntoa(result[20:24])

    finally:
        sock.close()

ethernet_ip = "192.168.1.1" #get_interface_ip("eth0")
while True:
    print(f"Scanning: {ethernet_ip}")
    cameraIPs = get_ONVIF_List(interface=ethernet_ip)

    if not cameraIPs:
        continue

    # We have a valid stream IP. Depending on camera depends on URL format
    camera_ip = cameraIPs[0]
    rtsp_url = (
        f"rtsp://admin:admin@{camera_ip}/0/ch01/"
    )
    #rtsp_url = (
    #    f"rtsp://admin:admin@{camera_ip}:80/ch0_0.264"
    #)

    # And now that we have the cameras IP and access URL, now we can do the FFMPEG funny business
    # CODE HERE
