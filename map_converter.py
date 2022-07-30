from argparse import ArgumentParser
from ast import arg
from operator import index
from PIL import Image
from ctypes import c_uint32

from matplotlib.pyplot import cla

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

        data = list(img.getdata())

        tiles = []
        tilesCountX = int(img.width/TILE_SIZE) 
        tilesCountY = int(img.height/TILE_SIZE)

        for y in range(tilesCountY):
            for x in range(tilesCountX):
                tiles.append(sub_array(data, get_tiles_indicies(img.width,x*TILE_SIZE,y*TILE_SIZE)))
        return tiles, tilesCountX

def hash_tile(tile):
    p1 = 7
    p2 = 31
    res = c_uint32(p1)
    for c in tile:
        res = c_uint32(res.value * p2 + c) 
    return res.value

class HashInfo:
    def __init__(self,indx, x,y, hash) -> None:
        self.index = indx
        self.x = x
        self.y = y
        self.hash = hash
        self.hf = False
        self.vf = False
        self.pal = 0
        
        
def hash_tiles(tiles, width):
    hashes = []
    for i in range(len(tiles)):
        x = i%width
        y = int(i/width)
        hashes.append(HashInfo(i,x,y,hash_tile(tiles[i])))
    return hashes

def find_matching_tile(hashed_set, tile):
    for x in hashed_set:
        if x.hash == tile.hash:
            return x
    return None

def build_index_map(hashed_set, hashed_map):
    res = []
    for map_tile in hashed_map:
        tile = find_matching_tile(hashed_set, map_tile)
        if(tile is None):
            print("Failed to find tile at ({},{})".format(map_tile.x, map_tile.y))
            res.append(0)
        else:
            res.append(tile.index)

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
    return tile.to_bytes(2,byteorder ="little") 

    return arr

def write_snesmap_file(filepath, index_map):
    with open(filepath, mode = "wb") as f:
        for x in index_map:
            f.write(snes_map_tile(0,0,0,0,x))

def run_conversion():
    tiles_set, tiles_set_width = load_image_to_tiles(args.tileset)
    hashed_set = hash_tiles(tiles_set,tiles_set_width)
    tiles_map, tiles_map_width = load_image_to_tiles(args.tilemap)
    hashed_map = hash_tiles(tiles_map,tiles_map_width)

    index_map = build_index_map(hashed_set, hashed_map)

    write_snesmap_file(args.outpath, index_map)
    

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
