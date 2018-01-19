
#include <gtest/gtest.h>

#include "libbm_sdi_camera_control/bmsdi.h"

#include "libbm_sdi_camera_control/helpers.h"



static void checkPacket( BMSDIPacket *packet, const uint8_t len, const uint8_t answer[] )
{
  ASSERT_EQ( len, align32(len) );

  uint8_t *data = (uint8_t *)packet;

  for( int i = 0; i < len; ++i ) {
    //printf("%d  %x\n", i, packet->data[i]);
    ASSERT_EQ( data[i], answer[i]);
  }
}

// Shorthand for "check the first packet in the buffer"
static void checkBuffer( BMSDIBuffer *buffer, const uint8_t len, const uint8_t answer[] )
{
  ASSERT_EQ( buffer->len, align32(buffer->len));
  ASSERT_EQ( buffer->len, len );

  checkPacket( (BMSDIPacket *)buffer->data, len, answer );
}


// Based on BM's example "trigger instantaneous auto focus
// on camera 4"
TEST(test_new_config_packet, test_inst_autofocus ) {

  const uint8_t camAddr = 4;
  const uint8_t answer[] = {4, 4, 0, 0, 0, 1, 0, 0};

  {
    BMSDIBuffer *buffer = bmNewConfigPacket( camAddr,
                              BM_CAT_LENS,
                              BM_PARAM_INST_AUTOFOCUS,
                              BM_OP_ASSIGN, BM_TYPE_VOID,
                              0 );

    checkBuffer( buffer, sizeof(answer), answer );

    free(buffer);
  }

  // Try this version
  {
    BMSDIBuffer *buffer = bmAllocBuffer();
    BMSDIConfigPacket *packet = bmAddConfigPacket( buffer,
                              camAddr,
                              BM_CAT_LENS,
                              BM_PARAM_INST_AUTOFOCUS,
                              BM_OP_ASSIGN, BM_TYPE_VOID,
                              0 );

    ASSERT_TRUE( packet != NULL );

    // this also works because there's only one packet in the buffer
    checkBuffer( buffer, sizeof(answer), answer );
    checkPacket( (BMSDIPacket *)packet, sizeof(answer), answer );

    free(buffer);
  }

  // Try this version
  {
    BMSDIBuffer *buffer = bmInstantaneousAutofocus( camAddr );

    ASSERT_TRUE( buffer != NULL );

    // this also works because there's only one packet in the buffer
    checkBuffer( buffer, sizeof(answer), answer );

    free(buffer);
  }

  // And this version
  {
    BMSDIBuffer *buffer = bmAllocBuffer();
    ASSERT_TRUE( buffer != NULL );

    BMSDIConfigPacket *packet = bmAddInstantaneousAutofocus( buffer, camAddr );

    ASSERT_TRUE( packet != NULL );

    // this also works because there's only one packet in the buffer
    checkBuffer( buffer, sizeof(answer), answer );
    checkPacket( (BMSDIPacket *)packet, sizeof(answer), answer );

    free(buffer);
  }

}

// BM example "turn on OIS on all cameras"
TEST(test_new_config_packet, test_ois_all_cameras ) {

  const uint8_t answer[] = {255, 5, 0, 0, 0, 6, 0, 0, 1, 0, 0, 0};

  BMSDIBuffer *buffer = bmNewConfigPacket( 255,
                            BM_CAT_LENS,
                            BM_PARAM_OIS,
                            BM_OP_ASSIGN,
                            BM_TYPE_BOOLEAN,
                            1 );

  bmFirstConfigWriteInt8( buffer, 1 );

  checkBuffer( buffer, sizeof(answer), answer );

  free(buffer);
}

// BM example "set exposure to 10 ms on camera 4 (10 ms = 10000
//us = 0x00002710)"
TEST(test_new_config_packet, test_set_exposure_on_camera ) {

  const uint8_t answer[] = {4, 8, 0, 0, 1, 5, 3, 0, 0x10, 0x27, 0x0, 0};

  BMSDIBuffer *buffer = bmNewConfigPacket( 4,
                            BM_CAT_VIDEO,
                            BM_PARAM_EXPOSURE_US,
                            BM_OP_ASSIGN,
                            BM_TYPE_INT32,
                            1 );

  bmFirstConfigWriteInt32( buffer, 10000 );

  checkBuffer( buffer, sizeof(answer), answer );

  free(buffer);
}


// BM example "dd 15% to zebra level (15 % = 0.15 f = 0x0133 fp)"
TEST(test_new_config_packet, test_increment_zebra_level ) {

  const uint8_t answer[] = {4, 6, 0, 0, 4, 2, 128, 1, 0x33, 0x01, 0, 0};


  BMSDIBuffer *buffer = bmNewConfigPacket( 4,
                            BM_CAT_DISPLAY,
                            BM_PARAM_ZEBRA_LEVEL,
                            BM_OP_OFFSET,
                            BM_TYPE_FIXED16,
                            1 );

  bmFirstConfigWriteFixed32( buffer, 0.15 );

  checkBuffer( buffer, sizeof(answer), answer );
}
