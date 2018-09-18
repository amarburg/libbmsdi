#pragma once

#include "bmsdi_message.h"

#ifdef __cplusplus
extern "C" {
#endif

// Convenience wrappers which properly format / set up
// the arguments to some of the commands in the BM SDK.

#define HELPER_ZERO_PARAM( name, category, param ) \
  inline struct BMSDIMessage *bmAdd##name( struct BMSDIBuffer *buffer, uint8_t camNum ) { \
    return bmAddConfigMessage( buffer, camNum, category, param, BM_OP_ASSIGN, BM_TYPE_VOID, 0); \
  }


// I haven't figured out how to translate between C type (uint8_t)
// and protocol type (BM_TYPE_INT8) inside the #define,
// so for now you must provide both
#define HELPER_ONE_PARAM( name, category, param, p1type, p1const ) \
  inline struct BMSDIMessage *bmAdd##name( struct BMSDIBuffer *buffer, uint8_t camNum, p1type p1 ) { \
    struct BMSDIMessage *msg = bmAddConfigMessage( buffer, camNum, category, param, \
                                BM_OP_ASSIGN, p1const, 1); \
    if( msg ) bmConfigWrite_##p1type( msg, p1 ); \
    return msg; \
  }\
  \
  inline struct BMSDIMessage *bmAdd##name##Offset( struct BMSDIBuffer *buffer, uint8_t camNum, p1type p1 ) { \
    struct BMSDIMessage *msg = bmAddConfigMessage( buffer, camNum, category, param, \
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
HELPER_ONE_PARAM( OrdinalAperture, BM_CAT_LENS, BM_PARAM_APERTURE_ORD, int16_t, BM_TYPE_INT16 )

//=== Helper for 1.1:   Sensor Gain ===
HELPER_ONE_PARAM( SensorGain, BM_CAT_VIDEO, BM_PARAM_SENSOR_GAIN, int8_t, BM_TYPE_INT8 )

//=== Helper for 1.6:  Ordinal Shutter Speed ===
HELPER_ONE_PARAM( OrdinalShutter, BM_CAT_VIDEO, BM_PARAM_EXPOSURE_ORD, int16_t, BM_TYPE_INT16 )

//== Helpers for category 6 "Reference" ==
HELPER_ONE_PARAM( ReferenceSource, BM_CAT_REFERENCE, BM_PARAM_REF_SOURCE, int8_t, BM_TYPE_INT8 )



//==Helper for 1.0:  Set Video Mode ==

struct VideoModeRef {
  uint32_t mode;   // Equal to tje BMDDisplayMode enum!
  uint8_t intFrameRate; // | These four parameters correspond to
  uint8_t timing;       // | four of the five parameters to the
  uint8_t resolution;   // | SDI protocol message for setting the
  uint8_t progressive;  // | videe mode
  unsigned int width, height;
  float    frameRate;
};

const struct VideoModeRef *decodeBMDMode( uint32_t bmMode );

// Uses the 32-bit symbols from DeckLinkAPIModes.h
inline struct BMSDIMessage *bmAddVideoMode( struct BMSDIBuffer *buffer, uint8_t camNum, int32_t mode )
{
  struct BMSDIMessage *msg = bmAddConfigMessage( buffer, camNum,
                              BM_CAT_VIDEO, BM_PARAM_VIDEO_MODE,
                              BM_OP_ASSIGN, BM_TYPE_INT8, 5);
  if( !msg ) return msg;

  const struct VideoModeRef *vms = decodeBMDMode( mode );
  if( vms == NULL ) return msg;

  bmConfigWriteInt8At( msg, 0, vms->intFrameRate );
  bmConfigWriteInt8At( msg, 1, vms->timing );
  bmConfigWriteInt8At( msg, 2, vms->resolution );
  bmConfigWriteInt8At( msg, 3, vms->progressive );
  bmConfigWriteInt8At( msg, 4, 0 );


  return msg;
}

//-- Message 1.2:  White Balance
inline struct BMSDIMessage *bmAddWhiteBalance( struct BMSDIBuffer *buffer, uint8_t camNum, int16_t colorTemp, int16_t tint )
{
  struct BMSDIMessage *msg = bmAddConfigMessage( buffer, camNum,
                              BM_CAT_VIDEO, BM_PARAM_WHITE_BALANCE,
                              BM_OP_ASSIGN, BM_TYPE_INT16, 2);
  if( !msg ) return msg;

  if( colorTemp < 2500 ) colorTemp = 2500;
  if( colorTemp > 10000 ) colorTemp = 10000;

  bmConfigWriteInt16At( msg, 0, colorTemp );   // Color temp  2500 to 10000
  bmConfigWriteInt16At( msg, 1, tint );           // Tint -50 to 50

  return msg;
}

inline struct BMSDIMessage *bmAddWhiteBalanceOffset( struct BMSDIBuffer *buffer, uint8_t camNum, int16_t colorTempOffset, int16_t tintOffset )
{
  struct BMSDIMessage *msg = bmAddConfigMessage( buffer, camNum,
                              BM_CAT_VIDEO, BM_PARAM_WHITE_BALANCE,
                              BM_OP_OFFSET, BM_TYPE_INT16, 2);
  if( !msg ) return msg;

  bmConfigWriteInt16At( msg, 0, colorTempOffset );   // Color temp  2500 to 10000
  bmConfigWriteInt16At( msg, 1, tintOffset );                 // Tint -50 to 50

  return msg;
}

//-- Message 1.3:  AutoWhiteBalance
HELPER_ZERO_PARAM( AutoWhiteBalance, BM_CAT_VIDEO, BM_PARAM_AUTO_WB )

//-- Message 1.4:  Restorewhitebalance
HELPER_ZERO_PARAM( RestoreWhiteBalance, BM_CAT_VIDEO, BM_PARAM_RESTORE_AUTO_WB )


#ifdef __cplusplus
}
#endif
