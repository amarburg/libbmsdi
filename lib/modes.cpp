
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "libbmsdi/helpers.h"

// Made my job slightly harder by not being dependent on Blackmagic SDK

static void setMode( VideoModeStruct mode, uint32_t a, uint32_t b, uint32_t c, uint32_t d  ) {
  mode[0] = a;  // Frame rate
  mode[1] = b;  // Std or M-timing
  mode[2] = c;  // Resolution
  mode[3] = d;  // Progressive/interlaced
  mode[4] = 0;  //Only one choice, YVU
}

bool decodeBMDMode( uint32_t bmMode, VideoModeStruct mode ) {

  if( bmMode == 0x48703239 )  //bmdModeHD1080p2997
    setMode( mode, 30, 1, 3, 0 );
  else {
    fprintf(stderr, "Couldn't decode mode %08x!\n", bmMode );
    return false;
  }

  return true;

}
