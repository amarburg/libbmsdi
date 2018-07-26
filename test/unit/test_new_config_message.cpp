
#include <gtest/gtest.h>

#include "libbmsdi/bmsdi_message.h"
#include "libbmsdi/helpers.h"



static void checkMessage( BMSDIMessage *msg, const uint8_t len, const uint8_t answer[] )
{
  //ASSERT_EQ( len, align32(len) );

  uint8_t *data = (uint8_t *)msg;

  for( int i = 0; i < len; ++i ) {
    ASSERT_EQ( answer[i], data[i]) << "In message at byte " << i;
  }
}

static void checkMessageInBuffer( BMSDIBuffer *buffer, int idx, const uint8_t len, const uint8_t answer[] )
{
  BMSDIMessage *msg = bmMessageAt(buffer,idx);
  ASSERT_TRUE(msg != NULL);

  checkMessage( msg, len, answer );
}


// Based on BM's example "trigger instantaneous auto focus
// on camera 4"
TEST(TestConfigMessage, TestInstAutofocus ) {

  const uint8_t camAddr = 4;
  const uint8_t afMsg[] = {camAddr, 4, 0, 0, 0, 1, 0, 0};

  // Test message in packet
  {
    BMSDIBuffer *buffer = bmNewBuffer();
    bmAddConfigMessage( buffer,
                        camAddr,
                        BM_CAT_LENS,
                        BM_PARAM_INST_AUTOFOCUS,
                        BM_OP_ASSIGN, BM_TYPE_VOID,
                        0 );

    ASSERT_EQ( buffer->len, align32(buffer->len));
    ASSERT_EQ( buffer->len, sizeof(afMsg) );

    // this also works because there's only one packet in the buffer
    checkMessageInBuffer( buffer, 0, sizeof(afMsg), afMsg );

    free(buffer);
  }

  // And this helper
  {
    BMSDIBuffer *buffer = bmNewBuffer();
    bmAddInstantaneousAutofocus( buffer, camAddr );

    ASSERT_TRUE( buffer != NULL );

    // this also works because there's only one packet in the buffer
    checkMessageInBuffer( buffer, 0, sizeof(afMsg), afMsg );

    free(buffer);
  }

  // Define a another message which we can combine into a multi-message packet

  // Defines a focus=0.0 request
  const uint8_t focusMsg[] = {camAddr, 6, 0, 0, 0, 0, 128, 0, 0, 0};
  // Try this helper
  {
    BMSDIBuffer *buffer = bmNewBuffer();
    bmAddFocus( buffer, camAddr, 0.0 );

    ASSERT_TRUE( buffer != NULL );

    // this also works because there's only one packet in the buffer
    checkMessageInBuffer( buffer, 0, sizeof(focusMsg), focusMsg );

    free(buffer);
  }

  // Stack two requests
  {
    BMSDIBuffer *buffer = bmNewBuffer();
    BMSDIMessage *msg = bmAddInstantaneousAutofocus( buffer, camAddr );
    ASSERT_TRUE( msg != NULL );

    msg = bmAddFocus( buffer, camAddr, 0.0 );
    ASSERT_TRUE( msg != NULL );

    // this also works because there's only one packet in the buffer
    checkMessageInBuffer( buffer, 0, sizeof(afMsg), afMsg );
    checkMessageInBuffer( buffer, 1, sizeof(focusMsg), focusMsg );

    free(buffer);
  }

  // Fill a buffer
  {
    BMSDIBuffer *buffer = bmNewBuffer();

    int msgSize = align32( sizeof(afMsg) );
    int count = 0;

    for( ; ((count+1)*msgSize) < MAX_BUFFER_LEN; count++ ) {
      // These should all succeed
      struct BMSDIMessage *result = bmAddInstantaneousAutofocus( buffer, camAddr );
      ASSERT_TRUE( result != NULL );
    }

    // This one will fail
    struct BMSDIMessage *result = bmAddInstantaneousAutofocus( buffer, camAddr );
    ASSERT_TRUE( result == NULL );

    for( int i = 0; i < (count-1); i++ ) {
      checkMessageInBuffer( buffer, i, sizeof(afMsg), afMsg );
    }

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
