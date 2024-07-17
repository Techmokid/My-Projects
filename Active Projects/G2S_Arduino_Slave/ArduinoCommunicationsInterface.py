class Arduino:
    def __init__(self, port, baudrate):
        ser = serial.Serial(port="COM4", baudrate=115200)
        time.sleep(2)
        

class Button:
    def __init__(self, x, y, width, height, color, text, text_color):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color
        self.text = text
        self.text_color = text_color

    def draw(self):
        drawRect(self.x, self.y, self.width, self.height, self.color, True)
        drawText(self.x + 10, self.y + self.height - 20, 2, self.text, self.text_color)

    def is_touched(self, touch_x, touch_y):
        return self.x <= touch_x <= self.x + self.width and self.y <= touch_y <= self.y + self.height

def read_touch_input():
    global ser
    if ser.in_waiting > 0:
        data = ser.readline().decode('utf-8').strip()
        if data.startswith("TOUCH"):
            _, x, y = data.split(':')
            return int(x), int(y)
    return None

# Arduino Serial Communication Commands
def read_serial():
    global ser
    if ser.in_waiting > 0:
        data = ser.readline().decode('utf-8').strip()
        print(f"Received command: {data}")
        if "ERR" in data:
            print("ERR")

def send_command(msg):
    ser.write((msg + "\n").encode('utf-8'))

def draw_shape(shape, x, y, width, height=None, col=None, fill=False):
    msg = f"{'F' if fill else ''}{shape}:{x}:{y}:{width}"
    if height is not None:
        msg += f":{height}"
    if col is not None:
        msg += f":{col[0]}:{col[1]}:{col[2]}"
    send_command(msg)

def drawCircle(x, y, radius, col, fill):
    draw_shape("CIRCLE", x, y, radius, col=col, fill=fill)

def drawSquare(x, y, size, col, fill):
    draw_shape("SQUARE", x, y, size, col=col, fill=fill)

def drawRect(x, y, width, height, col, fill):
    draw_shape("RECT", x, y, width, height=height, col=col, fill=fill)

def drawText(x, y, size, msg, col):
    send_command(f"TEXT:{x}:{y}:{size}:{msg}:{col[0]}:{col[1]}:{col[2]}")

def drawRotatedRect(x, y, width, height, angle, col, fill):
    draw_shape("ROT", x, y, width, height=height, col=col, fill=fill)
    send_command(f"ROT:{x}:{y}:{width}:{height}:{angle}:{col[0]}:{col[1]}:{col[2]}")

def drawTriangle(x0, y0, x1, y1, x2, y2, col, fill):
    msg = f"TRIG:{x0}:{y0}:{x1}:{y1}:{x2}:{y2}:{col[0]}:{col[1]}:{col[2]}"
    if fill:
        msg = "F" + msg
    send_command(msg)

def fillScreen(col):
    send_command(f"FRECT:0:0:320:240:{col[0]}:{col[1]}:{col[2]}")

def clearScreen():
    fillScreen(colors["BLACK"])
