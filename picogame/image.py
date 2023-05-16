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
        """Use a string to create an image. One byte per pixel. Height and width are inferred based on carriage returns.
        The input must have equal length rows."""
        
        width = 0    
        height = 0
            
        self._imageData = []
        for currentChar in newImage:
            if (currentChar == '\n'):
                if height == 1:
                    # First line, let's get the width
                    width = len(self._imageData)
                height += 1
            elif (currentChar == ' '):
                pass
            elif (currentChar == '.') or (currentChar == 'f'):
                self._imageData.append(0)
            elif (currentChar == '1'):
                self._imageData.append(int(0xffff))
            elif (currentChar == '2'):
                self._imageData.append(int(0xf904))
            elif (currentChar == '3'):
                self._imageData.append(int(0xfc98))
            elif (currentChar == '4'):
                self._imageData.append(int(0xfc06))
            elif (currentChar == '5'):
                self._imageData.append(int(0xffa1))
            elif (currentChar == '6'):
                self._imageData.append(int(0x24f4))
            elif (currentChar == '7'):
                self._imageData.append(int(0x7eca))
            elif (currentChar == '8'):
                self._imageData.append(int(0x0215))
            elif (currentChar == '9'):
                self._imageData.append(int(0x879f))
            elif (currentChar == 'a'):
                self._imageData.append(int(0xc05e))
            elif (currentChar == 'b'):
                self._imageData.append(int(0xfc9f))
            elif (currentChar == 'c'):
                self._imageData.append(int(0x50ca))
            elif (currentChar == 'd'):
                self._imageData.append(int(0xacf0))
            elif (currentChar == 'e'):
                self._imageData.append(int(0x7b07))
            else:
                self._imageData.append(int(0x0020))
        
        height -= 1
        
        print("height",height)
        tempBuffer = bytearray(width*height*2)
        self.buffer = framebuf.FrameBuffer(tempBuffer,width,height,framebuf.RGB565)
        
        # We need to flip rows because bmp starts on the bottom left.
        for y in range(0,height):
            for x in range(0, width):
                self.buffer.pixel(x,y,self._imageData[y*width+x])

        self.size = (width,height)
            
                
        
