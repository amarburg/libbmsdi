
#include <gtest/gtest.h>

#include "libbmsdi/bmsdi_message.h"
#include "libbmsdi/helpers.h"



static void checkMessage( BMSDIMessage *msg, const uint8_t len, const uint8_t answer[] )
{
  ASSERT_EQ( len, align32(len) );

  uint8_t *data = (uint8_t *)msg;

  for( int i = 0; i < len; ++i ) {
    ASSERT_EQ( answer[i], data[i]) << "In message at byte " << i;
  }
}

static void checkMessageInBuffer( BMSDIBuffer *buffer, int id, const uint8_t len, const uint8_t answer[] )
{
  // Add code to walk through buffer to find id'th message in buffer
  ASSERT_EQ(id, 0);

  // TODO  Add capacity to walk through a buffer

  checkMessage( (struct BMSDIMessage *)buffer->data, len, answer );
}


// Based on BM's example "trigger instantaneous auto focus
// on camera 4"
TEST(TestConfigMessage, TestInstAutofocus ) {

  const uint8_t camAddr = 4;
  const uint8_t answer[] = {camAddr, 4, 0, 0, 0, 1, 0, 0};

  // Test message in packet
  {
    BMSDIBuffer *buffer = bmNewBuffer();
    BMSDIMessage *msg = bmAddConfigMessage( buffer,
                                            camAddr,
                                            BM_CAT_LENS,
                                            BM_PARAM_INST_AUTOFOCUS,
                                            BM_OP_ASSIGN, BM_TYPE_VOID,
                                            0 );

    ASSERT_EQ( buffer->len, align32(buffer->len));
    ASSERT_EQ( buffer->len, sizeof(answer) );

    // this also works because there's only one packet in the buffer
    checkMessageInBuffer( buffer, 0, sizeof(answer), answer );

    free(buffer);
  }

  // Try this helper
  {
    BMSDIBuffer *buffer = bmInstantaneousAutofocus( camAddr );

    ASSERT_TRUE( buffer != NULL );

    // this also works because there's only one packet in the buffer
    checkMessageInBuffer( buffer, 0, sizeof(answer), answer );

    free(buffer);
  }

  // And this helper
  {
    BMSDIBuffer *buffer = bmNewBuffer();
    bmAddInstantaneousAutofocus( buffer, camAddr );

    ASSERT_TRUE( buffer != NULL );

    // this also works because there's only one packet in the buffer
    checkMessageInBuffer( buffer, 0, sizeof(answer), answer );

    free(buffer);
  }


}


// BM example packet:  "turn on OIS on all cameras"
// TEST(TestNewConfigPacket, TestOISAllCameras ) {
//
//   const uint8_t answer[] = {255, 5, 0, 0, 0, 6, 0, 0, 1, 0, 0, 0};
//
//   BMSDIBuffer *buffer = bmNewConfigPacket( 255,
//                             BM_CAT_LENS,
//                             BM_PARAM_OIS,
//                             BM_OP_ASSIGN,
//                             BM_TYPE_BOOLEAN,
//                             1 );
//
//   bmFirstConfigWriteInt8( buffer, 1 );
//
//   checkFirstPacketInBuffer( buffer, sizeof(answer), answer );
//
//   free(buffer);
// }
//
// // BM example "set exposure to 10 ms on camera 4 (10 ms = 10000
// //us = 0x00002710)"
// TEST(TestNewConfigPacket, TestSetExposureOnCamera ) {
//
//   const uint8_t answer[] = {4, 8, 0, 0, 1, 5, 3, 0, 0x10, 0x27, 0x0, 0};
//
//   BMSDIBuffer *buffer = bmNewConfigPacket( 4,
//                             BM_CAT_VIDEO,
//                             BM_PARAM_EXPOSURE_US,
//                             BM_OP_ASSIGN,
//                             BM_TYPE_INT32,
//                             1 );
//
//   bmFirstConfigWriteInt32( buffer, 10000 );
//
//   checkFirstPacketInBuffer( buffer, sizeof(answer), answer );
//
//   free(buffer);
// }
//
//
// // BM example "dd 15% to zebra level (15 % = 0.15 f = 0x0133 fp)"
// TEST(TestNewConfigPacket, TestIncremenetZebraLevel ) {
//
//   const uint8_t answer[] = {4, 6, 0, 0, 4, 2, 128, 1, 0x33, 0x01, 0, 0};
//
//
//   BMSDIBuffer *buffer = bmNewConfigPacket( 4,
//                             BM_CAT_DISPLAY,
//                             BM_PARAM_ZEBRA_LEVEL,
//                             BM_OP_OFFSET,
//                             BM_TYPE_FIXED16,
//                             1 );
//
//   bmFirstConfigWriteFixed32( buffer, 0.15 );
//
//   checkFirstPacketInBuffer( buffer, sizeof(answer), answer );
// }
