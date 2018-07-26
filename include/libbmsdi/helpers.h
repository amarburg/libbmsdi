#pragma once


#include "libbmsdi/bmsdi_message.h"

#ifdef __cplusplus
extern "C" {
#endif


// These are convenience wrappers which properly format / set up
// the arguments to some of the commands in the BM SDK.

#define HELPER_NO_PARAM( name, category, param ) \
  inline BMSDIBuffer *bmAdd##name( BMSDIBuffer *buffer, uint8_t dest ) { \
    BMSDIMessage *msg = bmAddConfigMessage( buffer, dest, category, param, BM_OP_ASSIGN, BM_TYPE_VOID, 0); \
    return (msg ? buffer : NULL); \
  } \
  inline BMSDIBuffer *bm##name( uint8_t dest ) { \
    return bmAdd##name( bmNewBuffer(), dest ); \
  }



#define HELPER_ONE_PARAM( name, category, param, p1type, p1const ) \
  inline BMSDIBuffer *bmAdd##name( BMSDIBuffer *buffer, uint8_t dest, p1type p1 ) { \
    BMSDIMessage *msg = bmAddConfigMessage( buffer, dest, category, param, BM_OP_ASSIGN, p1const, 1); \
    if( !msg ) return NULL; \
    return (msg ? buffer : NULL); \
  } \
  inline BMSDIBuffer *bm##name( uint8_t dest, p1type p1 ) { \
    return bmAdd##name( bmNewBuffer(), dest, p1 ); \
  }




// Message 0.0:  Set focus
// inline BMSDIBuffer *bmAddFocus( BMSDIBuffer *buffer, uint8_t dest, float focus ) {
//   BMSDIMessage *msg = bmAddConfigMessage( buffer,
//                                           dest,
//                                           BM_CAT_LENS,
//                                           BM_PARAM_FOCUS,
//                                           BM_OP_ASSIGN,
//                                           BM_TYPE_FIXED16,
//                                           1 );
//   if( !msg ) return NULL;
//
//   bmConfigWriteFixed16( msg, focus );
//   return buffer;
// }
//
// inline BMSDIBuffer *bmFocus( uint8_t dest, float focus ) {
//   return bmAddFocus( bmNewBuffer(), dest, focus );
// }

HELPER_ONE_PARAM( Focus, BM_CAT_LENS, BM_PARAM_FOCUS, float, BM_TYPE_FIXED16 )

// Message 0.0:  Increment focus
inline BMSDIBuffer *bmAddFocusOffset( BMSDIBuffer *buffer, uint8_t dest, float inc ) {
  BMSDIMessage *msg = bmAddConfigMessage( buffer, dest,
                                          BM_CAT_LENS,
                                          BM_PARAM_FOCUS,
                                          BM_OP_OFFSET,
                                          BM_TYPE_FIXED16,
                                          1 );
  if( !msg ) return NULL;

  bmConfigWriteFixed16( msg, inc );
  return buffer;
}



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
HELPER_NO_PARAM( InstantaneousAutofocus, BM_CAT_LENS, BM_PARAM_INST_AUTOFOCUS )

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
