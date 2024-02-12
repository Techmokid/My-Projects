import socket,json,time,pyaudio,pyttsx3
import numpy as np

server_address = "122.109.10.54"
server_port = 25565

def ping_minecraft_server(address, port=25565):
    # Create a socket connection to the server
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.settimeout(10)

        try:
            s.connect((address, port))
        except:
            return None
        
        # Send handshake + status request
        s.send(b"\x07\x00\x00\x00\x00\x46\x6F\x6F\x00")
        s.send(b"\x01\x00")
        
        # Read the packet length (varint)
        packet_length = int.from_bytes(s.recv(1), byteorder='big')
        if packet_length:
            # Read the rest of the response
            data = s.recv(1024)
            
            # The response will be a JSON string that starts with a length header we can ignore for this purpose
            # So, we find the start of the JSON string (first '{' character) and decode it
            json_start = data.find(b'{')
            json_data = data[json_start:].decode('utf-8')
            
            server_info = json.loads(json_data)
            return server_info
        else:
            return None

def play_tone(frequency, duration, volume=0.5, sample_rate=44100):
    p = pyaudio.PyAudio()
    stream = p.open(format=pyaudio.paFloat32,
                    channels=1,
                    rate=sample_rate,
                    output=True)

    # Generate sine wave
    samples = (np.sin(2 * np.pi * np.arange(sample_rate * duration) * frequency / sample_rate)).astype(np.float32)

    # Play audio
    stream.write(volume * samples)

    stream.stop_stream()
    stream.close()
    p.terminate()

engine = pyttsx3.init()
engine.setProperty('rate',150)
engine.setProperty('volume',1)
serverStatus = None
while True:
    server_info = ping_minecraft_server(server_address, server_port)
    if server_info:
        if not (serverStatus == True):
            print("Server Online")
            print(json.dumps(server_info, indent=4))
            play_tone(262,0.1)
            play_tone(392,0.1)
            play_tone(330,0.1)
            play_tone(523,0.1)
            engine.say('Minecraft server is now online')
            engine.runAndWait()
        serverStatus = True
    else:
        if not (serverStatus == False):
            print("Server Offline")
            play_tone(523,0.1)
            play_tone(330,0.1)
            play_tone(392,0.1)
            play_tone(262,0.1)
            engine.say('Minecraft server is offline')
            engine.runAndWait()
        serverStatus = False
    time.sleep(30)



















