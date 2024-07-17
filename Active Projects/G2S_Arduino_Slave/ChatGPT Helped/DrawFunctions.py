from ArduinoCommunicationsInterface import Arduino

arduino = Arduino(port="COM4", baudrate=115200)

def draw_shape(shape, x, y, width, height=None, col=None, fill=False):
    msg = f"{'F' if fill else ''}{shape}:{x}:{y}:{width}"
    if height is not None:
        msg += f":{height}"
    if col is not None:
        msg += f":{col[0]}:{col[1]}:{col[2]}"
    arduino.send_command(msg)

def drawCircle(x, y, radius, col, fill):
    draw_shape("CIRCLE", x, y, radius, col=col, fill=fill)

def drawSquare(x, y, size, col, fill):
    draw_shape("SQUARE", x, y, size, col=col, fill=fill)

def drawRect(x, y, width, height, col, fill):
    draw_shape("RECT", x, y, width, height=height, col=col, fill=fill)

def drawText(x, y, size, msg, col):
    arduino.send_command(f"TEXT:{x}:{y}:{size}:{msg}:{col[0]}:{col[1]}:{col[2]}")

def drawRotatedRect(x, y, width, height, angle, col, fill):
    draw_shape("ROT", x, y, width, height=height, col=col, fill=fill)
    arduino.send_command(f"ROT:{x}:{y}:{width}:{height}:{angle}:{col[0]}:{col[1]}:{col[2]}")

def drawTriangle(x0, y0, x1, y1, x2, y2, col, fill):
    msg = f"TRIG:{x0}:{y0}:{x1}:{y1}:{x2}:{y2}:{col[0]}:{col[1]}:{col[2]}"
    if fill:
        msg = "F" + msg
    arduino.send_command(msg)

def fillScreen(col):
    arduino.send_command(f"FRECT:0:0:320:240:{col[0]}:{col[1]}:{col[2]}")

def clearScreen():
    fillScreen([0, 0, 0])

def drawTopBar():
    network_connection = check_network_connection()
    drawRect(0, 0, 320, 30, [30, 30, 30], True)
    drawRect(0, 30, 320, 210, [0, 0, 0], True)
    drawRotatedRect(16, 16, 13, 13, 45, [200, 200, 200], True)
    drawTriangle(17, 5, 17, 26, 27, 15, [100, 100, 100], True)
    drawRect(12, 13, 5, 6, [120, 0, 120], True)
    drawRect(17, 13, 5, 6, [0, 200, 120], True)
    drawText(45, 8, 2, header_title, colors["WHITE"])
    drawRect(289, 5, 25, 20, [120, 120, 120], True)
    drawRect(291, 7, 21, 15, colors["BLACK"], True)
    if network_connection == 0:
        drawRotatedRect(301, 14, 2, 30, 55, colors["RED"], True)
        drawRotatedRect(301, 14, 2, 30, -55, colors["RED"], True)
    elif network_connection == 1:
        drawText(296, 8, 2, "?", colors["ORANGE"])
    elif network_connection == 2:
        drawRotatedRect(305, 14, 2, 15, 55, colors["GREEN"], True)
        drawRotatedRect(298, 17, 2, 5, -55, colors["GREEN"], True)
