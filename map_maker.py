import io


map = bytearray()

for x in range(32*32):
    map.append(x%64)
    map.append(x%17)

f = open("Maps/map1.bin", "wb")

f.write(map)
f.close()