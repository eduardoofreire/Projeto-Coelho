#include <stdio.h>
#include <ctype.h>
#include "buffer.h"

Buffer *buffer_create(size_t member_size) {
    Buffer *buffer = malloc(sizeof(Buffer));
    buffer->member_size = member_size;
    buffer->buffer_size = 2;
    buffer->p = 0;
    buffer->data = malloc(buffer->member_size * buffer->buffer_size);
    return buffer;
}

void buffer_destroy(Buffer *B) {
    free(B->data);
    free(B);
}

void buffer_reset(Buffer *B) {
    free(B->data);
    B->p = 0;
    B->data = malloc(B->member_size * B->buffer_size);
}

void *buffer_push_back(Buffer *B) {
    B->p++;

    //Se tentar add num vetor cheio
    if(B->p > B->buffer_size){
        B->buffer_size *= 2;
        void *dataux = malloc(B->member_size * B->buffer_size);
        void *p = B->data;
        //p  B->member_size;
        void *paux = dataux;

        for (int i = 0; i < B->p; ++i) {
            p += B->member_size;
            paux += B->member_size;
            *(char *) paux = *(char *) p;
        }
        free(B->data);
        B->data = dataux;
    }

    return B->data + B->p*B->member_size;
}

int read_line(FILE *input, Buffer *B) {
    int count = 0;
    buffer_reset(B);
    char c;
    int i;
    while ((i = fgetc(input)) != EOF)
    {
        count++;
        c = (char) i;
        buffer_push_char(B, c);
        if (c == '\n') break;
    }

    return count;
}

int main() {
    /*
    Buffer *b = buffer_create(sizeof(char));
    FILE *input = fopen("test","r");

    read_line(input,b);
    void *p = b->data;
    for (int i = 0; i < b->p; ++i) {
        p++;
        printf("%c", *(char *) p);
    }

    read_line(input,b);
    p = b->data;
    for (int i = 0; i < b->p; ++i) {
        p++;
        printf("%c", *(char *) p);
    }

    //printf("%c\n",input);
    
    buffer_push_char(b, 'a');
    buffer_push_char(b, 'b');
    buffer_push_char(b, 'c');

    void *p = b->data;
    for (int i = 0; i < b->p; ++i) {
        p++;
        printf("%c", *(char *) p);
    }
    printf("\n");

    buffer_reset(b);

    p = b->data;
    for (int i = 0; i < b->p; ++i) {
        p++;
        printf("%c", *(char *) p);
    }
    printf("\n");

    buffer_push_char(b, 'a');
    buffer_push_char(b, 'b');
    buffer_push_char(b, 'c');
    buffer_push_char(b, 'd');

    p = b->data;
    for (int i = 0; i < b->p; ++i) {
        p++;
        printf("%c", *(char *) p);
    }
    printf("\n");
    
    
    printf("%c\n", *(char *) b->data);
    printf("%zu\n",b->p);
    printf("%zu\n",b->member_size);
    printf("%zu\n",b->buffer_size);
    */

    //buffer_destroy(b);
}