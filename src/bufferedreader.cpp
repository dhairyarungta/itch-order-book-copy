#include "bufferedreader.h"
#include <errno.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>


read_t buf_t::ensure(unsigned int const n)
{
    if(this->available(n))
    {
        return read_t::OK;
    }
    ssize_t bytes = this->read(n);

    if(bytes ==0)
    {
        return read_t::ERR;
    }
    else if (bytes<0)
    {
        return read_t::ERR;
    }
    else 
    {
        return read_t::OK;
    }

}

ssize_t buf_t::read(unsigned int const n)
{
    assert(n<=len);
    assert(pos<=limit);
    assert(limit<=len);
    
    if (pos+n > len)
    {
        discard_to_pos();
    }
    ssize_t bytes_read = 0;
    while ((this->available())<n)
    {
        ssize_t bytes_temp = this->read();
        if(bytes_temp<0)
        {
            perror("Read error:");
            return bytes_temp;
        }
        if(bytes_temp==0)
            return 0;
        bytes_read+=bytes_temp;
    }

    return bytes_read;
    
}


ssize_t buf_t::read()
{
    ssize_t bytes =::read(this->fd, (void*)(ptr+limit), len-limit);
    if(bytes==-1)
    {
        perror("blocking read into buf!");
        return -1;
    }

    assert(bytes>=0);
    assert(bytes<=len);
    limit+=(unsigned)bytes;
    bytesread+=(size_t)bytes;
    assert(pos<=limit);
    assert(limit<=len);
    return bytes;
}

ssize_t buf_t::nb_read()
{
    ssize_t bytes = recv(this->fd, (void*)(ptr+limit), len-limit, MSG_DONTWAIT);
    if(bytes==-1)
        return -1;
    
    assert(bytes <=len);
    assert(bytes >= 0);
    limit+=(unsigned)bytes;

    bytesread+=(size_t)bytes;
    assert(pos<=limit);
    assert(limit<=len);
    return bytes;
}