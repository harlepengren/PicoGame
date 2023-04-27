import os
import struct

def openImage(path):
    with open(path, mode='rb') as f:
        signature = struct.unpack('2c', f.read(2))
        fsize = struct.unpack('I',f.read(4))
        f.seek(4,os.SEEK_CUR)
        dataOffset = struct.unpack('I',f.read(4))[0]

        infoHeaderSize = struct.unpack('I',f.read(4))
        size = struct.unpack('2I',f.read(8))
        f.seek(2,os.SEEK_CUR)
        depth = struct.unpack('H',f.read(2))[0]

        # If compression is 3 then we also need the mask fields to determine whether it is RGB555 or RGB565
        compression = struct.unpack('I',f.read(4))
        imageSize = struct.unpack('I', f.read(4))

        f.seek(4,os.SEEK_CUR)

        colorUsed = struct.unpack('2I', f.read(8))
        masks = struct.unpack('<4I',f.read(16))

        # Go to end of head
        f.seek(dataOffset)
        print(f.tell())

        rowSize = int(size[0]*depth/32*4)

        imageData = []
        for currentRow in range(0,size[1]):
            currentRead = f.read(rowSize)
            if len(currentRead) > 0:
                imageData.append(currentRead)


        print("Signature: ", signature)
        print("File Size: ", fsize)
        print("Data Offset: ", dataOffset)
        print("Header Size: ", infoHeaderSize)
        print("Width/Height: ", size)
        print("Bit Depth: ", depth)
        print("Compression: ", compression)
        print("Image Size: ", imageSize)
        print("Color Table Used: ", colorUsed)
        print("Masks: ", masks)
        print("Row Size: ", rowSize)
        print("Number of rows: ", len(imageData))

        print("First row: ", imageData[0])

        return imageData
