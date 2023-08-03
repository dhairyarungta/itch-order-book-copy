#ifndef ITCH_H
#define ITCH_H


#include <sys/types.h>

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




#endif 