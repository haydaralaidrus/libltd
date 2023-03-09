#include "../include/ltd/ref_counter.hpp"

namespace ltd
{
    ref_counter::ref_counter() : counter(1)
    {

    }

    void ref_counter::inc()
    {
        ++counter;
    }

    bool ref_counter::dec()
    {
        return --counter == 0;
    }
}
