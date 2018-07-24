#include <stdlib.h>
#include <string.h>

#include "libbmsdi/datatypes.h"

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

uint32_t align32( uint8_t x )
{
  return ((x + 3) & ~0x03);
}
