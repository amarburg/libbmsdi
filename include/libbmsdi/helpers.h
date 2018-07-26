#pragma once


#include "libbmsdi/bmsdi_message.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define T_TYPE(type) \
//   #if BM_TYPE_BOOLEAN == type \
//     bool \
//   #elif BM_TYPE_INT8 == type \
//     uint8_t \
//   #elif BM_TYPE_FIXED16 == type \
//     float \
//   #else \
//     #error "Unable to figure out type" \
//   #endif

// These are convenience wrappers which properly format / set up
// the arguments to some of the commands in the BM SDK.

#define HELPER_ZERO_PARAM( name, category, param ) \
  inline BMSDIMessage *bmAdd##name( BMSDIBuffer *buffer, uint8_t dest ) { \
    return bmAddConfigMessage( buffer, dest, category, param, BM_OP_ASSIGN, BM_TYPE_VOID, 0); \
  }


// I haven't figured out how to translate between C type (uint8_t)
// and protocol type (BM_TYPE_INT8) inside the #define,
// so for now you must provide both
#define ASSIGN_ONE_PARAM( name, category, param, p1type, p1const ) \
  inline BMSDIMessage *bmAdd##name( BMSDIBuffer *buffer, uint8_t dest, p1type p1 ) { \
    BMSDIMessage *msg = bmAddConfigMessage( buffer, dest, category, param, \
                                BM_OP_ASSIGN, p1const, 1); \
    if( msg ) bmConfigWrite_##p1type( msg, p1 ); \
    return msg; \
  }

#define OFFSET_ONE_PARAM( name, category, param, p1type, p1const ) \
  inline BMSDIMessage *bmAdd##name##Offset( BMSDIBuffer *buffer, uint8_t dest, p1type p1 ) { \
    BMSDIMessage *msg = bmAddConfigMessage( buffer, dest, category, param, \
                                BM_OP_OFFSET, p1const, 1); \
    if( msg ) bmConfigWrite_##p1type( msg, p1 ); \
    return msg; \
  }


//=====

//-- Message 0.0   Focus
ASSIGN_ONE_PARAM( Focus, BM_CAT_LENS, BM_PARAM_FOCUS, float, BM_TYPE_FIXED16 )
OFFSET_ONE_PARAM( Focus, BM_CAT_LENS, BM_PARAM_FOCUS, float, BM_TYPE_FIXED16 )

//-- Message 0.1.  Instantantaneous autofocus
HELPER_ZERO_PARAM( InstantaneousAutofocus, BM_CAT_LENS, BM_PARAM_INST_AUTOFOCUS )




// Message 0.1:  Instantantaneous Autofocus
// inline BMSDIBuffer *bmAddInstantaneousAutofocus( BMSDIBuffer *buffer, uint8_t dest ) {
//   BMSDIMessage *msg = bmAddConfigMessage( buffer, dest,
//                                           BM_CAT_LENS,
//                                           BM_PARAM_INST_AUTOFOCUS,
//                                           BM_OP_ASSIGN,
//                                           BM_TYPE_VOID,
//                                           0 );
//   return (msg ? buffer : NULL);
// }

// inline BMSDIBuffer *bmInstantaneousAutofocus( uint8_t dest ) {
//   return bmAddInstantaneousAutofocus( bmNewBuffer(), dest );
// }


//=== Message 0.4:  Ordinal Aperture
inline BMSDIBuffer *bmAddOrdinalApertureOffset( BMSDIBuffer *buffer, uint8_t dest, int inc ) {
  BMSDIMessage *msg = bmAddConfigMessage( buffer, dest,
                                          BM_CAT_LENS,
                                          BM_PARAM_APERTURE_ORD,
                                          BM_OP_OFFSET,
                                          BM_TYPE_INT16,
                                          1 );
  if( !msg ) return NULL;

  bmConfigWriteInt16( msg, inc );
  return buffer;
}



//=== Helper for 1.1:   Sensor Gain ===
inline BMSDIBuffer *bmAddGainOffset( BMSDIBuffer *buffer, uint8_t dest, int inc ) {
  BMSDIMessage *msg = bmAddConfigMessage( buffer, dest,
                                          BM_CAT_VIDEO,
                                          BM_PARAM_SENSOR_GAIN,
                                          BM_OP_OFFSET,
                                          BM_TYPE_INT8,
                                          1 );
  if( !msg ) return NULL;

  bmConfigWriteInt8( msg, inc );
  return buffer;
}

//=== Helper for 1.6:  Ordinal Shutter Speed ===
inline BMSDIBuffer *bmAddOrdinalShutterOffset( BMSDIBuffer *buffer, uint8_t dest, int inc ) {
  BMSDIMessage *msg = bmAddConfigMessage( buffer, dest,
                                          BM_CAT_VIDEO,
                                          BM_PARAM_EXPOSURE_ORD,
                                          BM_OP_OFFSET,
                                          BM_TYPE_INT16,
                                          1 );
  if( !msg ) return NULL;

  bmConfigWriteInt16( msg, inc );
  return buffer;
}





//== Helpers for category 6 "Reference" ==
inline BMSDIBuffer *bmAddReferenceSource( BMSDIBuffer *buffer, uint8_t dest, uint8_t i ) {
  BMSDIMessage *msg = bmAddConfigMessage( buffer,
                                dest, BM_CAT_REFERENCE,
                                BM_PARAM_REF_SOURCE,
                                BM_OP_ASSIGN,
                                BM_TYPE_INT8,
                                1 );
  bmConfigWriteInt8( msg, i );
  return (msg ? buffer : NULL);
}

#ifdef __cplusplus
}
#endif
