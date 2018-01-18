
#include <gtest/gtest.h>

#include "libbm_sdi_camera_control/bmsdi.h"

TEST(test_new_packet, zero_length) {

  const int packetLen = 10;

  BMSDIPacket *packet = newPacket( packetLen );

  ASSERT_EQ( packet->len, align32(packetLen) );

  // Check that all bytes have been zeroed outo
  for( int i = 0; i < packetLen; i++ ) {
    ASSERT_EQ( packet->data[i], 0 );
  }

}
