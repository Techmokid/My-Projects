from DrawFunctions import drawRect, drawText

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
