#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "protocol.h"
#include "datatypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_BUFFER_LEN   (255)

#define MAX_MESSAGE_LEN  (64)
#define MAX_PAYLOAD_LEN  (MAX_MESSAGE_LEN-4)
#define MAX_COMMAND_DATA (MAX_MESSAGE_LEN-8)

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

struct BMSDIConfigData {
  struct {
    uint8_t category;
    uint8_t parameter;
    uint8_t datatype;
    uint8_t operation;
  } header;
  char bytes[MAX_COMMAND_DATA];
};

// Generic packet consisting of header and payload
struct BMSDIMessage {
  int msgLen;

  union {
    char raw[MAX_MESSAGE_LEN];

    struct {
      struct BMSDIHeader header;
      union {
        struct BMSDIConfigData config;
        char bytes[MAX_PAYLOAD_LEN];
      };
    } message;
  };
};

// == Core functions ==

// Function for manipulating buffers
struct BMSDIBuffer *bmNewBuffer();
struct BMSDIBuffer *bmNewMessageBuffer(struct BMSDIMessage *msg);
void bmResetBuffer( struct BMSDIBuffer *buffer );
int bmAddMessage( struct BMSDIBuffer *buffer, struct BMSDIMessage *msg );

// Generate a new BMSDIMessage.
struct BMSDIMessage *bmNewMessage( uint8_t dest, uint8_t len, uint8_t cmd );
struct BMSDIMessage *bmNewConfigMessage( uint8_t dest, uint8_t category, uint8_t parameter,
                                        uint8_t op,   uint8_t dataType, uint8_t count );

// struct BMSDIConfigPacket *bmAddConfigPacket( struct BMSDIBuffer *buffer,
//                                       uint8_t dest, uint8_t category, uint8_t parameter,
//                                       uint8_t op, uint8_t dataType, uint8_t count );


#define DefineWriteFunctions( name, type ) \
  inline void bmConfigWrite##name##At( struct BMSDIMessage *msg, int i, type d ) \
  { \
    ((type *)msg->message.config.bytes[i]) = d; \
  } \
  inline void bmConfigWrite##name( struct BMSDIMessage *msg, type d ) \
  {  \
    bmConfigWriteAt##nameAt( packet, 0, d ); \
  }

DefineWriteFunctions( Boolean, uint8_t )
DefineWriteFunctions( Int8, uint8_t )
DefineWriteFunctions( Int16, uint16_t )
DefineWriteFunctions( Int32, uint32_t )
DefineWriteFunctions( Int64, uint64_t )

// Specialized versions for dealing with Fixed32 types
inline void bmConfigWriteAtFixed16( struct BMSDIConfigPacket *packet, int i, float f )
{
  ((int16_t *)msg->message.config.bytes[i]) = floatToFixed16(f);
}

inline void bmConfigWriteFixed16( struct BMSDIConfigPacket *packet, float f )
{
  bmConfigWriteAtFixed16( packet, 0, f );
}

#ifdef __cplusplus
}
#endif
