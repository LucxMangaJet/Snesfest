from argparse import ArgumentParser
from ast import arg
from operator import index
from PIL import Image
from ctypes import c_uint32

g_log = False
args = None
TILE_SIZE = 8

def log(x):
    if(g_log):
        print(x)

def run_unit_tests():
    None

def get_tiles_indicies(iWitdh, startX, startY):
    arr = []    
    for x in range(TILE_SIZE):
        for y in range(TILE_SIZE):
            arr.append(startX + x + (startY + y)*iWitdh)
    return arr

def sub_array(data, indicies):
    arr = []
    for x in indicies:
        arr.append(data[x])
    return arr

def load_image_to_tiles(path):
    with Image.open(path) as img:
        #img = img.convert("RGB")
        if img.mode != "P":
            raise Exception("Format error image at{} is expected to be in palette mode".format(path))

        log("converting image to tiles: {}".format(img))

        data = list(img.getdata())

        tiles = []
        tilesCountX = int(img.width/TILE_SIZE) 
        tilesCountY = int(img.height/TILE_SIZE)

        for y in range(tilesCountY):
            for x in range(tilesCountX):
                tiles.append(sub_array(data, get_tiles_indicies(img.width,x*TILE_SIZE,y*TILE_SIZE)))
        return tiles

def hash_tile(tile):
    p1 = 7
    p2 = 31
    res = c_uint32(p1)
    for c in tile:
        res = c_uint32(res.value * p2 + c) 
    return res.value

def hash_tiles(tiles):
    return [hash_tile(t) for t in tiles]



def build_index_map(hashed_set, hashed_map):
    res = []
    for x in hashed_map:
        res.append(hashed_set.index(x))
    return res

#SNES
#v = vflip
#h = hflip
#o = prio
#p = palette
#t = tile
#SNES expected
#vhoppptt tttttttt
#currently implemented
#000000tt tttttttt
def snes_map_tile(vflip, hflip, prio,pal,tile):
    return ( tile>>8,tile%256) 

def build_snes_map(index_map):
    arr = bytearray()
    for x in index_map:
        bytes = snes_map_tile(0,0,0,0,x)
        arr.append(bytes[0])
        arr.append(bytes[1])
    return arr

def write_bytearray_file(filepath, data):
    with open(filepath, mode = "wb") as f:
        f.write(data)

def run_conversion():
    tiles_set = load_image_to_tiles(args.tileset)
    hashed_set = hash_tiles(tiles_set)
    tiles_map = load_image_to_tiles(args.tilemap)
    hashed_map = hash_tiles(tiles_map)

    index_map = build_index_map(hashed_set, hashed_map)

    snes_map = build_snes_map(index_map)
    write_bytearray_file(args.outpath, snes_map)
    

def run():
    parser = ArgumentParser()
    parser.add_argument("tileset")
    parser.add_argument("tilemap")
    parser.add_argument("outpath")
    parser.add_argument("--verbose", action ="store_true")
    parser.add_argument("--tests", action ="store_true")

    global args
    args = parser.parse_args()

    global g_log
    if(args.verbose):
        g_log = True

    log("Converting {} with palette {} to {}".format(args.tilemap, args.tileset, args.outpath))

    if(args.tests):
        run_unit_tests()
        exit(0)

    run_conversion()
    

if (__name__ == "__main__"):
    run()
