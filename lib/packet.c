
#include <stdlib.h>
#include <string.h>

#include "libbmsdi/bmsdi.h"

static uint8_t sizeOfType( uint8_t t ) {
  switch( t ) {
  case BM_TYPE_BOOLEAN:
  case BM_TYPE_INT8:
  case BM_TYPE_STR:
      return 1;
  case BM_TYPE_FIXED16:
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


static void bmInitCommandPacket( struct BMSDIPacket *packet,
                                  uint8_t dest, uint8_t len, uint8_t cmd )
{
    packet->header.dest = dest;
    packet->header.cmd_id = cmd;
    packet->header.cmd_len =  len;
    packet->header.reserved = 0;
}

static void bmInitConfigPacket( struct BMSDIConfigPacket *packet,
                                uint8_t category, uint8_t parameter,
                                uint8_t op, uint8_t dataType )
{
  packet->config.category = category;
  packet->config.parameter = parameter;
  packet->config.datatype = dataType;
  packet->config.operation = op;
}

static struct BMSDIBuffer *bmAllocBufferN( uint8_t sz )
{
  struct BMSDIBuffer *packet = (struct BMSDIBuffer *)malloc( sz + 2*sizeof(uint8_t) );
  packet->len = 0;
  packet->alloc = sz;

  memset( packet->data, 0, sz );

  return packet;
}

// Allocate a new 255-character BMSDIBuffer with room for up to 255 characters
// plus its own overhead fields
struct BMSDIBuffer *bmAllocBuffer()
{
  return bmAllocBufferN( 255 );
}

struct BMSDIPacket *bmAddPacket( struct BMSDIBuffer *buffer,
                                uint8_t dest, uint8_t len, uint8_t cmd )
{
  uint8_t packetlen = len + sizeof(struct BMSDIHeader);

  // Round up to nearest 32-bit boundary
  uint8_t actuallen = align32( packetlen );
  if( (buffer->len + actuallen) > buffer->alloc ) return NULL;

  struct BMSDIPacket *packet = (struct BMSDIPacket *)&(buffer->data[buffer->len]);
  buffer->len += actuallen;

  bmInitCommandPacket( packet, dest, len, cmd );

  return packet;
}

struct BMSDIConfigPacket *bmAddConfigPacket( struct BMSDIBuffer *buffer,
                                      uint8_t dest, uint8_t category, uint8_t parameter,
                                     uint8_t op, uint8_t dataType, uint8_t count )
{
  uint8_t cmdlen  = sizeOfType( dataType ) * count + sizeof(struct BMSDIConfigHeader);

  struct BMSDIConfigPacket *packet = (struct BMSDIConfigPacket *)bmAddPacket( buffer, dest, cmdlen, BM_CMD_CONFIG );

  bmInitConfigPacket( packet, category, parameter, op, dataType );

  return packet;
}




struct BMSDIBuffer *bmNewPacket( uint8_t dest, uint8_t len, uint8_t cmd )
{
  uint8_t packetlen = align32(len + sizeof(struct BMSDIHeader));

  struct BMSDIBuffer *out = bmAllocBufferN( packetlen );
  out->len = packetlen;

  bmInitCommandPacket( (struct BMSDIPacket *)out->data, dest, len, cmd );

  return out;
}

struct BMSDIBuffer *bmNewConfigPacket( uint8_t dest, uint8_t category, uint8_t parameter,
                              uint8_t op, uint8_t dataType, uint8_t count )
{
  uint8_t cmdlen  = sizeOfType( dataType ) * count + sizeof(struct BMSDIConfigHeader);

  struct BMSDIBuffer *out = bmNewPacket( dest, cmdlen, BM_CMD_CONFIG );

  bmInitConfigPacket( (struct BMSDIConfigPacket *)out->data, category, parameter, op, dataType );

  return out;
}
