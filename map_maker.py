import io


map = bytearray()

for x in range(32*32):
    map.append(0x00)
    map.append(x%256)

f = open("Maps/map1.bin", "wb")

f.write(map)
f.close()