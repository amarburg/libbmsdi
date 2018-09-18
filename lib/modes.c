
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
const struct VideoModeRef VideoModeTable[] = {
  //HD1080 modes
  {0x32337073, 24, 1, 3, 0, 1920, 1080, 23.98 },
  {0x32347073, 24, 0, 3, 0, 1920, 1080, 24.0  },
  {0x48703235, 25, 0, 3, 0, 1920, 1080, 25.0 },
  {0x48703239, 30, 1, 3, 0, 1920, 1080, 29.97 },
  {0x48703330, 30, 0, 3, 0, 1920, 1080, 30.0 },
  {0x48693530, 50, 0, 3, 1, 1920, 1080, 50.0 },
  {0x48693539, 60, 1, 3, 1, 1920, 1080, 59.94 },
  {0x48693630, 60, 0, 3, 1, 1920, 1080, 60.0 },
  {0x48703530, 50, 0, 3, 0, 1920, 1080, 50.0 },
  {0x48703539, 60, 1, 3, 0, 1920, 1080, 59.94 },
  {0x48703630, 60, 0, 3, 0, 1920, 1080, 60.0 },

  // HD720 Modes
  {0x68703530, 50, 0, 2, 0, 1280, 720, 50 },
  {0x68703539, 60, 1, 2, 0, 1280, 720, 5994 },
  {0x68703630, 60, 0, 2, 0, 1280, 720, 60 },

  // 2K Modes
  {0x326B3233, 24, 1, 4, 0, 2048, 1080, 23.98 },
  {0x326B3234, 24, 0, 4, 0, 2048, 1080, 24.0  },
  {0x326B3235, 25, 0, 4, 0, 2048, 1080, 25.0  },

  // 4K Modes
  {0x346B3233, 24, 1, 6, 0, 4096, 2160, 23.98 },
  {0x346B3234, 24, 0, 6, 0, 4096, 2160, 24.0  },
  {0x346B3235, 25, 0, 6, 0, 4096, 2160, 25.0  },
  {0x346B3239, 30, 1, 6, 0, 4096, 2160, 29.97 },
  {0x346B3330, 30, 0, 6, 0, 4096, 2160, 30.0  },
  {0x346B3530, 50, 0, 6, 0, 4096, 2160, 50.0  },
  {0x346B3539, 60, 1, 6, 0, 4096, 2160, 59.94 },
  {0x346B3630, 60, 0, 6, 0, 4096, 2160, 60.0  }
};



const struct VideoModeRef *decodeBMDMode( uint32_t bmMode ) {

  for( unsigned int i = 0; i < (sizeof(VideoModeTable)/sizeof(struct VideoModeRef)); ++i ) {
    if( bmMode == VideoModeTable[i].mode ) {
      return &(VideoModeTable[i]);
    }
  }

  return NULL;
}
