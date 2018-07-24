
#include <stdlib.h>
#include <string.h>

#include "libbmsdi/bmsdi_message.h"


struct BMSDIMessage *bmNewMessage( uint8_t dest, uint8_t len, uint8_t cmd )
{
  struct BMSDIMessage *msg = malloc(sizeof(struct BMSDIMessage));
  msg->len = len + 4;

  msg->message.header.dest = dest;
  msg->message.header.cmd_id = cmd;
  msg->message.header.cmd_len = len;
  msg->message.header.reserved = 0;

  return msg;
}

struct BMSDIMessage *bmNewConfigMessage( uint8_t dest, uint8_t category, uint8_t parameter,
                                         uint8_t op,   uint8_t dataType, uint8_t count )
{
  uint8_t cmdlen = sizeof(struct BMSDIConfigHeader) + (sizeOfType(dataType) * count);
  struct BMSDIMessage *msg = bmNewMessage( dest, cmdlen, BM_CMD_CONFIG );

  msg->message.config.header.category = category;
  msg->message.config.header.parameter = parameter;
  msg->message.config.header.datatype = dataType;
  msg->message.config.header.operation = op;

  return msg;
}
