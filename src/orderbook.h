#pragma once 
#include <vector>

#define MKPRIMITIVE(__x)((std::underlying_type<decltype(__x)>::type)__x)

constexpr bool is_power_of_two(uint64_t n)
{
    return (n!=0 && ((n&(n-1))==0));
}


enum class sprice_t : int32_t {};

bool constexpr is_bid(spric_t const x) {return int32_t(x)>=0;}
#define MEMORY_DEFS using __ptr = ptr_t;\
    using size_t__ = typename std::underlying_type<ptr_t>::type;




typedef struct order 
{
    qty_t m_qty;
    level_id_t level_idx;
    book_id_t book_idx;
}order_t;


class price_level
{
public:
    price_level()
    {}

    
}