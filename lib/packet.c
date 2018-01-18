
#include <stdlib.h>
#include <string.h>

#include "libbm_sdi_camera_control/bmsdi.h"

struct BMSDIPacket *newPacket( uint8_t packetlen )
{
  // Round up to nearest 32-bit boundary
  uint8_t actuallen = align32( packetlen );

  struct BMSDIPacket *packet = (struct BMSDIPacket *)malloc( actuallen + sizeof(uint8_t) );
  packet->len = actuallen;
  memset( packet->data, 0, actuallen );

  return packet;
}

struct BMSDIPacket *newCommandPacket( uint8_t dest, uint8_t len, uint8_t cmd )
{
  uint8_t packetlen = len + sizeof(struct BMSDIHeader);

  struct BMSDIPacket *out = newPacket( packetlen );
  struct BMSDICmdPacket *packet = (struct BMSDICmdPacket *)out->data;

  packet->header.dest = dest;
  packet->header.cmd_id = cmd;
  packet->header.cmd_len =  len;
  packet->header.reserved = 0;

  return out;
}

struct BMSDIPacket *newConfigPacket( uint8_t dest, uint8_t category, uint8_t parameter,
                              uint8_t op, uint8_t dataType, uint8_t count )
{
  uint8_t datalen = sizeOfType( dataType ) * count;
  uint8_t cmdlen  = datalen + sizeof(struct BMSDIConfigHeader);

  struct BMSDIPacket *out = newCommandPacket( dest, cmdlen, BM_CMD_CONFIG );
  struct BMSDIConfigPacket *packet = (struct BMSDIConfigPacket *)out->data;

  packet->config.category = category;
  packet->config.parameter = parameter;
  packet->config.datatype = dataType;
  packet->config.operation = op;


  return out;
}
