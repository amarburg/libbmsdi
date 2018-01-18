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

struct BMSDIBuffer *newPacket( uint8_t len );

struct BMSDIBuffer *newCommandPacket( uint8_t dest, uint8_t len, uint8_t cmd );

struct BMSDIBuffer *newConfigPacket( uint8_t dest, uint8_t category, uint8_t parameter,
                                     uint8_t op, uint8_t dataType, uint8_t count );

#ifdef __cplusplus
}
#endif
