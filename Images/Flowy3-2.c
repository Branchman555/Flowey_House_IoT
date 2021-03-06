
/*******************************************************************************
* image
* filename: unsaved
* name: Flowy3-2
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



static const uint8_t image_data_Flowy32[63] = {
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x03, 0x8e, 0x00, 
    0x06, 0x03, 0x00, 
    0x00, 0x00, 0x00, 
    0x38, 0x00, 0xe0, 
    0x78, 0x00, 0xf0, 
    0x38, 0x00, 0xe0, 
    0x04, 0x01, 0x00, 
    0x0e, 0x03, 0x80, 
    0x1f, 0x07, 0xc0, 
    0x1f, 0x8f, 0xc0, 
    0x0e, 0x03, 0x80, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00
};
const tImage Flowy32 = { image_data_Flowy32, 21, 21,
    8 };

