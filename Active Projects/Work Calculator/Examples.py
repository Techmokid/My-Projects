from tkinter import *
import time

root = Tk()
root.title("Example Code")

#Create a text field
e = Entry(root)
e.grid(row=5,column=2)
e.insert(0, "Enter your name: ")

#Create a function that plays when the button is pressed
def myClick():
    if((e.get() != "Enter your name: ") and (e.get() != "")):
        helloText = "Hello \"" + e.get() + "\"!"
        myLabel = Label(root,text=helloText)
        myLabel.grid(row=1,column=1)
        e.insert(0, "Enter your name: ")

#Actually create the button
myButton = Button(root, text="Click Me!", padx=200, pady=50, command=myClick, fg="blue", bg="green")
myButton.grid(row=2,column=10)

#Actually start everything up
root.mainloop()
