#pragma once


#include <stdint.h>

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

struct BMSDIBuffer {
  uint8_t len;
  char    data[];
};


struct BMSDIHeader {
  uint8_t dest;
  uint8_t cmd_len;
  uint8_t cmd_id;
  uint8_t reserved;
};

struct BMSDIPacket {
  struct BMSDIHeader header;
  char   payload[];
};




// Right now there's only one command:
//    "0" == change config
struct BMSDIConfigHeader {
  uint8_t category;
  uint8_t parameter;
  uint8_t datatype;
  uint8_t operation;
};


struct BMSDIConfigPacket {
  struct BMSDIHeader header;
  struct BMSDIConfigHeader config;
  char   payload[];
};


/// Basic functions


inline uint32_t align32( uint8_t x ) { return ((x + 3) & ~0x03); }

struct BMSDIBuffer *bmNewPacket( uint8_t len );

struct BMSDIBuffer *bmNewCommandPacket( uint8_t dest, uint8_t len, uint8_t cmd );

struct BMSDIBuffer *bmNewConfigPacket( uint8_t dest, uint8_t category, uint8_t parameter,
                                     uint8_t op, uint8_t dataType, uint8_t count );

#define bmConfigWriteBoolean( x, y ) (bmConfigWriteInt8(x,y))
void bmConfigWriteInt8( struct BMSDIBuffer *buffer, int8_t d )
{
  struct BMSDIConfigPacket *packet = (struct BMSDIConfigPacket *)buffer->data;
  *(uint8_t *)packet->payload = d;
}

void bmConfigWriteInt16( struct BMSDIBuffer *buffer, int16_t d )
{
  struct BMSDIConfigPacket *packet = (struct BMSDIConfigPacket *)buffer->data;
  *(int16_t *)packet->payload = d;
}

void bmConfigWriteInt32( struct BMSDIBuffer *buffer, int32_t d )
{
  struct BMSDIConfigPacket *packet = (struct BMSDIConfigPacket *)buffer->data;
  *(int32_t *)packet->payload = d;
}

void bmConfigWriteInt64( struct BMSDIBuffer *buffer, int64_t d )
{
  struct BMSDIConfigPacket *packet = (struct BMSDIConfigPacket *)buffer->data;
  *(int64_t *)packet->payload = d;
}

void bmConfigWriteFixed32( struct BMSDIBuffer *buffer, float f )
{
  struct BMSDIConfigPacket *packet = (struct BMSDIConfigPacket *)buffer->data;
  *(int16_t *)packet->payload = floatToFixed16(f);
}




#ifdef __cplusplus
}
#endif
