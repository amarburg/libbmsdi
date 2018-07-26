#pragma once


#include "libbmsdi/bmsdi_message.h"

#ifdef __cplusplus
extern "C" {
#endif


// These are convenience wrappers which properly format / set up
// the arguments to some of the commands in the BM SDK.

#define HELPER_ZERO_PARAM( name, category, param ) \
  inline BMSDIMessage *bmAdd##name( BMSDIBuffer *buffer, uint8_t dest ) { \
    return bmAddConfigMessage( buffer, dest, category, param, BM_OP_ASSIGN, BM_TYPE_VOID, 0); \
  }


// I haven't figured out how to translate between C type (uint8_t)
// and protocol type (BM_TYPE_INT8) inside the #define,
// so for now you must provide both
#define HELPER_ONE_PARAM( name, category, param, p1type, p1const ) \
  inline BMSDIMessage *bmAdd##name( BMSDIBuffer *buffer, uint8_t dest, p1type p1 ) { \
    BMSDIMessage *msg = bmAddConfigMessage( buffer, dest, category, param, \
                                BM_OP_ASSIGN, p1const, 1); \
    if( msg ) bmConfigWrite_##p1type( msg, p1 ); \
    return msg; \
  }\
  \
  inline BMSDIMessage *bmAdd##name##Offset( BMSDIBuffer *buffer, uint8_t dest, p1type p1 ) { \
    BMSDIMessage *msg = bmAddConfigMessage( buffer, dest, category, param, \
                                BM_OP_OFFSET, p1const, 1); \
    if( msg ) bmConfigWrite_##p1type( msg, p1 ); \
    return msg; \
  }


//=====

//-- Message 0.0   Focus
HELPER_ONE_PARAM( Focus, BM_CAT_LENS, BM_PARAM_FOCUS, float, BM_TYPE_FIXED16 )

//-- Message 0.1.  Instantantaneous autofocus
HELPER_ZERO_PARAM( InstantaneousAutofocus, BM_CAT_LENS, BM_PARAM_INST_AUTOFOCUS )

//=== Message 0.4:  Ordinal Aperture
HELPER_ONE_PARAM( OrdinalAperture, BM_CAT_LENS, BM_PARAM_APERTURE_ORD, uint16_t, BM_TYPE_INT16 )

//=== Helper for 1.1:   Sensor Gain ===
HELPER_ONE_PARAM( SensorGain, BM_CAT_VIDEO, BM_PARAM_SENSOR_GAIN, uint8_t, BM_TYPE_INT8 )

//=== Helper for 1.6:  Ordinal Shutter Speed ===
HELPER_ONE_PARAM( OrginalShutter, BM_CAT_VIDEO, BM_PARAM_EXPOSURE_ORD, uint16_t, BM_TYPE_INT16 )

//== Helpers for category 6 "Reference" ==
HELPER_ONE_PARAM( ReferenceSource, BM_CAT_REFERENCE, BM_PARAM_REF_SOURCE, uint8_t, BM_TYPE_INT8 )



#ifdef __cplusplus
}
#endif
