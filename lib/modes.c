
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "libbmsdi/helpers.h"

// Made my job slightly harder by not being dependent on Blackmagic SDK
// params for BM_PARAM_VIDEO_MODE:
// 5 * int8: [0]:  frame rate (24,25,30,50,60)
//           [1]:  0=regular, 1=M-rate
//           [2]:  dimensions
//                    0=NTSC,  1=PAL, 2=720
//                    3=1080, 4=2k, 5=2k DCI,
//                    6=4k, 7=4k DCI
//           [3]:  0=progressize, 1=interlaced
//           [4]:  0=YUV color


//
// n.b. I haven't tested all of these modes.  Good luck!
struct VideoModeRef {
  uint32_t mode;
  uint32_t frameRate;
  uint32_t timing;
  uint32_t resolution;
  uint32_t progressive;
} VideoModeTable[] = {
  //HD1080 modes
  {0x32337073, 24, 1, 3, 0}, // bmdModeHD1080p2398
  {0x32347073, 24, 0, 3, 0}, // bmdModeHD1080p24
  {0x48703235, 25, 0, 3, 0}, // bmdModeHD1080p25
  {0x48703239, 30, 1, 3, 0}, // bmdModeHD1080p2997
  {0x48703330, 30, 0, 3, 0}, // bmdModeHD1080p30
  {0x48693530, 50, 0, 3, 1}, // bmdModeHD1080i50
  {0x48693539, 60, 1, 3, 1}, // bmdModeHD1080i5994
  {0x48693630, 60, 0, 3, 1}, // bmdModeHD1080i6000
  {0x48703530, 50, 0, 3, 0}, // bmdModeHD1080p50
  {0x48703539, 60, 1, 3, 0}, // bmdModeHD1080p5994
  {0x48703630, 60, 0, 3, 0}, // bmdModeHD1080p6000

  // HD720 Modes
  {0x68703530, 50, 0, 2, 0}, // bmdModeHD720p50
  {0x68703539, 60, 1, 2, 0}, // bmdModeHD720p5994
  {0x68703630, 60, 0, 2, 0}, // bmdModeHD720p60

  // 2K Modes
  {0x326B3233, 24, 1, 4, 0}, // bmdMode2k2398
  {0x326B3234, 24, 0, 4, 0}, // bmdMode2k24
  {0x326B3235, 25, 0, 4, 0}, // bmdMode2k25

  // 4K Modes
  {0x346B3233, 24, 1, 6, 0}, // bmdMode4K2160p2398
  {0x346B3234, 24, 0, 6, 0}, // bmdMode4K2160p24
  {0x346B3235, 25, 0, 6, 0}, // bmdMode4K2160p25
  {0x346B3239, 30, 1, 6, 0}, // bmdMode4K2160p2997
  {0x346B3330, 30, 0, 6, 0}, // bmdMode4K2160p30
  {0x346B3530, 50, 0, 6, 0}, // bmdMode4K2160p50
  {0x346B3539, 60, 1, 6, 0}, // bmdMode4K2160p5994
  {0x346B3630, 60, 0, 6, 0}  // bmdMode4K2160p60
};



bool decodeBMDMode( uint32_t bmMode, VideoModeStruct mode ) {

  for( unsigned int i = 0; i < (sizeof(VideoModeTable)/sizeof(struct VideoModeRef)); ++i ) {
    if( bmMode == VideoModeTable[i].mode ) {

      mode[0] = VideoModeTable[i].frameRate;
      mode[1] = VideoModeTable[i].timing;
      mode[2] = VideoModeTable[i].resolution;
      mode[3] = VideoModeTable[i].progressive;
      mode[4] = 0;  //Only one choice, YVU

      return true;
    }
  }

  fprintf(stderr, "Couldn't decode mode %08x!\n", bmMode );
  return false;
}
