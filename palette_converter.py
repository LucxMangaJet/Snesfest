import argparse
from ast import arg
from cgi import test
import io
from argparse import ArgumentParser
from sys import byteorder

from matplotlib import colors

g_log = False
args = None

#0bbbbbgggggrrrrr
def rgb2snes(r,g, b):
    FILTER = 0x000000F8
    res = (b&FILTER) <<7
    #print("{0:b}".format(res))
    res |= (g&FILTER) <<2
    #print("{0:b}".format(res))
    res |= (r&FILTER) >>3
    #print("{0:b}".format(res))
    return res

def log(x):
    if(g_log):
        print(x)


def hex2snes(col):
    r = int(col[0:2], base=16)
    g = int(col[2:4], base=16)
    b = int(col[4:6], base=16)
    col = rgb2snes(r,g,b)
    return col

def snes2hex(color):
    FILTER_RED =   0b0000000000011111
    FILTER_GREEN = 0b0000001111100000
    FILTER_BLUE =  0b0111110000000000
    red =   (color&FILTER_RED)<<3
    green = (color&FILTER_GREEN)>>2
    blue =  (color&FILTER_BLUE)>>7 
    col = "{:02x}{:02x}{:02x}".format(red, green, blue)
    return col

    

def test_hex2snes(vhex, expected):
    value = hex2snes(vhex)
    if expected != value:
        print("hex2snes Error: {}. Expected: {}. Value: {}.".format(vhex, hex(expected), hex(value)))

    chex = snes2hex(expected)
    if int(chex, base=16) != int(vhex, base=16):
        print("snes2hex Error: {}. Expected: {}. Value: {}.".format("{0:b}".format(expected), vhex, chex))

    
    
    
def run_unit_tests():
    log("Running unit tests")
    test_hex2snes("000000",0x00)
    test_hex2snes("F8F8F8",0x7FFF)
    #                      0b0bbbbbgggggrrrrr
    test_hex2snes("F80000",0b0000000000011111)
    test_hex2snes("00F800",0b0000001111100000)
    test_hex2snes("0000F8",0b0111110000000000)
    test_hex2snes("080808",0b0000010000100001)
    test_hex2snes("C078B8",0x5df8)
    test_hex2snes("d078b8",0b0101110111111010)




def collect_colors():
    with open(args.filepath, mode = "r") as f:
            colors = []
            lines = f.readlines()
            count = len(lines)

            if count > 256:
                raise Exception("Too many lines. Max lines expected 256. Recieved {}".format(len(count)))

            log("Converting {} colors.".format(count))

            #validate
            for line in lines:
                col = hex2snes(line)
                colors.append(col)
            
            return colors

def export_colors_binary(colors):
    with open(args.outpath, mode = "wb") as f:
        for col in colors:
            f.write(col.to_bytes(2, byteorder='big'))
        

def export_colors_hex(colors):
    with open(args.outpath, mode = "w") as f:
        for col in colors:
            f.write("{}\n".format(snes2hex(col)))


def run():
    parser = ArgumentParser()
    parser.add_argument("filepath")
    parser.add_argument("outpath")
    parser.add_argument("--log", action ="store_true")
    parser.add_argument("--tests", action ="store_true")
    parser.add_argument("--hex", action ="store_true")

    global args
    args = parser.parse_args()

    #validate args

    global g_log
    if(args.log):
        g_log = True



    if(args.tests):
        run_unit_tests()

    colors = collect_colors()
    if(args.hex):
        export_colors_hex(colors)
    else:
        export_colors_binary(colors)








if (__file__ != "__main__"):
    run()
