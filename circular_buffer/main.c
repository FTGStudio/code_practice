#include <stdlib.h>
#include <stdint.h>


typedef struct
{
    uint8_t * const buffer;
    int head;
    int tail;
    const int maxlen;
} circ_bbuf_t;

int circ_bbuf_push(circ_bbuf_t *c, uint8_t data)
{
    int next;
    next = c->head+1; // next is where head will piint to after this write
    if(next >= c->maxlen)
        next = 0;
    
    if(next == c->tail) // if the head1 == tail, circular buffer is fulls
        return -1;
    
    c->buffer[c->head] = data; // load data and then move
    c->head = next; // head to next data offset
    return 0; // return success to indicate successful push
}

int circ_bbuf_pop(circ_bbuf_t *c, uint8_t *data)
{
    int next;

    if(c->head == c->tail) // if thea head == tail, we don't have any data
        return -1;
    
    next = c->tail + 1; // next is where tail will point to after this read
    if(next >= c->maxlen)
        next = 0;

    *data = c->buffer[c->tail]; // read data and then move
    c->tail = next;
    return 0; //return success to indicate sucessful push.
}