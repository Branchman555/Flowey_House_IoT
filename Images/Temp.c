
/*******************************************************************************
* image
* filename: unsaved
* name: Temp
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Threshold Dither 128
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: no
*******************************************************************************/

/*
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
*/
#include <stdint.h>



static const uint8_t image_data_Temp[5] = {
    0xf8, 
    0x20, 
    0x20, 
    0x20, 
    0x20
};
const tImage Temp = { image_data_Temp, 5, 5,
    8 };

