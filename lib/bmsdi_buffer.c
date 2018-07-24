
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "libbmsdi/bmsdi_message.h"


// Allocate a new 255-character BMSDIBuffer with room for up to 255 characters
// plus its own overhead fields
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

int bmAddMessage( struct BMSDIBuffer *buffer, struct BMSDIMessage *msg )
{
  if( (buffer->len + msg->len) > MAX_BUFFER_LEN ) return -1;

  memcpy( (void *)&(buffer->data[buffer->len]), msg->raw, msg->len );
  buffer->len += msg->len;

  return buffer->len;
}

// Combines bmnewBuffer and
struct BMSDIBuffer *bmNewMessageBuffer(struct BMSDIMessage *msg)
{
  struct BMSDIBuffer *buffer = bmNewBuffer();
  bmAddMessage( buffer, msg );
  return buffer;
}
