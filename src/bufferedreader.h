#pragma once

#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>

typedef int fd_t;


enum class read_t {OK, ERROR};
inline bool is_ok(read_t const retcode)
{
    return retcode == read_t::OK;
}

inline read_t operator!(read_t const code)
{
    return code;
}



typedef struct buf 
{
    buf(unsigned int len): ptr(new char[len]), len(len), limit(0), pos(0){}
    ~buf(){delete[] ptr;}
    char *const ptr; //length of buffer
    unsigned int const  len;
    unsigned int limit;

    unsigned int pos;
    
    size_t bytes_read;
    fd_t fd = -1;

    char const *get(unsigned int idx) const
    {
        return ptr+pos+idx;
    }

    unsigned available(void) const {return limit-pos;}
    bool available(unsigned n) const {return pos+n<=limit;}
    unsigned free_space (void )const {return len-limit;}
    void advnace(unsigned bytes)
    {
        pos+=bytes;
        assert(pos<=limit); //assert
    }
    void discard_to_pos(void)
    {
        if(pos && pos<limit)
        {//shitifing to the beginning of the buffer
            memmove((void*)ptr, ptr+pos, limit-pos);//
        }
        limit-=pos;
        //reset pos to the start of buffer
        pos =0;
    }

    void cleanup(void)
    {
        limit = 0;
        pos =0;
        fd = -1;
    }

    ssize_t read(void);
    ssize_t read(unsigned int n);
    read_t ensure (unsigned n);
    ssize_t nb_read(void);
 
} buf_t;