#ifndef ITCH_H
#define ITCH_H


#include <sys/types.h>
#include <cstring>


enum class itch_t
{
  SYSEVENT = 'S',
  STOCK_DIRECTORY = 'R',
  TRADING_ACTION = 'H',
  REG_SHO_RESTRICT = 'Y',  // 20
  MPID_POSITION = 'L',     // 26
  MWCB_DECLINE = 'V',      // market wide circuit breaker // 35
  MWCB_STATUS = 'W',
  IPO_QUOTE_UPDATE = 'K',  // 28
  ADD_ORDER = 'A',         // 36
  ADD_ORDER_MPID = 'F',
  EXECUTE_ORDER = 'E',
  EXECUTE_ORDER_WITH_PRICE = 'C',
  REDUCE_ORDER = 'X',
  DELETE_ORDER = 'D',
  REPLACE_ORDER = 'U',
  TRADE = 'P',
  CROSS_TRADE = 'Q',
  BROKEN_TRADE = 'B',
  NET_ORDER_IMBALANCE = 'I',
  RETAIL_PRICE_IMPROVEMENT = 'N',
  PROCESS_LULD_AUCTION_COLLAR_MESSAGE = 'J'

};

using MSG = itch_t;

template <MSG __type>
unsigned char constexpr netlen = -1;

//Template specilisations for netlen
template<>
constexpr unsigned char netlen<MSG::SYSEVENT> =12;

template<>
constexpr unsigned char netlen <MSG::STOCK_DIRECTORY> =39;

template<>
constexpr unsigned char netlen<MSG::TRADING_ACTION> = 25;

template<>
constexpr unsigned char netlen<MSG::REG_SHO_RESTRICT> = 20;

template<>
constexpr unsigned char netlen<MSG::MPID_POSITION> = 26;

template<>
constexpr unsigned char netlen<MSG::MWCB_DECLINE> = 35;

template<>
constexpr unsigned char netlen<MSG::MWCB_STATUS> = 12;

template<>
constexpr unsigned char netlen<MSG::IPO_QUOTE_UPDATE> = 28;

template<>
constexpr unsigned char netlen<MSG::ADD_ORDER> = 36;

template<>
constexpr unsigned char netlen<MSG::ADD_ORDER_MPID> =40;

template<>
constexpr unsigned char netlen<MSG::EXECUTE_ORDER> =31;

template<>
constexpr unsigned char netlen<MSG::EXECUTE_ORDER_WITH_PRICE> =36;

template<>
constexpr unsigned char netlen<MSG::REDUCE_ORDER> =23;

template<>
constexpr unsigned char netlen<MSG::REPLACE_ORDER> =35;

template<>
constexpr unsigned char netlen<MSG::TRADE> = 44;

template<>
constexpr unsigned char netlen<MSG::CROSS_TRADE> =40;

template<>
constexpr unsigned char netlen<MSG::BROKEN_TRADE> =19;

template<>
constexpr unsigned char netlen<MSG::NET_ORDER_IMBALANCE> =50;

template<>
constexpr unsigned char netlen<MSG::RETAIL_PRICE_IMPROVEMENT> =20;

template<>
constexpr unsigned char netlen<MSG::PROCESS_LULD_AUCTION_COLLAR_MESSAGE> =35;


template<itch_t __code>
struct itch_message
{   
    static constexpr itch_t code = __code;
    static constexpr unsigned char network_len = netlen<__code>;
    static itch_message parse (char const*ptr)
    {
        static_cast<void>(ptr);
        return itch_message();
    }

};

enum class BUY_SELL : char {BUY = 'B' , SELL = 'S'};
enum class timestamp_t :uint64_t{};
enum class oid_t :uint64_t{};
enum class price_t : uint32_t{};
enum class qty_t : uint32_t{};

static uint64_t read_eight(char const *src)
{
    return be64toh(*(uint64_t const*)src);
}

static uint64_t read_six(char const *src)
{
    uint64_t ret;
    char *pun = (char*)&ret;
    memcpy(pun ,src, 6);
    return (be64toh(ret)>>16);
}

static uint32_t read_four(char const *src)
{
    return be32toh(*(uint32_t const *)src);
}

static uint16_t read_two (char const *src)
{
    return be16toh(*(uint16_t const *)src);
}

static timestamp_t read_timestamp (char const *src)
{
    return timestamp_t(read_six(src));
}

static oid_t read_oid (char const *src)
{
    return oid_t(read_eight(src));
}

static price_t read_price(char const *src)
{
    return price_t(read_four(src));
}

static qty_t read_qty(char const *src)
{
    return qty_t(read_four(src));
}

static uint16_t read_locate(char const *src)
{
    return read_two(src);
}

using add_order_t = itch_message<MSG::ADD_ORDER>;

struct itch_message_

#endif 