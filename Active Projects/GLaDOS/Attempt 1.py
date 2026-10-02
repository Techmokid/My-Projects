import socket
import struct
import subprocess
import time
import os

from onvif import ONVIFDiscovery

# Testing for FFMPEG and FFPLAY
import shutil
import sys
from tkinter import messagebox

# ----------------------------------------------------------------------------------------------------------------------
# Configuration

# Windows testing:
ETHERNET_IP = "192.168.1.1"

# Raspberry Pi:
# ETHERNET_IP = None
# ETHERNET_INTERFACE = "eth0"

GIF_FILE = "overlay.gif"

RTSP_USERNAME = "admin"
RTSP_PASSWORD = "admin"

DISCOVERY_TIMEOUT = 5
RETRY_DELAY = 2


# ----------------------------------------------------------------------------------------------------------------------
# ONVIF discovery

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


def get_interface_ip(interface_name):
    """
    Return the IPv4 address assigned to a Linux network interface.
    For example: get_interface_ip("eth0")
    """
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


# ----------------------------------------------------------------------------------------------------------------------
# Video playback

def play_camera(rtsp_url, gif_file):
    """
    Run FFmpeg and FFplay until the camera stream ends.

    FFmpeg:
        - Decodes the camera
        - Loops the GIF
        - Applies 50% GIF opacity
        - Composites both images

    FFplay:
        - Displays the resulting video fullscreen
    """

    filter_graph = (
        "[1:v]"
        "format=rgba,"
        "colorchannelmixer=aa=0.5"
        "[gif];"
        "[0:v][gif]"
        "overlay="
        "x=(main_w-overlay_w)/2:"
        "y=(main_h-overlay_h)/2:"
        "shortest=1"
        "[video]"
    )

    ffmpeg_command = [
        "ffmpeg",

        # Reduce RTSP buffering and latency
        "-fflags", "nobuffer",
        "-flags", "low_delay",
        "-rtsp_transport", "tcp",

        # Camera input
        "-i", rtsp_url,

        # Loop GIF forever
        "-stream_loop", "-1",
        "-i", gif_file,

        # Overlay filter
        "-filter_complex", filter_graph,
        "-map", "[video]",

        # No sound
        "-an",

        # Avoid lossy video re-encoding
        "-c:v", "rawvideo",
        "-pix_fmt", "yuv420p",

        # NUT communicates dimensions and frame rate to FFplay
        "-f", "nut",
        "pipe:1"
    ]

    ffplay_command = [
        "ffplay",

        # Fullscreen, borderless, minimal buffering
        "-fs",
        "-noborder",
        "-fflags", "nobuffer",
        "-flags", "low_delay",
        "-framedrop",

        # Hide playback information
        "-hide_banner",
        "-loglevel", "warning",

        # Read FFmpeg's output
        "-i", "pipe:0"
    ]

    print("Starting camera display...")

    ffmpeg_process = subprocess.Popen(
        ffmpeg_command,
        stdout=subprocess.PIPE
    )

    ffplay_process = subprocess.Popen(
        ffplay_command,
        stdin=ffmpeg_process.stdout
    )

    # The parent Python process does not need this copy.
    ffmpeg_process.stdout.close()

    try:
        # Wait until FFplay closes or loses its input.
        ffplay_process.wait()

    finally:
        if ffplay_process.poll() is None:
            ffplay_process.terminate()

        if ffmpeg_process.poll() is None:
            ffmpeg_process.terminate()

        try:
            ffplay_process.wait(timeout=3)
        except subprocess.TimeoutExpired:
            ffplay_process.kill()

        try:
            ffmpeg_process.wait(timeout=3)
        except subprocess.TimeoutExpired:
            ffmpeg_process.kill()

    print("Camera display ended.")

def checkLibraries():
    missing = []
    
    if shutil.which("ffmpeg") is None:
        missing.append("FFmpeg")

    if shutil.which("ffplay") is None:
        missing.append("FFplay")

    if missing:
        messagebox.showerror(
            "Missing dependency",
            "The following programs could not be found:\n\n"
            + "\n".join(missing)
            + "\n\nPlease install them and add them to the system PATH."
        )

        sys.exit(1)

    print("FFmpeg and FFplay are available.")

# ----------------------------------------------------------------------------------------------------------------------
# Main program

def main():
    checkLibraries()
    
    if not os.path.isfile(GIF_FILE):
        raise FileNotFoundError(
            f"Overlay GIF was not found: {GIF_FILE}"
        )

    # Windows testing
    ethernet_ip = ETHERNET_IP

    # Use this instead on Raspberry Pi:
    # ethernet_ip = get_interface_ip(ETHERNET_INTERFACE)

    while True:
        try:
            print(f"Scanning through: {ethernet_ip}")

            camera_ips = get_ONVIF_List(
                timeout=DISCOVERY_TIMEOUT,
                interface=ethernet_ip
            )

            if not camera_ips:
                print("No ONVIF camera found. Retrying...")
                time.sleep(RETRY_DELAY)
                continue

            camera_ip = camera_ips[0]
            print(f"Found ONVIF camera: {camera_ip}")

            rtsp_url = (
                f"rtsp://{RTSP_USERNAME}:{RTSP_PASSWORD}"
                f"@{camera_ip}/0/ch01/"
            )

            play_camera(rtsp_url, GIF_FILE)

            print("Stream stopped. Returning to discovery...")
            time.sleep(RETRY_DELAY)

        except KeyboardInterrupt:
            print("\nExiting.")
            break

        except Exception as error:
            print(f"Error: {error}")
            time.sleep(RETRY_DELAY)


if __name__ == "__main__":
    main()