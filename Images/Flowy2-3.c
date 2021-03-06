
/*******************************************************************************
* image
* filename: unsaved
* name: Flowy2-3
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



static const uint8_t image_data_Flowy23[63] = {
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x20, 0x00, 
    0x00, 0x30, 0x00, 
    0x00, 0x30, 0x00, 
    0x00, 0x60, 0x00, 
    0x00, 0x20, 0x00, 
    0x00, 0x30, 0x00, 
    0x00, 0x30, 0x00, 
    0x00, 0x70, 0x00, 
    0x00, 0x00, 0x00
};
const tImage Flowy23 = { image_data_Flowy23, 21, 21,
    8 };

