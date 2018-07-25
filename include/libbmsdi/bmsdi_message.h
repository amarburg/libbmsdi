#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_BUFFER_LEN   (255)

#define MAX_MESSAGE_LEN  (64)
#define MESSAGE_HEADER_LEN (4)
#define MAX_PAYLOAD_LEN  (MAX_MESSAGE_LEN-MESSAGE_HEADER_LEN)

#define COMMAND_HEADER_LEN (4)
#define MAX_COMMAND_DATA (MAX_PAYLOAD_LEN-COMMAND_HEADER_LEN)

// "Rounds up" to nearest multiple of 4 (aka 32 bits)
uint32_t align32( uint8_t x );
uint8_t sizeOfType( uint8_t t );

// Generic buffer
struct BMSDIBuffer {
  uint8_t len;
  char    data[MAX_BUFFER_LEN];
};

// 4-byte header for all packets
struct BMSDIHeader {
  uint8_t dest;
  uint8_t cmd_len;
  uint8_t cmd_id;
  uint8_t reserved; // Always 0
};

struct BMSDIConfigMsg {
  struct BMSDIConfigHeader {
    uint8_t category;
    uint8_t parameter;
    uint8_t datatype;
    uint8_t operation;
  } header;
  char bytes[MAX_COMMAND_DATA];
};

// Generic packet consisting of header and payload
struct BMSDIMessage {
  struct BMSDIHeader header;
  union {
    char bytes[MAX_PAYLOAD_LEN];
    struct BMSDIConfigMsg config;
  };
};

// == Core functions ==

// Function for manipulating buffers
struct BMSDIBuffer *bmNewBuffer();
struct BMSDIMessage *bmAddMessage( struct BMSDIBuffer *buffer,
                                  uint8_t dest, uint8_t len, uint8_t cmd);

struct BMSDIMessage *bmAddConfigMessage( struct BMSDIBuffer *buffer,
                                        uint8_t dest, uint8_t category, uint8_t parameter,
                                        uint8_t op,   uint8_t dataType, uint8_t count );

void bmResetBuffer( struct BMSDIBuffer *buffer );


// struct BMSDIConfigPacket *bmAddConfigPacket( struct BMSDIBuffer *buffer,
//                                       uint8_t dest, uint8_t category, uint8_t parameter,
//                                       uint8_t op, uint8_t dataType, uint8_t count );


#define DefineWriteFunctions( name, type ) \
  inline void bmConfigWrite##name##At( struct BMSDIMessage *msg, int i, type d ) \
  { \
    ((type *)msg->config.bytes)[i] = d; \
  } \
  inline void bmConfigWrite##name( struct BMSDIMessage *msg, type d ) \
  {  \
    bmConfigWrite##name##At( msg, 0, d ); \
  }

DefineWriteFunctions( Boolean, uint8_t )
DefineWriteFunctions( Int8, uint8_t )
DefineWriteFunctions( Int16, uint16_t )
DefineWriteFunctions( Int32, uint32_t )
DefineWriteFunctions( Int64, uint64_t )

// Specialized versions for dealing with Fixed32 types
inline void bmConfigWriteFixed16At( struct BMSDIMessage *msg, int i, float f )
{
  ((int16_t *)msg->config.bytes)[i] = floatToFixed16(f);
}

inline void bmConfigWriteFixed16( struct BMSDIMessage *msg, float f )
{
  bmConfigWriteFixed16At( msg, 0, f );
}

#ifdef __cplusplus
}
#endif
