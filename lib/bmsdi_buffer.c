
#include "bmsdi_message.h"


// Allocate a new 255-character BMSDIBuffer with room for up to 255 characters
// plus its own overhead fields
struct BMSDIBuffer *bmNewBuffer()
{
  struct BMSDIBuffer *buffer = malloc( struct BMSDIBuffer );
  buffer->len = 0;
  return buffer;
}

void bmResetBuffer( struct BMSDIBuffer *buffer )
{
  buffer->len = 0;
}

struct int bmAddMessage( struct BMSDIBuffer *buffer, struct BMSDIMessage *msg )
{
  if( (buffer->len + app->len) > buffer->alloc ) return false;

  memcpy( (void *)&(buffer->data[buffer->len]), app->data, app->len );
  buffer->len += app->len;

  return true;
}

// Combines bmnewBuffer and
struct BMSDIBuffer *bmNewMessageBuffer(struct BMSDIMessage *msg)
{
  struct BMSDIBuffer *buffer = bmNewBuffer();
  bmAddMessage( buffer, msg );
  return buffer;
}
