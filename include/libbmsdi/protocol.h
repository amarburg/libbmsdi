#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Constants for the various fields in the BM SDI Camera Control Protocol

// Every message packet consist of a three byte header followed by an
// optional variable length data block.  The maximum packet size is 64 bytes
//
// Up to 32 messages may be concatenated and transmitted in one blanking
// packet up to a maximum of 255 bytes payload. Under most circumstances,
// this should allow all messages to be sent with a maximum of one frame
// latency.
//
// Format:
//
//   [0]    Destination device (uint8)
//   [1]    Command length (unit8).  Does not in clude header or trailing padding bytes
//   [2]    Command id (uint8)
//   [3]    reserved
//   [*]    Command data (uint[])
//   [*]    Padding.  Messages must be padded to a 32bit boundary with 0x0 bytes


#define BM_CMD_CONFIG    0      // Command 0:  Change configuration

// Defines
#define BM_OP_ASSIGN     0      // Operation 0:  Set value
#define BM_OP_OFFSET     1      // Operation 1:  Offset/toggle
//Operation types 2 through 127 are reserved.
//Operation types 128 through 255 are available for device specific purposes.

#define BM_TYPE_VOID     0      // "A void value is represented as a boolean
                                // array of length zero.  The data field is
                                // a 8 bit value with 0 meaning false and
                                // all other values meaning true."
#define BM_TYPE_BOOLEAN  0
#define BM_TYPE_INT8     1      // Data elements are signed bytes
#define BM_TYPE_INT16    2      // Data elements are signed 16 bit values
#define BM_TYPE_INT32    3      // Data elements are signed 32bit values
#define BM_TYPE_INT64    4      // Data elements are signed 64bit values
#define BM_TYPE_STR      5      // Data elements represent a UTF-8 string with no terminating character
// data types 6-127 are Reserved
#define BM_TYPE_FIXED16  128    // Data elements are signed 16 bit integers
                                // representing a real number with 5 bits
                                // for the integer component and 11 bits for
                                // the fractional component. The fixed point
                                // representation is equal to the real value
                                // multiplied by 2^11.

inline int16_t floatToFixed16( float i )
{
  return (i * (0x01<<11));
}

// Configuration categories
#define BM_CAT_LENS       0
#define BM_CAT_VIDEO      1
#define BM_CAT_AUDIO      2
#define BM_CAT_OUTPUT     3
#define BM_CAT_DISPLAY    4
#define BM_CAT_TALLY      5
#define BM_CAT_REFERENCE  6
#define BM_CAT_CONFIG     7
#define BM_CAT_COLOR      8
#define BM_CAT_COLOUR     8
#define BM_CAT_MEDIA      9
#define BM_CAT_PTZ       10


// Parameters for category 0 "Lens"
#define BM_PARAM_FOCUS            0     // fixed16:   0.0=near, 1.0=far
#define BM_PARAM_INST_AUTOFOCUS   1     // void
#define BM_PARAM_APERTURE_FSTOP   2     // fixed16:  aperture value with fstop = sqrt(2^AV)
#define BM_PARAM_APERTURE_NORM    3     // fixed16:  0.0=smallest, 1.0=largest
#define BM_PARAM_APERTURE_ORD     4     // int16:    Steps through f-stops 0=minimum, n=maximum
#define BM_PARAM_INST_AUTOAPERTURE 5    // void
#define BM_PARAM_OIS              6     // boolean:  true=Optical image stabilization enabled
#define BM_PARAM_ZOOM_MM          7
#define BM_PARAM_ZOOM_NORM        8
#define BM_PARAM_ZOOM_CONT        9

// Parameters for category 1 "Video"
#define BM_PARAM_VIDEO_MODE       0     // 5 * int8: [0]:  frame rate (24,25,30,50,60)
                                        //           [1]:  0=regular, 1=M-rate
                                        //           [2]:  dimensions
                              					//                    0=NTSC,  1=PAL, 2=720
                              					//                    3=1080, 4=2k, 5=2k DCI,
                              					//                    6=4k, 7=4k DCI
                                        //           [3]:  0=progressize, 1=interlaced
                                        //           [4]:  0=YUV color
                                        //
                                        //  See decodeBMDMode() to made BM SDK BMDisplayMode to this structure
                                        //
#define BM_PARAM_SENSOR_GAIN      1     // int8:    sensor gain (1x - 16x).   1 = -12db; 2 = -6db; 4 = 0 db; 8 = +6db; 16 = +12db
#define BM_PARAM_WHITE_BALANCE    2     // 2 * int16:  color temp (2500-10000);
                                        //             tint -50 50
#define BM_PARAM_AUTO_WB          3     // void:     set auto white balance
#define BM_PARAM_RESTORE_AUTO_WB  4     // void
#define BM_PARAM_EXPOSURE_US      5     // int32:   time in us (1-42000)
#define BM_PARAM_EXPOSURE_ORD     6     // int16:   Steps through exposure value
                                        //          min=0, max=n
#define BM_PARAM_DYNAMIC_RANGE    7     // int8:    0=film; 1=video
#define BM_PARAM_VIDEO_SHARPNESS  8     // int8:    0-3
#define BM_PARAM_RECORDING_FORMAT 9     // 5 * int16:[0]:  file frame rate
                                        //           [1]:  sensor frame rate
                                        //           [2]:  frame width (pixels)
                                        //           [3]:  frame height (pixels)
                                        //           [4]:  flags:
#define BM_PARAM_AUTOEXPOSURE_MODE 10   // int8:  0=Manual, 1=Iris, 2=Shutter,
                                        //        3=Iris + Shutter
                                        //        4=Shutter + Iris

#define BM_PARAM_SHUTTER_SPEED     12   // int32

// Parameters for category 2 "Audio"
// ((I'm not going to use them, so I can't test them...))

// Parameters for category 3 "Output"
#define BM_PARAM_OVERLAY_EN        0    // uint16 bit field:  bit 0=status, bit 1=frame guides
#define BM_PARAM_FRAME_GUIDE_STYLE 1    // int8: [0]:  Frame guides style
#define BM_PARAM_FRAME_GUIDE_OPACITY 2  // fixed16:    0.0=transparent, 1.0=opaque
#define BM_PARAM_OVERLAYS        3      // (replaces .1 and .2 above)


// Parameters for category 4 "Display"
#define BM_PARAM_ZEBRA_LEVEL     2


// Parameters for category 5 "Tally"
//...


// Parameters for category 6 "Reference"
#define BM_PARAM_REF_SOURCE         0   // int8:  0=internal, 1=program, 2=external
#define BM_PARAM_REF_OFFSET         1   // int32:  +/- offset in pixels

#define BM_REF_SOURCE_INTERNAL      0
#define BM_REF_SOURCE_PROGRAM       1
#define BM_REF_SOURCE_EXTERNAL      2


// Parameters for category 7 "Configuration"
#define BM_PARAM_RTC               0    // 2*int32:  [0] time as HHMMSSFF BCD
                                        //           [1] date as YYYYMMDD BCD
#define BM_PARAM_LANGUAGE          1
#define BM_PARAM_TIMEZONE          2    // int32:  minutes offset from UTC
#define BM_PARAM_LOCATION          3


// Parameters for category 8 "Colour Correction"
// ...

// Parameters for category 10 "Media"
// ...

// Parameters for category 11 "PTZ Control"
// ...


#ifdef __cplusplus
}
#endif
