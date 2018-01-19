#pragma once


#include "bmsdi.h"

#ifdef __cplusplus
extern "C" {
#endif



inline BMSDIBuffer *bmInstantaneousFocus( uint8_t dest, float focus ) {
  BMSDIBuffer *buffer = bmNewConfigPacket( dest, BM_CAT_LENS,
                                BM_PARAM_FOCUS,
                                BM_OP_ASSIGN,
                                BM_TYPE_FIXED16,
                                0 );

  bmConfigWriteFixed32( buffer, focus );

  return buffer;
}

  // Helpers for category 0 "Lens"
  inline BMSDIBuffer *bmInstantaneousAutofocus( uint8_t dest ) {
    return bmNewConfigPacket( dest, BM_CAT_LENS,
                                  BM_PARAM_INST_AUTOFOCUS,
                                  BM_OP_ASSIGN, BM_TYPE_VOID,
                                  0 );
  }



#ifdef __cplusplus
}
#endif
