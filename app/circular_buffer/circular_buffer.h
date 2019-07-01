#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t *  buffer;
    int head;
    int tail;
    int maxLen;

} circBuf_t;

#define CIRCBUF_DEF(x,y)    uint8_t x##_dataSpace[y];       \
                            circBuf_t x = {                 \
                                .buffer =   x##_dataSpace,  \
                                           .head   = 0,     \
                                           .tail   = 0,     \
                                           .maxLen = y      \
                            }

 int circBufPush(circBuf_t *c, uint8_t data);
 int circBufPop(circBuf_t *c, uint8_t *data);

 void circ_buffer_init(void);


//TODO: int circular_buf_get_range(circular_buf_t cbuf, uint8_t *data, size_t len);
//TODO: int circular_buf_put_range(circular_buf_t cbuf, uint8_t * data, size_t len);

#endif //CIRCULAR_BUFFER_H_
