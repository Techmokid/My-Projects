import serial
import time

class Arduino:
    _instance = None

    def __new__(cls, port=None, baudrate=None):
        if cls._instance is None:
            cls._instance = super(Arduino, cls).__new__(cls)
            cls._instance._initialized = False
        return cls._instance

    def __init__(self, port=None, baudrate=None):
        if self._initialized:
            return
        self.ser = serial.Serial(port=port, baudrate=baudrate)
        self.buffer = []
        time.sleep(2)
        self._initialized = True

    def clear_touch_commands(self):
        self.buffer = [line for line in self.buffer if not (line.startswith("TOUCH") or line.startswith("RELEASE"))]

    def clear_buffer(self):
        self.buffer = []

    def read_touch_input(self):
        self.read_serial()
        
        if len(self.buffer) > 0:
            for i in range(len(self.buffer)-1, -1, -1):
                line = self.buffer[i]
                
                if line.startswith("TOUCH"):
                    command = self.buffer.pop(i)
                    _, x, y, _ = command.split(':')
                    return int(x), int(y), True
                if line.startswith("RELEASE"):
                    command = self.buffer.pop(i)
                    _, x, y, _ = command.split(':')
                    return int(x), int(y), False
        return None, None, None

    def read_serial(self):
        while self.ser.in_waiting > 0:
            data = self.ser.readline().decode('utf-8').strip()
            self.buffer.append(data)
            if "ERR" in data:
                print("ERR")

    def send_command(self, msg):
        self.ser.write((msg + "\n").encode('utf-8'))

    def close(self):
        self.ser.close()
