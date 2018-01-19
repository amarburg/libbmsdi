
#include <gtest/gtest.h>

#include "libbm_sdi_camera_control/bmsdi.h"

static void checkPacket( BMSDIBuffer *packet, const uint8_t len, const uint8_t answer[] )
{
  ASSERT_EQ( packet->len, len );
  ASSERT_EQ( packet->len, align32(packet->len));

  for( int i = 0; i < len; ++i ) {
    //printf("%d  %x\n", i, packet->data[i]);
    ASSERT_EQ( (uint8_t)packet->data[i], answer[i]);
  }
}


// Based on BM's example "trigger instantaneous auto focus
// on camera 4"
TEST(test_new_config_packet, test_inst_autofocus ) {

  const uint8_t answer[] = {4, 4, 0, 0, 0, 1, 0, 0};
  const uint8_t answerlen = sizeof(answer);
  ASSERT_EQ( answerlen, align32(answerlen) );

    BMSDIBuffer *packet = bmNewConfigPacket( 4,
                              BM_CAT_LENS,
                              BM_PARAM_INST_AUTOFOCUS,
                              BM_OP_ASSIGN, BM_TYPE_VOID,
                              0 );

  checkPacket( packet, answerlen, answer );
}

// BM example "turn on OIS on all cameras"
TEST(test_new_config_packet, test_ois_all_cameras ) {

  const uint8_t answer[] = {255, 5, 0, 0, 0, 6, 0, 0, 1, 0, 0, 0};
  const uint8_t answerlen = sizeof(answer);
  ASSERT_EQ( answerlen, align32(answerlen) );

  BMSDIBuffer *packet = bmNewConfigPacket( 255,
                            BM_CAT_LENS,
                            BM_PARAM_OIS,
                            BM_OP_ASSIGN,
                            BM_TYPE_BOOLEAN,
                            1 );

  bmConfigWriteInt8( packet, 1 );

  checkPacket( packet, answerlen, answer );
}

// BM example "set exposure to 10 ms on camera 4 (10 ms = 10000
//us = 0x00002710)"
TEST(test_new_config_packet, test_set_exposure_on_camera ) {

  const uint8_t answer[] = {4, 8, 0, 0, 1, 5, 3, 0, 0x10, 0x27, 0x0, 0};
  const uint8_t answerlen = sizeof(answer);
  ASSERT_EQ( answerlen, align32(answerlen) );

  BMSDIBuffer *packet = bmNewConfigPacket( 4,
                            BM_CAT_VIDEO,
                            BM_PARAM_EXPOSURE_US,
                            BM_OP_ASSIGN,
                            BM_TYPE_INT32,
                            1 );

  bmConfigWriteInt32( packet, 10000 );

  checkPacket( packet, answerlen, answer );
}
