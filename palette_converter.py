import argparse
from ast import arg
import io
from argparse import ArgumentParser
from sys import byteorder

from matplotlib import colors

g_log = False
args = None

#0rrrrrgggggbbbbb
def rgb2snes(r,g, b):
    FILTER = 0x000000F8
    res = (b&FILTER) <<7
    res |= (g&FILTER) <<2
    res |= (r&FILTER) >>3
    return res

def log(x):
    if(g_log):
        print(x)


def hex2snes(col):
    r = int(col[0:2], base=16)
    g = int(col[2:4], base=16)
    b = int(col[4:6], base=16)
    col = rgb2snes(r,g,b)
    return col;
    

def test_hex2snes(vhex, expected):
    value = hex2snes(vhex)
    if expected != value:
        print("TestError: {}. Expected: {}. Value: {}.".format(vhex, hex(expected), hex(value)))

def run_unit_tests():
    log("Running unit tests")
    test_hex2snes("000000",0x00)
    test_hex2snes("FFFFFF",0x7FFF)
    #                      0b0bbbbbgggggrrrrr
    test_hex2snes("FF0000",0b0000000000011111)
    test_hex2snes("00FF00",0b0000001111100000)
    test_hex2snes("0000FF",0b0111110000000000)
    test_hex2snes("080808",0b0000010000100001)


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

def export_colors(colors):
    with open(args.outpath, mode = "wb") as f:
        for col in colors:
            f.write(col.to_bytes(2, byteorder='big'))
        


def run():
    parser = ArgumentParser()
    parser.add_argument("filepath")
    parser.add_argument("outpath")
    parser.add_argument("--log", action ="store_true")
    parser.add_argument("--tests", action ="store_true")

    global args
    args = parser.parse_args()

    #validate args

    global g_log
    if(args.log):
        g_log = True

    if(args.tests):
        run_unit_tests()

    colors = collect_colors()
    export_colors(colors)










if (__file__ != "__main__"):
    run()
