
#include <gtest/gtest.h>

#include "libbm_sdi_camera_control/bmsdi.h"


// Based on BM's example "trigger instantaneous auto focus
// on camera 4"
TEST(test_new_config_packet, testData ) {

  const uint8_t answer[] = {4, 4, 0, 0, 0, 1, 0, 0};
  const uint8_t answerlen = sizeof(answer);

  ASSERT_EQ( answerlen, align32(answerlen) );

    BMSDIPacket *packet = newConfigPacket( 4,
                              BM_CAT_LENS,
                              BM_PARAM_INST_AUTOFOCUS,
                              BM_OP_ASSIGN, BM_TYPE_VOID,
                              0 );

    ASSERT_EQ( packet->len, answerlen );

    for( int i = 0; i < answerlen; ++i ) {
      ASSERT_EQ( (uint8_t)packet->data[i], answer[i]);
    }

}
