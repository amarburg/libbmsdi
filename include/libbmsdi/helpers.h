#pragma once


#include "libbmsdi/bmsdi_message.h"

#ifdef __cplusplus
extern "C" {
#endif


// These are convenience wrappers which properly format / set up
// the arguments to some of the commands in the BM SDK.

// Message 0.0:  Set focus
inline BMSDIBuffer *bmAddFocus( BMSDIBuffer *buffer, uint8_t dest, float focus ) {
  BMSDIMessage *msg = bmAddConfigMessage( buffer,
                                          dest, BM_CAT_LENS,
                                          BM_PARAM_FOCUS,
                                          BM_OP_ASSIGN,
                                          BM_TYPE_FIXED16,
                                          1 );
  bmConfigWriteFixed16( msg, focus );

  return (msg ? buffer : NULL);
}

inline BMSDIBuffer *bmFocus( uint8_t dest, float focus ) {
  return bmAddFocus( bmNewBuffer(), dest, focus );
}



// Message 0.1:  Instantantaneous Autofocus
inline BMSDIBuffer *bmAddInstantaneousAutofocus( BMSDIBuffer *buffer, uint8_t dest ) {
  BMSDIMessage *msg = bmAddConfigMessage( buffer, dest, BM_CAT_LENS,
                                          BM_PARAM_INST_AUTOFOCUS,
                                          BM_OP_ASSIGN, BM_TYPE_VOID,
                                          0 );
  return (msg ? buffer : NULL);
}

inline BMSDIBuffer *bmInstantaneousAutofocus( uint8_t dest ) {
  return bmAddInstantaneousAutofocus( bmNewBuffer(), dest );
}


// inline bool bmAddFocus( BMSDIBuffer *buffer, uint8_t dest, float focus ) {
//   BMSDIConfigPacket *config = bmAddConfigPacket( buffer,
//                                 dest, BM_CAT_LENS,
//                                 BM_PARAM_FOCUS,
//                                 BM_OP_ASSIGN,
//                                 BM_TYPE_FIXED16,
//                                 1 );
//   if( !buffer ) return false;
//
//   bmConfigWriteFixed32( config, focus );
//
//   return true;
// }
//
//
//
//   // Helpers for category 0 "Lens"
//   inline BMSDIBuffer *bmInstantaneousAutofocus( uint8_t dest ) {
//     return bmNewConfigPacket( dest, BM_CAT_LENS,
//                                   BM_PARAM_INST_AUTOFOCUS,
//                                   BM_OP_ASSIGN, BM_TYPE_VOID,
//                                   0 );
//   }
//
//   inline BMSDIConfigPacket *bmAddInstantaneousAutofocus( BMSDIBuffer *buffer, uint8_t dest ) {
//     return bmAddConfigPacket( buffer, dest, BM_CAT_LENS,
//                                   BM_PARAM_INST_AUTOFOCUS,
//                                   BM_OP_ASSIGN, BM_TYPE_VOID,
//                                   0 );
//   }
//
//
//
//
//   // Helpers for category 6 "Reference"
//   inline BMSDIBuffer *bmReferenceSource( uint8_t dest, uint8_t i ) {
//     BMSDIBuffer *buffer = bmNewConfigPacket( dest, BM_CAT_REFERENCE,
//                                   BM_PARAM_REF_SOURCE,
//                                   BM_OP_ASSIGN,
//                                   BM_TYPE_INT8,
//                                   1 );
//
//     bmFirstConfigWriteInt8( buffer, i );
//
//     return buffer;
//   }

#ifdef __cplusplus
}
#endif
