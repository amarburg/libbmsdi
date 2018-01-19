
#include <gtest/gtest.h>

#include "libbm_sdi_camera_control/bmsdi.h"

TEST(test_new_cmd_packet, non_zero_length ) {

  const uint8_t dest = 255;
  const int     cmdlen = 10;
  const uint8_t cmd = BM_CMD_CONFIG;

  const int packetlen = sizeof(BMSDIHeader) + cmdlen;

  BMSDIBuffer *packet = bmNewPacket( dest, cmdlen, cmd );

  ASSERT_EQ( packet->len, align32(packetlen) );

  struct BMSDIPacket *p = (struct BMSDIPacket *)packet->data;

  ASSERT_EQ( p->header.dest, dest );
  ASSERT_EQ( p->header.cmd_id, cmd );
  ASSERT_EQ( p->header.cmd_len, 10 );
  ASSERT_EQ( p->header.reserved, 0 );

}
