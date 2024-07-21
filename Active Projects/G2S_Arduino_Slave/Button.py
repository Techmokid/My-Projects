if __name__ == "__main__":
    exit()

from DrawFunctions import drawRect, drawText

class Button:
    def __init__(self,
                 x, y, width, height,
                 color, text_color,
                 pressed_color, pressed_text_color,
                 text, press_function, draw_image_function):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color
        self.text = text
        self.text_color = text_color
        self.pressed_color = pressed_color
        self.pressed_text_color = pressed_text_color
        self.press_function = press_function
        self.draw_image_function = draw_image_function
        self.prevPressed = False

    def draw(self):
        drawRect(self.x, self.y, self.width, self.height, self.color, True)
        drawText(self.x + 10, self.y + self.height - 20, 2, self.text, self.text_color)
        if self.draw_image_function is not None:
            self.draw_image_function()

    def draw_pressed(self):
        drawRect(self.x, self.y, self.width, self.height, self.pressed_color, True)
        drawText(self.x + 10, self.y + self.height - 20, 2, self.text, self.pressed_text_color)
        if self.draw_image_function is not None:
            self.draw_image_function()

    def is_touched(self, touch_x, touch_y):
        return self.x <= touch_x <= self.x + self.width and self.y <= touch_y <= self.y + self.height

class Buttons:
    def __init__(self):
        self.buttons_list = []

    def clear_buttons(self):
        self.buttons_list = []

    def add_preexisting_button(self, button):
        self.buttons_list.append(button)
        
    def add_button(self, x, y, width, height, color, text_color, pressed_color, pressed_text_color, text, press_function, draw_image_function):
        button = Button(x, y, width, height, color, text_color, pressed_color, pressed_text_color, text, press_function, draw_image_function)
        self.buttons_list.append(button)
        button.draw()

    def process(self, touch_spot):
        touch_x, touch_y, touched = touch_spot
        if touched is None:
            return
        
        for b in self.buttons_list:
            if touched: # We are pressing and holding the button
                if b.is_touched(touch_x, touch_y):
                    if not b.prevPressed:
                        b.prevPressed = True
                        b.draw_pressed()
                else:                        # If we are not pressing the button, but it was previously pressed, redraw it as normal
                    if b.prevPressed:
                        b.prevPressed = False
                        b.draw()
            else:
                if b.is_touched(touch_x, touch_y):
                    try:
                        b.press_function()
                    except:
                        print("Error: No function was set for button \"" + b.text + "\"")
                        b.draw()
                        b.prevPressed = False

    def forceDrawButtons(self):
        for i in self.buttons_list:
            i.draw()
