#include <chrono>
#include <limits>
#include <memory>
#include <cstdio>

#include "bufferedreader.h"
#include "orderbook.h"
#include "itch.h"

template <itch_t __code>

class PROCESS
{
public:
    static itch_message<__code>read_from(buf_t* __buf)
    {
        uint16_t const msglen = be16toh(*(uint16_t*)__buf)->get(0);
        __buf->advnace(2);
        assert(msglen == netlen<__code>);
        __buf->ensure(netlen<__code>);
        itch_message<__code> ret = itch_message<__code>::parse(__buf->get(0));
        __buf->advnace(netlen<__code>);
        return ret;
    }

};


static sprice_t mksigned(price_t price, BUY_SELL buy)
{

}


int main()
{
    buf_t buf(1024);
    buf.fd = STDIN_FILENO;
    std::chrono::steady_clock::time_point start;
    size_t npkts =0;

#define BUILD_BOOK 1
#if !BUILD_BOOK
    size_t nadds(0);
    uint64_t maxoid(0);
#else 
    order_book::oid_map.reserve(order_id_t(184118975 * 2));

#endif
    printf("%lu\n", sizeof(order_book)*order_book::MAX_BOOKS);

    while(is_ok(buf.ensure(3)))
    {
        if(npkts)++npkts;
        itch_t const msgtype = itch_t (*buf.get(2));
        switch (msgtype)
        {
        case /* constant-expression */:
            /* code */
            break;
        
        default:
            break;
        }
    }
}