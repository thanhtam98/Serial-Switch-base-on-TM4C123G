#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "circular_buffer.h"

 int circBufPush(circBuf_t *c, uint8_t data)
 {
     int next  = c-> head +1;
     if (next >= c-> maxLen)
         next = 0;
     if (next == c->tail)
         return -1;

     c->buffer[c->head] = data;
     c->head = next;
     return 0;

 }
 int circBufPop(circBuf_t *c, uint8_t *data)
 {
     if (c->head == c -> tail) // buffer is empty
         return -1;

     int next = c->tail +1;
     if(next >= c->maxLen)
         next =0;

     *data =c->buffer[c->tail];
     c->tail = next;
     return 0;

 }
