import os
import framebuf

SEEK_CUR = 1

class Image:
    def createFromPath(self,path):
        self.openImage(path)
        self.createImageBuffer()
    
    def openImage(self,path):
        with open(path, mode='rb') as f:
            signature = f.read(2)
            fsize = int.from_bytes(f.read(4),'little')
            f.seek(4,SEEK_CUR)
            dataOffset = int.from_bytes(f.read(4),'little')

            infoHeaderSize = int.from_bytes(f.read(4),'little')
            self.size = (int.from_bytes(f.read(4),'little'),
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

            rowSize = int(self.size[0]*depth/32*4)

            self._imageData = []
            for currentRow in range(0,self.size[1]):
                for currentColumn in range(0,self.size[0]):
                    currentRead = f.read(2)
                    if len(currentRead) > 0:
                        self._imageData.append(currentRead)
        
    def createImageBuffer(self):
        width = self.size[0]
        height = self.size[1]
        tempBuffer = bytearray(width*height*2)
        self.buffer = framebuf.FrameBuffer(tempBuffer,width,height,framebuf.RGB565)
        
        # We need to flip rows because bmp starts on the bottom left.
        for y in range(0,height):
            for x in range(0, width):
                self.buffer.pixel(x,y,int.from_bytes(self._imageData[(height-1-y)*width+x],'little'))
                
    def createFromString(self,newImage):
        """Use a string to create an image. One byte per pixel. Height and width are inferred based on carriage returns."""
        
        width = newImage.find('\n',1)    
        height = 0
            
        self._imageData = []
        for currentChar in newImage:
            if (currentChar == '\n'):
                height += 1
            elif (currentChar == ' '):
                pass
            elif (currentChar == '.') or (currentChar == 'f'):
                self._imageData.append(0x0)
            elif (currentChar == '1'):
                self._imageData.append(0xffff)
            elif (currentChar == 'a'):
                self._imageData.append(0xf800)
            elif (currentChar == '3'):
                self._imageData.append(0x1f)
            else:
                self._imageData.append(0x7e0)
        
        tempBuffer = bytearray(width*height*2)
        self.buffer = framebuf.FrameBuffer(tempBuffer,width,height,framebuf.RGB565)
        
        # We need to flip rows because bmp starts on the bottom left.
        for y in range(0,height):
            for x in range(0, width):
                self.buffer.pixel(x,y,int.from_bytes(self._imageData[y*width+x],'little'))
            
                
        
