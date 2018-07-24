
#include <stdlib.h>
#include <string.h>

#include "libbmsdi/bmsdi_message.h"

//
// static void bmInitCommandPacket( struct BMSDIPacket *packet,
//                                   uint8_t dest, uint8_t len, uint8_t cmd )
// {
//     packet->header.dest = dest;
//     packet->header.cmd_id = cmd;
//     packet->header.cmd_len =  len;
//     packet->header.reserved = 0;
// }
//
// static void bmInitConfigPacket( struct BMSDIConfigPacket *packet,
//                                 uint8_t category, uint8_t parameter,
//                                 uint8_t op, uint8_t dataType )
// {
//   packet->config.category = category;
//   packet->config.parameter = parameter;
//   packet->config.datatype = dataType;
//   packet->config.operation = op;
// }
//
// static struct BMSDIBuffer *bmAllocBufferN( uint8_t sz )
// {
//   struct BMSDIBuffer *packet = (struct BMSDIBuffer *)malloc( sz + 2*sizeof(uint8_t) );
//   packet->len = 0;
//   packet->alloc = sz;
//
//   memset( packet->data, 0, sz );
//
//   return packet;
// }


struct BMSDIMessage *bmNewMessage( uint8_t dest, uint8_t len, uint8_t cmd )
{
  struct BMSDIBuffer *out = malloc(struct BMSDIMessage);
  out->len = packetlen;

  bmInitCommandPacket( (struct BMSDIPacket *)out->data, dest, len, cmd );

  return out;
}



struct BMSDIMessage *bmNewConfigMessage( uint8_t dest, uint8_t category, uint8_t parameter,
                                         uint8_t op,   uint8_t dataType, uint8_t count )
{
  uint8_t cmdlen  = sizeOfType( dataType ) * count + sizeof(struct BMSDIConfigHeader);
  struct BMSDIMessage *msg = bmNewMessage( dest, cmdlen, BM_CMD_CONFIG );

  msg->message.config.header.category = category;
  msg->message.config.header.parameter = parameter;
  msg->message.config.header.datatype = dataType;
  msg->message.config.header.operation = op;



  return out;
}
