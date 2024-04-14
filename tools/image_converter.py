# Converts an image to a raw stream of bytes
from PIL import Image

def convert_565rgb(color):
    r = color[0]
    g = color[1]
    b = color[2]

    return ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3)

def convert_image(filename, output_name, transparency_color = (0,0,0)):
    im = Image.open(filename)
    add_column = False

    # We are storing two pixels per byte. Therefore, we need
    # an even number of pixels in the width (so we don't have to
    # check for a row end in the middle of a pixel)
    if im.width % 2 != 0:
        add_column = True


    color_palette = [transparency_color]
    temporary_image = []
    
    for y in range(0,im.height):
        for x in range(0,im.width):
            current_color = im.getpixel((x,y))

            if current_color not in color_palette:
                color_palette.append(current_color)

            # Get the index of the color
            temporary_image.append(color_palette.index(current_color))
        
        if add_column:
            temporary_image.append(0)

    # Now export to a file
    with open("output_name.txt","wb") as binary_file:
        # write the color palette as the first 32 bytes (565 RGB)
        # the first byte tells how many entries
        binary_file.write(len(color_palette))

        # write the colors
        for current_color in color_palette:
            binary_file.write(convert_565rgb(current_color))

        for index in range(0,len(temporary_image),2):
            binary_file.write(((temporary_image[index] & 0xf) << 4) | ((temporary_image[index+1] & 0xf)))
