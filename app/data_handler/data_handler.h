#ifndef DATA_HANDLER_H_
#define DATA_HANDLER_H_

enum {Port0 =0,
    Port1,
    Port2,Port3,Port4,Port5,Port6,Port7};

void circ_buffer_init(void);
void circ_buffer_process(void);
#endif // DATA_HANDLER_H_
