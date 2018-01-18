#pragma once


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct BMSDIPacket {
  uint8_t len;
  char    data[];
};

struct BMSDIHeader {
  uint8_t dest;
  uint8_t cmd_len;
  uint8_t cmd_id;
  uint8_t reserved;
};

// Right now there's only one command:
//    "0" == change config
struct BMSDIConfigHeader {
  uint8_t category;
  uint8_t parameter;
  uint8_t datatype;
  uint8_t operation;
};

struct BMSDICmdPacket {
  struct BMSDIHeader header;
  char   payload[];
};

struct BMSDIConfigPacket {
  struct BMSDIHeader header;
  struct BMSDIConfigHeader config;
  char   payload[];
};

#define BM_CMD_CONFIG    0

// Defines
#define BM_OP_ASSIGN     0
#define BM_OP_OFFSET     1
//Operation types 2 through 127 are reserved.
//Operation types 128 through 255 are available for device specific purposes.

#define BM_TYPE_BOOLEAN  0
#define BM_TYPE_INT8     1
#define BM_TYPE_INT16    2
#define BM_TYPE_INT32    3
#define BM_TYPE_INT64    4
#define BM_TYPE_STR      5
// data types 6-127 are Reserved

inline uint8_t sizeOfType( uint8_t t ) {
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

inline uint32_t align32( uint8_t x ) { return ((x + 3) & ~0x03); }

struct BMSDIPacket *newPacket( uint8_t len );

struct BMSDIPacket *newCommandPacket( uint8_t dest, uint8_t len, uint8_t cmd );

struct BMSDIPacket *newConfigPacket( uint8_t dest, uint8_t category, uint8_t parameter,
                                     uint8_t op, uint8_t dataType, uint8_t count );

#ifdef __cplusplus
}
#endif
