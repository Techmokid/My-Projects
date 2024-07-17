import serial
import time

class Arduino:
    def __init__(self, port, baudrate):
        self.ser = serial.Serial(port=port, baudrate=baudrate)
        self.buffer = []
        time.sleep(2)

    def read_touch_input(self):
        if self.ser.in_waiting > 0:
            data = self.ser.readline().decode('utf-8').strip()
            if data.startswith("TOUCH"):
                _, x, y = data.split(':')
                return int(x), int(y)
        return None

    def read_serial(self):
        if self.ser.in_waiting > 0:
            data = self.ser.readline().decode('utf-8').strip()
            self.buffer.append(data)
            #print(f"Received command: {data}")
            if "ERR" in data:
                print("ERR")

    def send_command(self, msg):
        self.ser.write((msg + "\n").encode('utf-8'))

    def close(self):
        self.ser.close()
