#pragma once


#include <stdint.h>

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

struct BMSDIBuffer {
  uint8_t len, alloc;
  char    data[];
};


//
struct BMSDIHeader {
  uint8_t dest;
  uint8_t cmd_len;
  uint8_t cmd_id;
  uint8_t reserved; // Always 0
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


// Core functions

// "Rounds up" to nearest multiple of 4 (aka 32 bits)
uint32_t align32( uint8_t x ); 


// These are the one-shot versions
struct BMSDIBuffer *bmNewPacket( uint8_t dest, uint8_t len, uint8_t cmd );

struct BMSDIBuffer *bmNewConfigPacket( uint8_t dest, uint8_t category, uint8_t parameter,
                                     uint8_t op, uint8_t dataType, uint8_t count );


// Version which allows for multiple commands in a buffer

struct BMSDIBuffer *bmAllocBuffer();

struct BMSDIPacket *bmAddPacket( struct BMSDIBuffer *buffer,
                                uint8_t dest, uint8_t len, uint8_t cmd );

struct BMSDIConfigPacket *bmAddConfigPacket( struct BMSDIBuffer *buffer,
                                      uint8_t dest, uint8_t category, uint8_t parameter,
                                      uint8_t op, uint8_t dataType, uint8_t count );


#define DefineWriteFunctions( name, type ) \
  inline void bmConfigWriteAt##name( struct BMSDIConfigPacket *packet, int i, type d ) \
  { \
    ((type *)packet->payload)[i] = d; \
  } \
  inline void bmConfigWrite##name( struct BMSDIConfigPacket *packet, type d ) \
  {  \
    bmConfigWriteAt##name( packet, 0, d ); \
  } \
  inline void bmFirstConfigWriteAt##name( struct BMSDIBuffer *buffer, int i, type d ) \
  { \
    bmConfigWriteAt##name( (struct BMSDIConfigPacket *)buffer->data, i, d ); \
  } \
  inline void bmFirstConfigWrite##name( struct BMSDIBuffer *buffer, type d ) \
  { \
    bmFirstConfigWriteAt##name( buffer, 0, d ); \
  }


DefineWriteFunctions( Boolean, uint8_t )
DefineWriteFunctions( Int8, uint8_t )
DefineWriteFunctions( Int16, uint16_t )
DefineWriteFunctions( Int32, uint32_t )
DefineWriteFunctions( Int64, uint64_t )

inline void bmConfigWriteAtFixed32( struct BMSDIConfigPacket *packet, int i, float f )
{
  ((int16_t *)packet->payload)[i] = floatToFixed16(f);
}

inline void bmConfigWriteFixed32( struct BMSDIConfigPacket *packet, float f )
{
  bmConfigWriteAtFixed32( packet, 0, f );
}

inline void bmFirstConfigWriteAtFixed32( struct BMSDIBuffer *buffer, int i, float f )
{
  bmConfigWriteAtFixed32( (struct BMSDIConfigPacket *)buffer->data, i, f );
}

inline void bmFirstConfigWriteFixed32( struct BMSDIBuffer *buffer, float f )
{
  bmFirstConfigWriteAtFixed32( buffer, 0, f );
}

#ifdef __cplusplus
}
#endif
