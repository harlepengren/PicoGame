# PicoGame Image Format

We created a simple image format to save space on the Pico. Initially, this was created when we needed to keep the image in working memory. Therefore, we would have a simple palette and store the palette number for each pixel (two pixels per byte). Each drawing sequence would require us to convert the palette into the color for each pixel. This significantly reduced memory consumption, but was computationally heavy.

Since then we have changed into storing this in the flash memory. This allows us to copy (by row) instead.

## File Format

| Offset | Size    | Description     |
| ------ | ------- | -----------     |
| 0x00   | 2 bytes | Height of image |
| 0x02   | 2 bytes | Width of image  |
| 0x04   | 2 bytes | Number of colors in the color palette |
| 0x06   | 2 bytes per color | This is where we store the colors in the color palette. We will store 2 bytes per color (565). |
| 0x06 + (2*number of colors) | height * width / 2 | Store the actual pixels, 2 pixels per byte using the color palette index. |



## Special Notes
We are storing two pixels per byte. We don't want to check for the end of row in the middle of a byte. Therefore, the width must be even. If the input image is odd, we add 1 pixel to the end of the row to make it even.

The transparency color is always the first color in the color palette. If no transparency color is defined, then the transparency color is set to black. If you want no transparency in your image, then you need to set to a color that does not appear in the image.
