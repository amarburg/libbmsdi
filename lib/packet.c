
#include <stdlib.h>
#include <string.h>

#include "libbm_sdi_camera_control/bmsdi.h"

static uint8_t sizeOfType( uint8_t t ) {
  switch( t ) {
  case BM_TYPE_BOOLEAN:
  case BM_TYPE_INT8:
  case BM_TYPE_STR:
      return 1;
  case BM_TYPE_INT16:
      return 2;
  case BM_TYPE_INT32:
      return 4;
  case BM_TYPE_INT64:
      return 8;

  default:
      return 0;
  }
}

struct BMSDIBuffer *newPacket( uint8_t packetlen )
{
  // Round up to nearest 32-bit boundary
  uint8_t actuallen = align32( packetlen );

  struct BMSDIBuffer *packet = (struct BMSDIBuffer *)malloc( actuallen + sizeof(uint8_t) );
  packet->len = actuallen;
  memset( packet->data, 0, actuallen );

  return packet;
}

struct BMSDIBuffer *newCommandPacket( uint8_t dest, uint8_t len, uint8_t cmd )
{
  uint8_t packetlen = len + sizeof(struct BMSDIHeader);

  struct BMSDIBuffer *out = newPacket( packetlen );
  struct BMSDIPacket *packet = (struct BMSDIPacket *)out->data;

  packet->header.dest = dest;
  packet->header.cmd_id = cmd;
  packet->header.cmd_len =  len;
  packet->header.reserved = 0;

  return out;
}

struct BMSDIBuffer *newConfigPacket( uint8_t dest, uint8_t category, uint8_t parameter,
                              uint8_t op, uint8_t dataType, uint8_t count )
{
  uint8_t datalen = sizeOfType( dataType ) * count;
  uint8_t cmdlen  = datalen + sizeof(struct BMSDIConfigHeader);

  struct BMSDIBuffer *out = newCommandPacket( dest, cmdlen, BM_CMD_CONFIG );
  struct BMSDIConfigPacket *packet = (struct BMSDIConfigPacket *)out->data;

  packet->config.category = category;
  packet->config.parameter = parameter;
  packet->config.datatype = dataType;
  packet->config.operation = op;


  return out;
}
