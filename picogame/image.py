import os
import framebuf

SEEK_CUR = 1

def openImage(path):
    with open(path, mode='rb') as f:
        signature = f.read(2)
        fsize = int.from_bytes(f.read(4),'little')
        f.seek(4,SEEK_CUR)
        dataOffset = int.from_bytes(f.read(4),'little')

        infoHeaderSize = int.from_bytes(f.read(4),'little')
        size = (int.from_bytes(f.read(4),'little'),
                int.from_bytes(f.read(4),'little'))
        f.seek(2,SEEK_CUR)
        depth = int.from_bytes(f.read(2),'little')

        # If compression is 3 then we also need the mask fields to determine whether it is RGB555 or RGB565
        compression = int.from_bytes(f.read(4),'little')
        imageSize = int.from_bytes(f.read(4),'little')

        f.seek(4,SEEK_CUR)

        #colorUsed = struct.unpack('2I', f.read(8))
        f.seek(8, SEEK_CUR)
        masks = (int.from_bytes(f.read(4),'little'),
                 int.from_bytes(f.read(4),'little'),
                 int.from_bytes(f.read(4),'little'),
                 int.from_bytes(f.read(4),'little'))

        # Go to end of head
        f.seek(dataOffset)
        print(f.tell())

        rowSize = int(size[0]*depth/32*4)

        #imageData = framebuf.FrameBuffer(f.read(rowSize*size[1]), size[0], size[1], framebuf.RGB565)
        imageData = []
        for currentRow in range(0,size[1]):
            currentRead = f.read(rowSize)
            if len(currentRead) > 0:
                imageData.append(currentRead)

        return (size,imageData)
    
def createImageBuffer(self,sprite,x,y):
    #self.blit(sprite,size,x,y)
    width = size[0]
    height = size[1]
    tempBuffer = bytearray(width*height*2)
    buffer = framebuf.FrameBuffer(tempBuffer,width,height,framebuf.RGB565)
    
    for y in range(0,height):
        for x in range(0, width):
            buffer.pixel(x,y,sprite[x*y*2])

    return buffer
