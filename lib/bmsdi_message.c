
#include <stdlib.h>
#include <string.h>

#include "libbmsdi/bmsdi_message.h"

// Allocate a new 255-character BMSDIBuffer with room for up to 255 characters
// plus its own overhead fields

// TODO.  Technically you don't even need len, you can just calculate it
// by walking the list of messages
struct BMSDIBuffer *bmNewBuffer()
{
  struct BMSDIBuffer *buffer = malloc( sizeof(struct BMSDIBuffer) );
  buffer->len = 0;
  memset(buffer->data, 0, MAX_BUFFER_LEN );
  return buffer;
}

void bmResetBuffer( struct BMSDIBuffer *buffer )
{
  buffer->len = 0;
}

struct BMSDIMessage *bmAddMessage( struct BMSDIBuffer *buffer,
                                  uint8_t dest, uint8_t len, uint8_t cmd)
{
  uint8_t msg_len = align32(len + sizeof(struct BMSDIHeader));
  if( (buffer->len + msg_len) > MAX_BUFFER_LEN ) return NULL;

  struct BMSDIMessage *msg = (void *)&(buffer->data[buffer->len]);
  buffer->len += msg_len;

  msg->header.dest = dest;
  msg->header.cmd_id = cmd;
  msg->header.cmd_len = len;
  msg->header.reserved = 0;

  return msg;
}

struct BMSDIMessage *bmAddConfigMessage( struct BMSDIBuffer *buffer,
                                        uint8_t dest, uint8_t category, uint8_t parameter,
                                        uint8_t op,   uint8_t dataType, uint8_t count )
{
  uint8_t cmdlen = sizeof(struct BMSDIConfigHeader) + (sizeOfType(dataType) * count);

  struct BMSDIMessage *msg=bmAddMessage(buffer, dest, cmdlen, BM_CMD_CONFIG  );
  if( msg==NULL ) return NULL;

  msg->config.header.category = category;
  msg->config.header.parameter = parameter;
  msg->config.header.datatype = dataType;
  msg->config.header.operation = op;

  return msg;
}

// Bearing in mind there's no way to know if a message is valid other than
// inspecting its contents
struct BMSDIMessage *bmMessageAt( struct BMSDIBuffer *buffer, int idx )
{
  int offset = 0, count = 0;

  while( offset < MAX_BUFFER_LEN ) {
    struct BMSDIMessage *msg = (void *)&(buffer->data[offset]);

    if( idx == count ) return msg;

    // Else advance
    offset += align32( sizeof(struct BMSDIHeader) + msg->header.cmd_len);
    ++count;
  }

  return NULL;
}
