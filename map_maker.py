import io
import sys

from numpy import size
import PySimpleGUI as gui

class Palette(object):

    def __init__(self):
        self.colors = []

    @staticmethod
    def load_from_file(x):
        pal = Palette()
        with open(file = x, mode = "rb") as f:
            while(bytes := f.read(2)):
                red = (bytes[1]<<3) %256
                green = ((bytes[0] & 0x03 + bytes[1]>>5) <<3) %256
                blue = ((bytes[0]>>2)<<3) %256

                col = "#{:02X}{:02X}{:02X}".format(red, green, blue)
                pal.colors.append(col)

        return pal

palette = Palette()


def load_palette():
    file = gui.popup_get_file("Select the palette file")
    try: 
        new_pal = Palette.load_from_file(file)
    except Exception as e:
        gui.popup("Error!", e)
    
    print(new_pal.colors)


#tilemap format
#v-flip h-flip prio, pallete, tileIndex
#vhopppcc cccccccc

pal_button_confirm = gui.Button('Load', key="pal_load")

buttons = []
for x in range(256):
    button = gui.Button(button_color = "#000000")
    buttons.append(button)

layout = [[pal_button_confirm],buttons]


window = gui.Window(title="Snes Map Maker", layout=layout, size = (480,360))

while True:
    event, values = window.read()
    print(event)
    if event == gui.WIN_CLOSED or event == 'Cancel':
        break
    elif event == "pal_load":
        load_palette()