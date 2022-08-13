from argparse import ArgumentParser
from ast import arg
from operator import index
from PIL import Image
from ctypes import c_uint32


g_log = False
args = None

def log(x):
    if(g_log):
        print(x)

def load_image(path):
    with Image.open(path) as img:
        #img = img.convert("RGB")
        if img.mode != "P":
            raise Exception("Format error image at{} is expected to be in palette mode".format(path))

        
        data = list(img.getdata())
        return data, img.width


def run_conversion(bpp):
    data, width = load_image(args.tileset)
    output = bytearray()

    for y in range(int(len(data)/(width*8))):
        for x in range(int(width/8)):
            #bp 12
            for row in range(8):
                append(output,convert_bitplane(data, (y * 8 + row) * width + x*8, 0))
                if bpp >=2:
                    append(output,convert_bitplane(data, (y * 8 + row) * width + x*8, 1))
            #bp 34
            if bpp >=4:
                for row in range(8):
                    append(output,convert_bitplane(data, (y * 8 + row) * width + x*8, 2))
                    append(output,convert_bitplane(data, (y * 8 + row) * width + x*8, 3))

    return output

def append(output, int):
    output.append(int.to_bytes(1,byteorder="little")[0])


def convert_bitplane(data, offset, bitplane):
    value = 0
    for x in range(8):
        value += ((data[offset+x] >> bitplane) & 0x01) << (7-x)
    return value

def write_to_file(filepath, data):
    with open(filepath, mode = "wb") as f:
        f.write(data)


def run():
    parser = ArgumentParser()
    parser.add_argument("bpp")
    parser.add_argument("tileset")
    parser.add_argument("outpath")
    parser.add_argument("--verbose", action ="store_true")
    parser.add_argument("--tests", action ="store_true")

    global args
    args = parser.parse_args()

    global g_log
    if(args.verbose):
        g_log = True

    log("Converting {}to {}".format(args.tileset, args.outpath))

    if(args.tests):
        run_unit_tests()
        exit(0)

    data = run_conversion(int(args.bpp))
    write_to_file(args.outpath, data)
    

if (__name__ == "__main__"):
    run()
