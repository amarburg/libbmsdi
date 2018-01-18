#pragma once




#define BM_CMD_CONFIG    0

// Defines
#define BM_OP_ASSIGN     0
#define BM_OP_OFFSET     1
//Operation types 2 through 127 are reserved.
//Operation types 128 through 255 are available for device specific purposes.

#define BM_TYPE_VOID     0
#define BM_TYPE_BOOLEAN  0
#define BM_TYPE_INT8     1
#define BM_TYPE_INT16    2
#define BM_TYPE_INT32    3
#define BM_TYPE_INT64    4
#define BM_TYPE_STR      5
// data types 6-127 are Reserved


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
#define BM_PARAM_FOCUS            0
#define BM_PARAM_INST_AUTOFOCUS   1
#define BM_PARAM_APERTURE_FSTOP   2
#define BM_PARAM_APERTURE_NORM    3
#define BM_PARAM_APERTURE_ORD     4
#define BM_PARAM_INST_AUTOAPERTURE 5
#define BM_PARAM_OIS              6
#define BM_PARAM_ZOOM_MM          7
#define BM_PARAM_ZOOM_NORM        8
#define BM_PARAM_ZOOM_CONT        9

// Parameters for category 1 "Video"
#define BM_PARAM_VIDEO_MODE       0
#define BM_PARAM_SENSOR_GAIN      1
#define BM_PARAM_WHITE_BALANCE    2
#define BM_PARAM_AUTO_WB          3
#define BM_PARAM_RESTORE_AUTO_WB  4
#define BM_PARAM_EXPOSURE_US      5
#define BM_PARAM_EXPOSURE_ORD     6
#define BM_PARAM_DYNAMIC_RANGE    7
#define BM_PARAM_VIDEO_SHARPNESS  8
#define BM_PARAM_RECORDING_FORMAT 9
#define BM_PARAM_AUTOEXPOSURE_MODE 10


// Parameters for category 2 "Audio"
// ((I'm not going to use them, so I can't test them...))

// Parameters for category 3 "Output"
#define BM_PARAM_OVERLAY_EN        0
#define BM_PARAM_FRAME_GUIDE_STYLE 1
#define BM_PARAM_FRAME_GUIDE_OPACITY 2
#define BM_PARAM_OVERLAYS        3


// Parameters for category 4 "Display"
//...


// Parameters for category 5 "Tally"
//...


// Parameters for category 6 "Reference"
#define BM_PARAM_REF_SOURCE         0
#define BM_PARAM_REF_OFFSET         1


// Parameters for category 7 "Configuration"
#define BM_PARAM_RTC               0
#define BM_PARAM_LANGUAGE          1
#define BM_PARAM_TIMEZONE          2
#define BM_PARAM_LOCATION          3


// Parameters for category 8 "Colour Correction"
// ...

// Parameters for category 10 "Media"
// ...

// Parameters for category 11 "PTZ Control"
// ...
