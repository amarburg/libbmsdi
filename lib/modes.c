
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "libbmsdi/helpers.h"

// Made my job slightly harder by not being dependent on Blackmagic SDK


struct VideoModeRef {
  uint32_t mode;
  uint32_t frameRate;
  uint32_t timing;
  uint32_t resolution;
  uint32_t progressive;
} VideoModeTable[] = {
  {0x48703239, 30, 1, 3, 0}    // bmdModeHD1080p2997
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
